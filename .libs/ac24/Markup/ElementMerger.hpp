// *********************************************************************************************************************
// Description:		Element Merger
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	BFA, FEs
// *********************************************************************************************************************

#ifndef ELEMENTMERGER_HPP
#define ELEMENTMERGER_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "MarkupInterfaces.hpp"
#include "EntryComponent.hpp"
#include "MarkupCommandsUtils.hpp"
#include "ElementDuplicator.hpp"

namespace EDB {
class Project;
typedef ODB::Ref<Project> ProjectRef;
}

namespace PRMU {

class MARKUP_DLL_EXPORT ElementMerger {
private:
	static GS::ErrorStatus  MergeIfNecessary (EDB::ProjectRef						targetProject,
											  const EDB::GeneralElemConstRefList&	elemsToMerge,
											  EDB::GeneralElemRefList&				mergedElems,
											  PRMU::ElemDuplicator*					elemDuplicator);

	static GS::ErrorStatus MergeIfNecessary (EDB::ProjectRef												targetProject,
											 const EDB::GeneralElemConstRefList&							elemsToMerge,
											 GS::Array<GS::Pair<EDB::GeneralElemRef, EDB::GeneralElemRef>>&	mergedModificationElems,
											 PRMU::ElemDuplicator*											elemDuplicator);
public:
	ElementMerger () {}
	static GS::ErrorStatus	MergeDiff3DElements (EDB::ProjectRef&										targetProject,
												 const ElementsFromDiff3DByComponentTypes&				elementsFromDiff3DByComponentTypes,
												 InPlanElementsByDesiredComponentTypes&					inPlanElementsByDesiredComponentTypes,
												 ElemDuplicator*										elemDuplicator);
};

}

#endif