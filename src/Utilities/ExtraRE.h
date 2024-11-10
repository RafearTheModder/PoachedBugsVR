#pragma once

#include "RE/Skyrim.h"

namespace REX{
    /* These set effect duration/magnitude functions would make the most sense in CommonLib, but I do not know the AE/1.6000000000000000000000000 address lib ids...*/
    bool SetEffectMagnitude(RE::Effect* effect, float magnitude);

	bool SetEffectDuration(RE::Effect* effect, std::uint32_t duration);

	// Really shaky on this function's details, so not comfortable submitting it to CommonLib yet
	template <class T>
	unsigned int BSTArrayAddElement(RE::BSTArray<T>* array, T* effect)
	{
		using func_t = decltype(&BSTArrayAddElement<T>);
		static REL::Relocation<func_t> func{ REL::Offset(0x88ea20) };
		return func(array, effect);
	}
}