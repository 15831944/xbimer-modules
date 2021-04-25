// *********************************************************************************************************************
// Suggestion, that holds elements to be modified
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MODIFIEDSUGGESTION_HPP)
#define MODIFIEDSUGGESTION_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "Suggestion.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------
// --- Type definitions	------------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT SuggestionForModification : public Suggestion
{
	DECLARE_DYNAMIC_CLASS (SuggestionForModification)
private:
	SuggestionForModification ();
	SuggestionForModification (const SuggestionForModification& source);
public:
	virtual ~SuggestionForModification () = default;
	virtual SuggestionForModification*		Clone () const override;

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

	static ODB::Ref<SuggestionForModification>	Create (const EDB::GeneralElemRef& elemInModel, const EDB::GeneralElemRef& elemOutOfModel);

	virtual void							ConvertToAC22 () override;

	virtual bool							IsRelatedElement (const EDB::GeneralElemConstRef &elem) const override;

	static bool								IsRelatedElementStatic (const EDB::GeneralElemConstRef& elem);

	static const ODB::Id&					GetInModelAssociationId (void);
	static const ODB::Id&					GetOutOfModelAssociationId (void);
};

} // namespace PRMU

#endif