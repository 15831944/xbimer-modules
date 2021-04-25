// *********************************************************************************************************************
// Description:		Component Checker
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	BFA
// *********************************************************************************************************************

#ifndef COMPONENTCHECKER_HPP
#define COMPONENTCHECKER_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "MarkupInterfaces.hpp"
#include "EntryComponent.hpp"

namespace EDB {
class Project;
typedef ODB::Ref<Project> ProjectRef;
}

namespace PRMU {

class MARKUP_DLL_EXPORT ComponentChecker
{
	const bool										isDiff3DWindowOnTop;
	MarkupEntrySetConstRef							entrySet;
	GetDiff3DElemExistenceAndStateInfoFunctionPtr	GetGeometricalSourceChange;
	const bool										modelElementsCanBeAddedAsModification;
	const bool										onlyHighlightCanBeAdded;

private:
	bool IsElemLinkableToAnyMarkup (EDB::GeneralElemConstRef elem, short* testResult = nullptr) const;

	bool IsAssociatedElementsCompatible (const EDB::GeneralElemConstRef& elem) const;

	EDB::GeneralElemConstRef GetMergedOrExistingInProjectElem (const EDB::GeneralElemConstRef& elem) const;
	EDB::GeneralElemConstRef GetMergedElem (const EDB::GeneralElemConstRef& elem) const;
	EDB::GeneralElemConstRef GetExistingInProjectElem (const EDB::GeneralElemConstRef& elem) const;

	bool CanAddElemToEntryAsComponentElemType (const MarkupEntryConstRef& entry,
											   const EDB::GeneralElemConstRef& elem,
											   const EntryComponent::Type& asType,
											   bool allowSameType = false) const;

	bool CanAddElemToProjectFromDiff3DAsComponentType (const EDB::GeneralElemConstRef& elem,
													   const PRMU::EntryComponent::Type& asType) const;

	bool CanAddElemsToProjectFromDiff3DAsComponentType (const EDB::GeneralElemConstRefList& elems,
														const PRMU::EntryComponent::Type& asType) const;

	bool CheckComponentCompatibilityRulesForElemsAcrossEntries (const EDB::GeneralElemConstRefList& elems,
																const PRMU::EntryComponent::Type& asType,
																const PRMU::MarkupEntryConstRef& entry = nullptr) const;

public:
	ComponentChecker (MarkupEntrySetConstRef						entrySet,
					  const bool									isDiff3DWindowOnTop = false,
					  GetDiff3DElemExistenceAndStateInfoFunctionPtr	GetGeometricalSourceChange = nullptr,
					  const bool									modelElementsCanBeAddedAsModification = true,
					  const bool									onlyHighlightCanBeAdded = false);

	bool CanRemoveEntryComponents (PRMU::EntryComponentConstRefList entryComponent) const;

	bool CanAddElemsToEntryAsComponentElemType (const PRMU::MarkupEntryConstRef& entry,
												const EDB::GeneralElemConstRefList& elems,
												const PRMU::EntryComponent::Type& asType) const;

	bool CanAddElemsToEntry (const PRMU::MarkupEntryConstRef& entry,
							 const EDB::GeneralElemConstRefList& elems,
							 const PRMU::EntryComponent::Type& asType) const;

	bool CanLinkElemToEntryAsComponentType (const PRMU::MarkupEntryConstRef& entry,
											const EDB::GeneralElemConstRef& elem,
											const PRMU::EntryComponent::Type& asType) const;

	bool CanAddElemToNewEntryWithDefaultComponentType (const EDB::GeneralElemConstRef& elem) const;

	bool CanAddElemsToNewEntryWithDefaultComponentTypes (const EDB::GeneralElemConstRefList& elems) const;

	const PRMU::IMarkupEditabilityChecker* GetMarkupEditabilityChecker () const;
};

}

#endif