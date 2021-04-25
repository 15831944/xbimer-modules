// *********************************************************************************************************************
// Description:		DeleteEntryViewFromEntryCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef DELETEENTRYVIEWFROMENTRYCOMMAND_HPP
#define DELETEENTRYVIEWFROMENTRYCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "EntryView.hpp"
#include "MarkupEntry.hpp"
#include "MarkupCommandBase.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT DeleteEntryViewFromEntryCommand : public MarkupCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (DeleteEntryViewFromEntryCommand)

private:
	PRMU::EntryViewRefList			entryViews;
	PRMU::MarkupEntryRef			entry;

private:
	DeleteEntryViewFromEntryCommand ();
	DeleteEntryViewFromEntryCommand (const DeleteEntryViewFromEntryCommand& source); //disabled
	DeleteEntryViewFromEntryCommand& operator= (const DeleteEntryViewFromEntryCommand& source); //disabled

public:
	DeleteEntryViewFromEntryCommand (const IMarkupEditabilityChecker* checker, 
									 PRMU::MarkupEntryRef entry,
									 PRMU::EntryViewRefList entryViews);

	virtual GS::ErrorStatus ExecuteInternal (void) override;

	virtual GS::ErrorStatus RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;
};

}

#endif