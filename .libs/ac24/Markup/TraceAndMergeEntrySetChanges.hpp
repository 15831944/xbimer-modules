// *********************************************************************************************************************
// Description:		MergeEntrySetChangesCommand class
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef MERGEENTRYSETCHANGESCOMMAND_HPP
#define MERGEENTRYSETCHANGESCOMMAND_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// from GSRoot
#include "ClassInfo.hpp"

// from ODB
#include "ODBMD5DifferenceGenerator.hpp"
#include "ODBIdSpace.hpp"

// --- Type definitions --------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT TraceAndMergeEntrySetChanges {
public:
	class MARKUP_DLL_EXPORT IdSpaceContentEnumerator : public ODB::MD5DifferenceGenerator::ObjectSet {
	private:
		ODB::IdSpace* idSpace;
	public:
		explicit IdSpaceContentEnumerator (ODB::IdSpace* idSpace);

		virtual void	EnumerateObjects (ODB::MD5DifferenceGenerator::ObjectSet::ConstObjectEnumerator* enumerator) const override;
	};

protected:
	ODB::IdSpace*			temporaryIdSpace;
	MarkupEntrySetConstRef	originalEntrySet;
	MarkupEntrySetRef		temporaryEntrySet;
	MarkupEntryRefList		entryListToCopy;

	ODB::MD5DifferenceGenerator*	differenceGenerator;
	IdSpaceContentEnumerator*		idSpaceContentEnumerator;


protected:

	TraceAndMergeEntrySetChanges (void);
	explicit TraceAndMergeEntrySetChanges (const TraceAndMergeEntrySetChanges& source);

	GS::ErrorStatus FillAndTraceNewIdSpace (void);

public:
	TraceAndMergeEntrySetChanges			(const PRMU::MarkupEntrySetConstRef& originalEntrySet, 
											 PRMU::MarkupEntryRefList			 entryList);

	virtual ~TraceAndMergeEntrySetChanges	(void);

	GS::ErrorStatus		MergeEntrySetChanges	(void);
	MarkupEntrySetRef	GetTemporaryEntrySet	(void) const;
	void				GetCurrentChanges		(ODB::Delta* delta_out) const;
};
} // PRMU namespace

#endif
