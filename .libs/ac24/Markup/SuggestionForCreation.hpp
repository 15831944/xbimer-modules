// *********************************************************************************************************************
// Suggestion, that holds elements to be created
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (NEWSUGGESTION_HPP)
#define NEWSUGGESTION_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "Suggestion.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------
// --- Type definitions	------------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT SuggestionForCreation : public Suggestion
{
	DECLARE_DYNAMIC_CLASS (SuggestionForCreation)
public:
	SuggestionForCreation ();
	SuggestionForCreation (EDB::GeneralElemRef newElem);
	SuggestionForCreation (const SuggestionForCreation& source);

	virtual ~SuggestionForCreation () = default;

	virtual SuggestionForCreation*			Clone () const override;

	virtual EDB::GeneralElemRef				Accept (const GS::HashSet<Suggestion::AcceptType>& type, GS::HashTable<ODB::Id, ODB::Id>& idMapTable) override;

	EDB::GeneralElemConstRef				GetElementOutOfModel () const override;
	EDB::GeneralElemRef						GetElementOutOfModel () override;

	PRMU::EntryComponent::Type	GetElemType (const EDB::GeneralElemConstRef& elem) const override;
	static EntryComponentConstRefList		GetComponent (const EDB::GeneralElemConstRef& elem);

	static GS::ErrorStatus					CopyElem (EDB::GeneralElemRef originalElem, EDB::GeneralElemRef& newElem, GS::HashTable<ODB::Id, ODB::Id>& idMapTable);

	virtual void							ConvertToAC22 () override;

	virtual bool							IsRelatedElement (const EDB::GeneralElemConstRef &elem) const override;

	static bool								IsRelatedElementStatic (const EDB::GeneralElemConstRef& elem);
};

} // namespace PRMU

#endif