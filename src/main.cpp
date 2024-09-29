#include "Patches/Patch.h"
#include "dataHandler.h"

#include "Serialization.h"

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
#ifndef NDEBUG
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
	auto path = logger::log_directory();
	if (!path) {
		return false;
	}

	*path /= Version::PROJECT;
	*path += ".log"sv;
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
	log->set_level(spdlog::level::trace);
#else
	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::info);
#endif

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);

	if(Version::COMMITS_SINCE_TAG > 0)
	{
		logger::info("Running Pre-Release Test Build!");
		logger::info(FMT_STRING("{} v{} Commits since version tag: {} Commit Hash: {}"),
								Version::PROJECT, Version::NAME, Version::COMMITS_SINCE_TAG, Version::COMMIT_HASH);
	}
	else
	{
		logger::info(FMT_STRING("{} v{} Commit Hash: {}"), Version::PROJECT, Version::NAME, Version::COMMIT_HASH);
	}

	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = Version::PROJECT.data();
	a_info->version = Version::MAJOR;

	if (a_skse->IsEditor()) {
		logger::critical("Loaded in editor, marking as incompatible");
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver <
#ifndef SKYRIMVR
		SKSE::RUNTIME_1_5_39
#else
		SKSE::RUNTIME_VR_1_4_15
#endif
	) {
		logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
		return false;
	}

	return true;
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	logger::info("loaded");

	SKSE::Init(a_skse);
	dataHandler::readSettings();

	Patch::InstallAllPatches();

	auto serializationInterface = SKSE::GetSerializationInterface();
	serializationInterface->SetUniqueID(Serialization::kUniqueID);
	serializationInterface->SetSaveCallback(std::addressof(Serialization::Save));
	serializationInterface->SetLoadCallback(std::addressof(Serialization::Load));

	return true;
}
