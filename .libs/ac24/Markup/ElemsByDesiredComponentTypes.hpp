// *********************************************************************************************************************
// Markup Interfaces
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef ELEMSBYDESIREDCOMPONENTTYPES_HPP
#define ELEMSBYDESIREDCOMPONENTTYPES_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// from GSRoot
#include "HashTable.hpp"

// from VBElements
#include "GeneralElem.hpp"


// --- predeclarations ---------------------------------------------------------------------------

namespace EDB {
typedef ODB::Ref<EDB::GeneralElem> GeneralElemRef;
typedef ODB::RefList<EDB::GeneralElem> GeneralElemRefList;
typedef ODB::ConstRefList<EDB::GeneralElem> GeneralElemConstRefList;
// 
class Project;
typedef ODB::ConstRef<EDB::Project> ProjectConstRef;
}

namespace PRMU {

struct MARKUP_DLL_EXPORT ElementsFromDiff3DByComponentTypes {
	GS::HashTable<EDB::ProjectConstRef, EDB::GeneralElemConstRefList> creationsTable;
	GS::HashTable<EDB::ProjectConstRef, EDB::GeneralElemConstRefList> modificationsTable;
	EDB::GeneralElemConstRefList deletions;
	EDB::GeneralElemConstRefList highlights;

	ElementsFromDiff3DByComponentTypes (const GS::HashTable<EDB::ProjectConstRef, EDB::GeneralElemConstRefList>& creationsTable,
										const GS::HashTable<EDB::ProjectConstRef, EDB::GeneralElemConstRefList>& modificationsTable,
										const EDB::GeneralElemConstRefList& deletions,
										const EDB::GeneralElemConstRefList& highlights);
	ElementsFromDiff3DByComponentTypes ();

	bool IsEmpty () const;
	USize GetSize () const;
	void AppendWithoutDuplicates (const ElementsFromDiff3DByComponentTypes& source);

private:
	bool ContainsId (const EDB::GeneralElemConstRefList& list, const ODB::Id& id);
	bool ContainsId (const GS::HashTable<EDB::ProjectConstRef, EDB::GeneralElemConstRefList>& table, const ODB::Id& id);
};


struct MARKUP_DLL_EXPORT InPlanElementsByDesiredComponentTypes {
	EDB::GeneralElemRefList highlights;
	EDB::GeneralElemRefList creations;
	EDB::GeneralElemRefList deletions;
	GS::Array<GS::Pair<EDB::GeneralElemRef, EDB::GeneralElemRef>> modifications;

	InPlanElementsByDesiredComponentTypes (const EDB::GeneralElemRefList& highlights,
										   const EDB::GeneralElemRefList& creations,
										   const EDB::GeneralElemRefList& deletions,
										   const GS::Array<GS::Pair<EDB::GeneralElemRef, EDB::GeneralElemRef>>& modifications);
	InPlanElementsByDesiredComponentTypes (const InPlanElementsByDesiredComponentTypes& source);
	InPlanElementsByDesiredComponentTypes ();

	bool IsEmpty () const;
	void Clear ();
	void AppendWithoutDuplicates (const InPlanElementsByDesiredComponentTypes& source);
};

} // namespace PRMU
#endif