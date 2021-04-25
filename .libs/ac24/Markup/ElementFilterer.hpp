// *********************************************************************************************************************
// Description:		Element Filterer
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	BFA
// *********************************************************************************************************************

#ifndef ELEMENTFILTERER_HPP
#define ELEMENTFILTERER_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "MarkupInterfaces.hpp"
#include "ElemsByDesiredComponentTypes.hpp"
#include "EntryComponent.hpp"
#include "ComponentChecker.hpp"

namespace EDB {
class Project;
typedef ODB::Ref<Project> ProjectRef;
}

namespace PRMU {

class MARKUP_DLL_EXPORT ElementFilterer {
public:
	static void FilterElementsThatCanBeAddedToNewEntry (PRMU::ElementsFromDiff3DByComponentTypes& elementsFromDiff3DByComponentTypes,
														PRMU::ComponentChecker& componentChecker);

	static void FilterElementsThatCanBeAddedToNewView (PRMU::MarkupEntryConstRef entry,
													   PRMU::ElementsFromDiff3DByComponentTypes& elementsFromDiff3DByComponentTypes,
													   PRMU::InPlanElementsByDesiredComponentTypes& inPlanElementsByDesiredComponentTypesToLinkOnly,
													   PRMU::ComponentChecker& componentChecker);

	static void FilterElementsThatCanBeAddedToEntry (PRMU::MarkupEntryRef entry,
													 PRMU::ElementsFromDiff3DByComponentTypes& elementsFromDiff3DByComponentTypes,
													 PRMU::ComponentChecker& componentChecker);
};

}

#endif