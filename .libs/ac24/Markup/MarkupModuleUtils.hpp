// *********************************************************************************************************************
// Utilities to operate on Markup data structure and serve dialog needs
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef MARKUPMODULEUTILS_HPP
#define MARKUPMODULEUTILS_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "MarkupCommandsUtils.hpp"
#include "MarkupInterfaces.hpp"

// from GSRoot
#include "Array.hpp"
#include "ClassInfo.hpp"
#include "GSGuid.hpp"
#include "UniString.hpp"

// from ProjectNavigator
#include "CaptureData.hpp"

// from VBElements
#include "EDBGeneralDefinitions.hpp"

// from TWClient
#include "TWClient/Mailbox/UserContact.hpp"
#include "Definitions.hpp"

#include "IOUtilities.hpp"
#include <functional>

// --- Predeclarations --------------------------------------------------------------------------------------------------

namespace EDB {
class Project;
typedef ODB::Ref<Project> ProjectRef;
}

namespace GS {
class EventReceiver;
}

namespace PRMU {

// --- EntryView utilities ----------------------------------------------------------------------------------------------

GSErrCode MARKUP_DLL_EXPORT CaptureScreenAndConnectToEntryView (EntryViewRef view, PN::CaptureInterface* captureInterface);


GS::ErrCode MARKUP_DLL_EXPORT GenerateNumberedUniqueNames (const GS::UniString&			  baseName,
														   const GS::Array<GS::UniString> referenceNames,
														   GS::Array<GS::UniString>&	  newNames,
														   const USize					  numeberOfNewNames);

// --- Generate New Entry and New Scene auto numbered name --------------------------------------------------------------

template <class T>
void GetNames (GS::Array<GS::UniString>& nameList, ODB::ConstRefList<T> objectList)
{
	nameList.Clear ();
	for (auto item : objectList) {
		nameList.Push (item->GetName ());
	}
}

template <class T>
GS::UniString GenerateNewName (const GS::UniString& suggestedName, ODB::ConstRefList<T> objectList)
{
	GS::Array<GS::UniString> nameList;
	GetNames<T> (nameList, objectList);
	return IOUtil::GenerateNumberedUniqueName (suggestedName, 255, IOUtil::MakeUniqueAtEnd, [&] (const GS::UniString& name) {
		return !nameList.Contains (name);
	});
}

template <typename TNameHolder>
GS::ErrCode GenerateNewNames (const GS::UniString& baseName, ODB::ConstRefList<TNameHolder> nameHolders, GS::Array<GS::UniString>& newNames, USize numberToCreate)
{
	GS::Array<GS::UniString> existingNames;
	GetNames<TNameHolder> (existingNames, nameHolders);

	DBASSERT (existingNames.GetSize () == nameHolders.GetSize ());

	return GenerateNumberedUniqueNames (baseName, existingNames, newNames, numberToCreate);
}

// --- Get Entries Based On Guid ----------------------------------------------------------------------------------------

MarkupEntryConstRefList MARKUP_DLL_EXPORT MakeEntryListFromGuids (const GS::Array<GS::Guid> elemsGuids, MarkupEntrySetConstRef entrySet);
MarkupEntryConstRef MARKUP_DLL_EXPORT GetMarkupEntryByGuid (const GS::Guid entryGuid, MarkupEntrySetConstRef entrySet);


// ----------------------------------------------------------------------------------------------------------------------

GS::ErrorStatus MARKUP_DLL_EXPORT CopyEntriesAndRelatedObjectsIntoTemporaryIdSpace (const PRMU::MarkupEntryRefList& entryList, const MarkupEntrySetConstRef& entrySet, ODB::IdSpace* tempIdSpace);

// History Entry Change Processor - Accept Elements and Edit AssignInfo properties

MARKUP_DLL_EXPORT extern const GS::CustomClassProperty	AcceptSuggestionProperty;
MARKUP_DLL_EXPORT extern const GS::CustomClassPropertyValueStatic	AcceptSuggestionsCommand;

MARKUP_DLL_EXPORT extern const GS::CustomClassProperty	EditEntryProperty;
MARKUP_DLL_EXPORT extern const GS::CustomClassPropertyValueStatic	EditEntryCommand;


}
#endif