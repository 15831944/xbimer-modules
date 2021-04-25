// *********************************************************************************************************************
// Suggestion, that holds elements to be deleted
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (DELETEDSUGGESTION_HPP)
#define DELETEDSUGGESTION_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "Suggestion.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------
// --- Type definitions	------------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT SuggestionForDeletion : public Suggestion
{
	DECLARE_DYNAMIC_CLASS (SuggestionForDeletion)
private:
	SuggestionForDeletion ();
	SuggestionForDeletion (const SuggestionForDeletion& source);

public:
	SuggestionForDeletion (EDB::GeneralElemRef elem);

	virtual ~SuggestionForDeletion () = default;
	
	virtual SuggestionForDeletion*			Clone () const override;

	virtual EDB::GeneralElemRef				Accept (const GS::HashSet<Suggestion::AcceptType>& type, GS::HashTable<ODB::Id, ODB::Id>& idMapTable) override;

	EDB::GeneralElemConstRef				GetElementInModel () const override;
	EDB::GeneralElemRef						GetElementInModel () override;
	PRMU::EntryComponent::Type	GetElemType (const EDB::GeneralElemConstRef& elem) const override;
	static EntryComponentConstRefList		GetComponent (EDB::GeneralElemConstRef elem);

	virtual bool							IsRelatedElement (const EDB::GeneralElemConstRef &elem) const override;

	static bool								IsRelatedElementStatic (const EDB::GeneralElemConstRef& elem);
};

} // namespace PRMU

#endif