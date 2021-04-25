// *********************************************************************************************************************
// Base class for Suggestion types
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (SUGGESTION_HPP)
#define SUGGESTION_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "EntryComponent.hpp"
#include "EntryComponentTypes.hpp"

// from GSRoot
#include "HashSet.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------
// --- Type definitions	------------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT Suggestion : public EntryComponent
{
	DECLARE_ABSTRACT_DYNAMIC_CLASS(Suggestion)
protected:
	Suggestion (const ODB::DynamicClass* finalDynamicClass);

public:
	enum AcceptType {
		GeometryAndPositioning = 1,
		FloorPlanAndSection,
		Model,
		Layer,
		StructuralFunction,
		Renovation,
		ClassificationAndProperties,
		StructuralAnalyticalModel,
	};

	Suggestion ();

	virtual ~Suggestion ();

	virtual EDB::GeneralElemRef Accept (const GS::HashSet<AcceptType>& type, GS::HashTable<ODB::Id, ODB::Id>& idMapTable) = 0;

	static GS::HashSet<AcceptType> fullAcceptSet;

	static SuggestionRefList TransformComponentsToSuggestions (EntryComponentRefList components);
};

} // namespace PRMU

#endif