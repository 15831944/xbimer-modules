
// *********************************************************************************************************************
// Holds all the MarkupEntries
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPENTRYSET_HPP)
#define MARKUPENTRYSET_HPP
#endif

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// from ObjectDatabase
#include "ODBReference.hpp"

// from TWRoot
#include "TWObject.hpp"

// from VBElements
#include "ProjectTypes.hpp"

// from GSRoot
#include "AutoPtr.hpp"
#include "BiHashTable.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace VBES {
class ElemSet;
}

namespace PRMU {
class IMarkupEditabilityChecker;
}

// --- Type definitions -------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT MarkupEntrySet : public TW::Object
{
	DECLARE_DYNAMIC_CLASS (MarkupEntrySet)
private:
	GS::Owner<PRMU::IMarkupEditabilityChecker> markupEditabilityChecker;
	MarkupEntrySet ();
	MarkupEntrySet (const MarkupEntrySet& source) = delete;

public:
	~MarkupEntrySet ();
	void				ConvertToOldMarkupStructure (const MarkupEntryRef& entryRef);

	static bool					ContainsMarkup (const MarkupEntrySetConstRef& markupEntrySet, const MarkupEntryConstRef& entry);
	static bool					ContainsAnyMarkup (const MarkupEntrySetConstRef& markupEntrySet);
	static bool					ContainsAnyMarkup (const EDB::ProjectConstRef& project);

	TagSetContainerConstRef		GetTagSetContainer () const;
	static TagSetContainerRef	GetTagSetContainer (const MarkupEntrySetRef& entrySet);

	static MarkupEntrySetConstRef	GetEntrySetByTagSet (const TagSetConstRef& tagSet);
	static MarkupEntrySetRef		GetEntrySetByTagSet (const TagSetRef& tagSet);

	static MarkupEntrySetConstRef	GetEntrySetByTagSetContainer (const TagSetContainerConstRef& tagSetContainer);
	static MarkupEntrySetRef		GetEntrySetByTagSetContainer (const TagSetContainerRef& tagSetContainer);

	MarkupEntryConstRefList			GetEntries						(void) const;
	static MarkupEntryRefList		GetEntries						(const MarkupEntrySetRef& entrySet);
	static MarkupEntryConstRefList	GetChildrenOfEntry				(const MarkupEntryConstRef& entry);

	void							DeleteAllMarkups				(void);

	USize							GetMarkupEntriesCount			(void) const;

	void							ConnectToProject				(const EDB::ProjectRef& project);

	const IMarkupEditabilityChecker* GetMarkupEditabilityChecker	(void) const;
	void							 SetMarkupEditabilityChecker	(PRMU::IMarkupEditabilityChecker* checker);

	void										SetDiff3DElemIdToCurrentModelElemIdMap (const GS::BiHashTable<ODB::Id, ODB::Id>& idMapTable);
	void										UpdateExistingKeysInDiff3DElemIdToCurrentModelElemIdMap (const GS::HashTable<ODB::Id, ODB::Id>& idMapTable);
	void										PutDiff3DElemIdToCurrentModelElemIdMap (const GS::HashTable<ODB::Id, ODB::Id>& idMapTable);
	const GS::BiHashTable<ODB::Id, ODB::Id>&	GetDiff3DElemIdToCurrentModelElemIdMap () const;

	bool										IsAnyEntryTurnedOn () const;

	static void						InsertMarkup (const MarkupEntrySetRef& markupEntryset, const MarkupEntryRef& entryRef);
	static void						RemoveMarkup (const MarkupEntrySetRef& markupEntryset, const MarkupEntryRef& entryRef);

	static	MarkupEntrySetConstRef	Get (const EDB::ProjectConstRef& project);
	static	MarkupEntrySetRef		Get (const EDB::ProjectRef& project);

	static	MarkupEntrySetConstRef	GetEntrySet (const MarkupEntryConstRef& entry);
	static	MarkupEntrySetRef		GetEntrySet (const MarkupEntryRef& entry);

	static	EDB::ProjectConstRef	GetProject (const MarkupEntrySetConstRef& entrySet);
	static	EDB::ProjectRef			GetProject (const MarkupEntrySetRef& entrySet);


	static	void				CreateMarkupEntrySetRootInProject (const EDB::ProjectRef& project);
	static	MarkupEntrySetRef	FindMarkupEntrySetRoot (const EDB::ProjectRef& project);
	static	MarkupEntrySetRef	CreateMarkupEntrySetRoot (const EDB::ProjectRef& project);
};
}	//namespace PRMU