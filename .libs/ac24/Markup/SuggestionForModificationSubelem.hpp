// *********************************************************************************************************************
// Suggestion, that holds elements to be modified
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MODIFIEDSUGGESTIONSUBELEM_HPP)
#define MODIFIEDSUGGESTIONSUBELEM_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "Suggestion.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------
// --- Type definitions	------------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT SuggestionForModificationSubelem : public Suggestion
{
	DECLARE_DYNAMIC_CLASS (SuggestionForModificationSubelem)
private:
	SuggestionForModificationSubelem ();
	SuggestionForModificationSubelem (const SuggestionForModificationSubelem& source);
public:
	virtual ~SuggestionForModificationSubelem () = default;
	virtual SuggestionForModificationSubelem*		Clone () const override;

	virtual EDB::GeneralElemRef				Accept (const GS::HashSet<Suggestion::AcceptType>& type, GS::HashTable<ODB::Id, ODB::Id>& idMapTable) override;

	EDB::GeneralElemConstRef				GetElementInModel () const override;
	EDB::GeneralElemRef						GetElementInModel () override;
	EDB::GeneralElemConstRef				GetElementOutOfModel () const override;
	EDB::GeneralElemRef						GetElementOutOfModel () override;

	static EntryComponentConstRefList		GetComponent (const EDB::GeneralElemConstRef& elem);
	static EntryComponentConstRefList		GetComponentInModel (const EDB::GeneralElemConstRef& elem);
	static EntryComponentConstRefList		GetComponentOutOfModel (const EDB::GeneralElemConstRef& elem);

	static EntryComponentRefList			GetComponent			(const EDB::GeneralElemRef& elem);
	static EntryComponentRefList			GetComponentInModel		(const EDB::GeneralElemRef& elem);
	static EntryComponentRefList			GetComponentOutOfModel	(const EDB::GeneralElemRef& elem);

	PRMU::EntryComponent::Type	GetElemType (const EDB::GeneralElemConstRef& elem) const override;

	static ODB::Ref<SuggestionForModificationSubelem>	Create (const EDB::GeneralElemRef& elemInModel, const EDB::GeneralElemRef& elemOutOfModel);

	virtual void							ConvertToAC22 () override;

	virtual bool							IsRelatedElement (const EDB::GeneralElemConstRef &elem) const override;

	static bool								IsRelatedElementStatic (const EDB::GeneralElemConstRef& elem);
};

} // namespace PRMU

#endif