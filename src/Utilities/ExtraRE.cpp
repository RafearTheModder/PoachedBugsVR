#include "ExtraRE.h"

namespace REX{
    bool SetEffectMagnitude(RE::Effect* effect, float magnitude)
	{
		using func_t = decltype(&SetEffectMagnitude);
		static REL::Relocation<func_t> func{ REL::Offset(0x108a40) };
		return func(effect, magnitude);
	}

	bool SetEffectDuration(RE::Effect* effect, std::uint32_t duration)
	{
		using func_t = decltype(&SetEffectDuration);
		static REL::Relocation<func_t> func{ REL::Offset(0x108b00) };
		return func(effect, duration);
	}
}