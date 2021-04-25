// *********************************************************************************************************************
// Markup Elem Effect
//
// Module:			Markup
// Namespace:		PRMU
// Contact Person:	EB
//
// SG Compatible
// *********************************************************************************************************************


#ifndef	COMPONENTEFFECT_HPP
#define	COMPONENTEFFECT_HPP

#pragma once

// from Markup
#include "EntryComponent.hpp"
#include "EntryComponentTypes.hpp"

// from GSRoot
#include "FastLock.hpp"

namespace Cache {
	class GenericCache;
};

namespace PRMU {
class MARKUP_DLL_EXPORT ComponentEffect
{
	friend struct ComponentEffectGetter;

private:
	mutable GS::FastLock cacheLock;
	mutable Cache::GenericCache* cache;

public:
	ComponentEffect (Cache::GenericCache* cache);

	GS::Pair<PRMU::EntryComponent::Type, bool> GetComponentType (const EDB::GeneralElemConstRef& pElem, bool areSubelemsRelevant) const;

protected:
	PRMU::EntryComponent::Type GetType (const EDB::GeneralElemConstRef &mainElem, const EDB::GeneralElemConstRef& elem, bool areSubelemsRelevant) const;
	PRMU::EntryComponent::Type GetTypeWithoutCache (const EDB::GeneralElemConstRef &mainElem, const EDB::GeneralElemConstRef& elem, bool areSubelemsRelevant) const;

};

} // namespace PRMU

#endif	// MARKUPELEMEFFECT_HPP
