// *********************************************************************************************************************
// Description:		Element Duplicator.
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FEs
// *********************************************************************************************************************

#ifndef ELEMENTDUPLICATOR_HPP
#define ELEMENTDUPLICATOR_HPP

#pragma once

// from ElementManager
#include "ProjectTypes.hpp"
#include "GeneralElem.hpp"

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT ElemDuplicator
{
public:
	class MARKUP_DLL_EXPORT DuplicatedElemPreparator {
	public:
		virtual ~DuplicatedElemPreparator ();
	public:
		virtual GSErrCode PostProcessElement (const EDB::GeneralElemRef& duplicatedElem, const EDB::GeneralElemConstRef& sourceElem) = 0;
	};

protected:
	VBES::ElemSetRef						targetElemSet;
	EDB::GeneralElemConstRefList			elemsToDuplicate;
	GS::HashTable<ODB::Id, ODB::Id>			idMapTable;
	GS::Owner<DuplicatedElemPreparator>		duplicatedElemPreparator;

public:
	ElemDuplicator (VBES::ElemSetRef targetElemSet);
	virtual ~ElemDuplicator ();

	GSErrCode								Do										(void);

	void									SetElementsToDuplicate					(const EDB::GeneralElemConstRefList& elemsToDuplicate);
	EDB::GeneralElemRefList					GetMergedElements						(void) const;
	const GS::HashTable<ODB::Id, ODB::Id>&	GetIdMapTable							(void) const;

	void									SetDuplicatedElemPreparator				(GS::Owner<DuplicatedElemPreparator>&& newDuplicatedElemPreparator);

protected:
	virtual GSErrCode						DuplicateElemsAndMergeIntoTargetElemSet (const EDB::GeneralElemConstRefList& elems) = 0;
};

}

#endif