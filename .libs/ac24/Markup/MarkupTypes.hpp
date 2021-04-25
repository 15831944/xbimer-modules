// *********************************************************************************************************************
// MarkupTypes: Contains every class name and typedef of MarkupModule
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPTYPES_HPP)
#define MARKUPTYPES_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "MarkupExport.hpp"

// from ObjectDatabase
#include "ODBRefList.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PRMUAC22 {
class	AssignInfo;
typedef ODB::Ref<AssignInfo>					AssignInfoRef;
typedef ODB::ConstRef<AssignInfo>				AssignInfoConstRef;
}

namespace PRMU {

class	EntryComment;
typedef ODB::Ref<PRMU::EntryComment>			EntryCommentRef;
typedef ODB::ConstRef<PRMU::EntryComment>		EntryCommentConstRef;
typedef ODB::RefList<EntryComment>				EntryCommentRefList;
typedef ODB::ConstRefList<EntryComment>			EntryCommentConstRefList;

class	EntryRemark;
typedef ODB::Ref<EntryRemark>					EntryRemarkRef;
typedef ODB::ConstRef<EntryRemark>				EntryRemarkConstRef;

class	EntryView;
typedef ODB::Ref<EntryView>						EntryViewRef;
typedef ODB::ConstRef<EntryView>				EntryViewConstRef;
typedef ODB::RefList<EntryView>					EntryViewRefList;
typedef ODB::ConstRefList<EntryView>			EntryViewConstRefList;

class	MarkupClientConversionData;

class	MarkupEntry;
typedef ODB::Ref<MarkupEntry>					MarkupEntryRef;
typedef ODB::ConstRef<MarkupEntry>				MarkupEntryConstRef;
typedef ODB::RefList<MarkupEntry>				MarkupEntryRefList;
typedef ODB::ConstRefList<MarkupEntry>			MarkupEntryConstRefList;

class	MarkupEntryClientData;
typedef ODB::Ref<MarkupEntryClientData>			MarkupEntryClientDataRef;
typedef ODB::ConstRef<MarkupEntryClientData>	MarkupEntryClientDataConstRef;

class	MarkupEntrySet;
typedef ODB::Ref<MarkupEntrySet>				MarkupEntrySetRef;
typedef ODB::ConstRef<MarkupEntrySet>			MarkupEntrySetConstRef;

class	NewEntryParams;

class	TagSet;
typedef ODB::Ref<TagSet>					TagSetRef;
typedef ODB::ConstRef<TagSet>				TagSetConstRef;
typedef ODB::RefList<TagSet>				TagSetRefList;
typedef ODB::ConstRefList<TagSet>			TagSetConstRefList;

class	TagValue;
typedef ODB::Ref<TagValue>				TagValueRef;
typedef ODB::ConstRef<TagValue>			TagValueConstRef;
typedef ODB::RefList<TagValue>			TagValueRefList;
typedef ODB::ConstRefList<TagValue>		TagValueConstRefList;

class	TagSetContainer;
typedef ODB::Ref<TagSetContainer>		TagSetContainerRef;
typedef ODB::ConstRef<TagSetContainer>	TagSetContainerConstRef;

class HistoryEntry;
typedef ODB::Ref<HistoryEntry> HistoryEntryRef;
typedef ODB::ConstRef<HistoryEntry> HistoryEntryConstRef;
typedef ODB::RefList<HistoryEntry> HistoryEntryRefList;
typedef ODB::ConstRefList<HistoryEntry> HistoryEntryConstRefList;

}
#endif