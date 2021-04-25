// *********************************************************************************************************************
// Utilities for Markup related commands
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef MARKUPCOMMANDSUTILS_HPP
#define MARKUPCOMMANDSUTILS_HPP

#pragma once

// from Markup
#include "ComponentChecker.hpp"
#include "EntryComponent.hpp"
#include "MarkupEntrySet.hpp"
#include "MarkupExport.hpp"
#include "MarkupInterfaces.hpp"
#include "ElemsByDesiredComponentTypes.hpp"
#include "MarkupTypes.hpp"
#include "Suggestion.hpp"

// from VBElements
#include "EDBGeneralDefinitions.hpp"

// from GSRoot
#include "Array.hpp"
#include "Pair.hpp"
#include "AutoPtr.hpp"

// from TWRoot
#include "TWPermissionIDs.h"

// from ODB
#include "ODBDelta.hpp"

namespace VBES {
class ElemSet;
typedef ODB::Ref<ElemSet> ElemSetRef;
}

namespace ADB {
class AttributeIndex;
}

namespace PN {
class CaptureInterface;
class CaptureData;
typedef ODB::Ref<CaptureData> CaptureDataRef;
}

namespace PRMU {
struct TWUserParams;
}

namespace GS {
class Guid;
}

namespace PRMU {

MARKUP_DLL_EXPORT void SetMarkupDBModiTime (VBES::ElemSetRef elemSet, bool modifyModel = true);

MARKUP_DLL_EXPORT bool TWUserHasRights (const TWUserParams* twUserParams, const GS::Array<TWCB::PermissionID>& necessaryPermissions, short userId = 0);

MARKUP_DLL_EXPORT GS::Array<TWCB::PermissionID> GetIssueOperationsPermissions (GS::Array<IssueRelatedOperation> operation);

MARKUP_DLL_EXPORT GS::Array<TWCB::PermissionID> GetIssueOperationPermissions (IssueRelatedOperation operation);


class MARKUP_DLL_EXPORT IElemAdder
{
public:
	virtual ~IElemAdder ();

	virtual bool AddElemToEntry (PRMU::MarkupEntryConstRef entry,
								 EDB::GeneralElemRefList elemList,
								 const PRMU::EntryComponent::Type& compType,
								 PRMU::EntryViewConstRef entryView = nullptr) = 0;
};


MARKUP_DLL_EXPORT PRMU::EntryComponent::Type GetDiff3DElementType (const EDB::GeneralElemConstRef& elem,
																   GetDiff3DElemExistenceAndStateInfoFunctionPtr GetGeometricalSourceChange,
																   PRMU::MarkupEntrySetConstRef entrySet);


MARKUP_DLL_EXPORT PRMU::MarkupEntryRefList FilterEntriesByRequestedTWOperationForUser (const PRMU::MarkupEntryTWOperations& requestedOperation, const PRMU::MarkupEntryRefList& entries, const short& userId);


MARKUP_DLL_EXPORT bool CanAcceptEntryComponent (const PRMU::EntryComponentConstRef&	   component,
												const PRMU::IMarkupEditabilityChecker* markupEditabilityChecker,
												const bool							   checkOwnerUser = true);

MARKUP_DLL_EXPORT PRMU::InPlanElementsByDesiredComponentTypes MakeListOfInPlanElementsByDesiredComponentTypes (const EDB::GeneralElemRefList& elemList,
																											   const PRMU::EntryComponent::Type& type,
																											   GS::Array<GS::Pair<EDB::GeneralElemRef, EDB::GeneralElemRef>> modifications = {});

MARKUP_DLL_EXPORT PRMU::ElementsFromDiff3DByComponentTypes	MakeDiff3DElementListByComponentTypes (EDB::GeneralElemConstRefList mixedTypeElemList,
																								   GetDiff3DElemExistenceAndStateInfoFunctionPtr GetDiff3DElemExistenceAndStateInfo,
																								   PRMU::MarkupEntrySetConstRef entrySet);

MARKUP_DLL_EXPORT PRMU::ElementsFromDiff3DByComponentTypes MakeDiff3DElementListByComponentTypesWithGivenComponentType (EDB::GeneralElemConstRefList elemList,
																														PRMU::EntryComponent::Type type,
																														PRMU::MarkupEntrySetConstRef entrySet);

MARKUP_DLL_EXPORT EDB::GeneralElemRef	AttachElementAsNewToEntry (PRMU::MarkupEntryRef entry,
																   const EDB::GeneralElemRef& elem);

MARKUP_DLL_EXPORT void DetachElementsFromEntry (PRMU::MarkupEntryRef entry,
												EDB::GeneralElemRefList elems,
												const PRMU::IMarkupEditabilityChecker* markupEditabilityChecker);

MARKUP_DLL_EXPORT void DetachAndDeleteOutOfModelElementsFromEntry (PRMU::MarkupEntryRef entry, EDB::GeneralElemRefList elems,
																   const PRMU::IMarkupEditabilityChecker* markupEditabilityChecker);

void DeleteEntries (PRMU::MarkupEntryRefList entries);

MARKUP_DLL_EXPORT GS::ErrCode AcceptMarkupEntrySuggestions (const SuggestionRefList& suggestions,
															const GS::HashSet<Suggestion::AcceptType>& acceptType,
															const PRMU::IMarkupEditabilityChecker* markupEditabilityChecker,
															const IAcceptedIssueElemPreparator* issueElemPreparator = nullptr,
															bool reAttachElemsAsHighlight = true);

MARKUP_DLL_EXPORT void LinkAndRedefineEntryView (PRMU::MarkupEntryRef currentMarkup,
												 PRMU::EntryViewRef view,
												 PN::CaptureInterface* captureInterface,
												 const PN::CaptureDataRef& captureDataToBeCopied = nullptr);


MARKUP_DLL_EXPORT void AddElementsToEntryOnEditing (const EDB::GeneralElemRef& originalElem,
													const EDB::GeneralElemRef& newElem,
													const PRMU::EntryComponent::Type& type);

MARKUP_DLL_EXPORT void ReattachDeletionElemsAfterMorphConversion (GS::HashTable<EDB::GeneralElemRef, EDB::GeneralElemConstRef> correspondingElemsToNewElems);

}
#endif