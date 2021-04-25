// *********************************************************************************************************************
//  Link TagValues To Entry Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef LINKTAGVALUESTOENTRYCOMMAND_HPP
#define LINKTAGVALUESTOENTRYCOMMAND_HPP

#pragma once

// from ODB
#include "MVCCommand.hpp"

// from Markup
#include "MarkupEntry.hpp"
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "TagValue.hpp"

// from GSRoot
#include "ClassInfo.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT LinkTagValuesToEntryCommand : public MVC::CommandImp {
	DECLARE_DYNAMIC_CLASS_INFO (LinkTagValuesToEntryCommand)

private:
	TagValueRefList	tagValues;
	MarkupEntryRefList		entries;

	LinkTagValuesToEntryCommand ();
	LinkTagValuesToEntryCommand (const LinkTagValuesToEntryCommand& source);
	LinkTagValuesToEntryCommand& operator= (const LinkTagValuesToEntryCommand& source);

public:
	LinkTagValuesToEntryCommand (TagValueRefList tagValues, MarkupEntryRefList entries);

	virtual GS::ErrorStatus Execute (void) override;
};

}


#endif