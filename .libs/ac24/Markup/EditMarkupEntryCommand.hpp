// *********************************************************************************************************************
// Description:		EditMarkupEntryCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef MARKUPENTRYCOMMAND_HPP
#define MARKUPENTRYCOMMAND_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

// from Markup
#include "MarkupEntry.hpp"
#include "MarkupCommandBase.hpp"
#include "TraceAndMergeEntrySetChanges.hpp"

// from GSRoot
#include "ClassInfo.hpp"

// from ODB
#include "ODBMD5DifferenceGenerator.hpp"
#include "ODBIdSpace.hpp"


// --- Type definitions --------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT EditMarkupEntryCommand : public MarkupCommandBase,
												 public TraceAndMergeEntrySetChanges
{
	DECLARE_DYNAMIC_CLASS_INFO (EditMarkupEntryCommand)

private:
	GS::Array<PRMU::MarkupEntryRef>	entries;
	
protected:
	EditMarkupEntryCommand ();
	EditMarkupEntryCommand (const EditMarkupEntryCommand& source);

private:
	EditMarkupEntryCommand& operator= (const EditMarkupEntryCommand& source); //disabled
	
public:
	EditMarkupEntryCommand (const IMarkupEditabilityChecker* checker, 
							const PRMU::MarkupEntrySetConstRef&	originalEntrySet,
							PRMU::MarkupEntryRefList&			entries,
							PRMU::IssueRelatedOperation			operation);

	~EditMarkupEntryCommand ();

	virtual	GS::ErrorStatus	ExecuteInternal (void) override;

	virtual GS::ErrorStatus RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;
};

} // PRMU namespace

#endif