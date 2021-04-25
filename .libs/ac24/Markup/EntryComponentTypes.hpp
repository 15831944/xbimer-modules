// *********************************************************************************************************************
// Contains every type of EntryComponent
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ENTRYCOMPONENTTYPES_HPP)
#define ENTRYCOMPONENTTYPES_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "MarkupExport.hpp"

// from ObjectDatabase
#include "ODBRefList.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PRMU {
class EntryComponent;
typedef ODB::Ref<EntryComponent>			EntryComponentRef;
typedef ODB::ConstRef<EntryComponent>		EntryComponentConstRef;
typedef ODB::RefList<EntryComponent>		EntryComponentRefList;
typedef ODB::ConstRefList<EntryComponent>	EntryComponentConstRefList;

class Suggestion;
typedef ODB::Ref<Suggestion>				SuggestionRef;
typedef ODB::ConstRef<Suggestion>			SuggestionConstRef;
typedef ODB::RefList<Suggestion>			SuggestionRefList;
typedef ODB::ConstRefList<Suggestion>		SuggestionConstRefList;


class SuggestionForModification;
typedef ODB::Ref<SuggestionForModification>				SuggestionForModificationRef;
typedef ODB::ConstRef<SuggestionForModification>		SuggestionForModificationConstRef;
typedef ODB::RefList<SuggestionForModification>			SuggestionForModificationRefList;
typedef ODB::ConstRefList<SuggestionForModification>	SuggestionForModificationConstRefList;

class SuggestionForModificationSubelem;
typedef ODB::Ref<SuggestionForModificationSubelem>			SuggestionForModificationSubelemRef;
typedef ODB::ConstRef<SuggestionForModificationSubelem>		SuggestionForModificationSubelemConstRef;
typedef ODB::RefList<SuggestionForModificationSubelem>		SuggestionForModificationSubelemRefList;
typedef ODB::ConstRefList<SuggestionForModificationSubelem>	SuggestionForModificationSubelemConstRefList;

class SuggestionForDeletion;
typedef ODB::Ref<SuggestionForDeletion>				SuggestionForDeletionRef;
typedef ODB::ConstRef<SuggestionForDeletion>		SuggestionForDeletionConstRef;
typedef ODB::RefList<SuggestionForDeletion>			SuggestionForDeletionRefList;
typedef ODB::ConstRefList<SuggestionForDeletion>	SuggestionForDeletionConstRefList;

class SuggestionForCreation;
typedef ODB::Ref<SuggestionForCreation>					SuggestionForCreationRef;
typedef ODB::ConstRef<SuggestionForCreation>			SuggestionForCreationConstRef;
typedef ODB::RefList<SuggestionForCreation>				SuggestionForCreationRefList;
typedef ODB::ConstRefList<SuggestionForCreation>		SuggestionForCreationConstRefList;

class Highlight;
typedef ODB::Ref<Highlight>						HighlightRef;
typedef ODB::ConstRef<Highlight>				HighlightConstRef;
typedef ODB::RefList<Highlight>					HighlightRefList;
typedef ODB::ConstRefList<Highlight>			HighlightConstRefList;

class Remark;
typedef ODB::Ref<Remark>						RemarkRef;
typedef ODB::ConstRef<Remark>					RemarkConstRef;
typedef ODB::RefList<Remark>					RemarkRefList;
typedef ODB::ConstRefList<Remark>				RemarkConstRefList;

} // namespace PRMU

#endif