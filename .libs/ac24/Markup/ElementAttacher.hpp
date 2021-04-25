// *********************************************************************************************************************
// Description:		Element Attacher.
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FEs, BFA
// *********************************************************************************************************************

#ifndef ELEMENTATTACHER_HPP
#define ELEMENTATTACHER_HPP

#pragma once

// from Markup
#include "ComponentChecker.hpp"
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "MarkupInterfaces.hpp"
#include "ElemsByDesiredComponentTypes.hpp"
#include "EntryComponent.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT ElementAttacher {
private:
	static void AttachModificationsToEntry (PRMU::MarkupEntryRef&											entry,
											GS::Array<GS::Pair<EDB::GeneralElemRef, EDB::GeneralElemRef>>	modifications,
											const PRMU::ComponentChecker&									componentChecker,
											PRMU::EntryViewRef												entryView = nullptr);

	static void AttachElementsToEntry (MarkupEntryRef&					entry,
									   EDB::GeneralElemRefList			elems,
									   const EntryComponent::Type&		type,
									   const PRMU::ComponentChecker&	componentChecker,
									   PRMU::EntryViewRef				entryView = nullptr,
									   bool								keepExistingComponents = false,
									   bool								recreateNewElements = true);
public:
	ElementAttacher () {}

	static GS::ErrorStatus AttachInPlanElementsByDesiredComponentTypesToEntry (const PRMU::MarkupEntrySetConstRef& entrySet,
																			   PRMU::MarkupEntryRef entry,
																			   const InPlanElementsByDesiredComponentTypes& inPlanElementsByDesiredComponentTypes,
																			   PRMU::EntryViewRef entryView = nullptr,
																			   bool keepExistingComponents = false,
																			   bool recreateNewElements = true);
};

}

#endif