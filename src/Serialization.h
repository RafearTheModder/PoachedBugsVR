#pragma once

namespace Serialization
{
	enum : std::uint32_t
	{
		// Use the same ID as Scrambled Bugs, since we are mostly taking its place for VR where it does not exist
		kUniqueID = 'ECF'
	};

	void Load(SKSE::SerializationInterface* serializationInterface);
	void Save(SKSE::SerializationInterface* serializationInterface);
}