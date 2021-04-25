// *********************************************************************************************************************
// Change Visibility Of Entry Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef CHANGEMARKUPENTRYVISIBILITYCOMMAND_HPP
#define CHANGEMARKUPENTRYVISIBILITYCOMMAND_HPP

#pragma once


// from ODB
#include "MVCCommand.hpp"

// from Markup
#include "MarkupEntry.hpp"
#include "MarkupCommandsUtils.hpp"

// from GSRoot
#include "ClassInfo.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT ChangeMarkupEntryVisibilityCommand : public MVC::CommandImp {
	DECLARE_DYNAMIC_CLASS_INFO (ChangeMarkupEntryVisibilityCommand)

private:
	PRMU::MarkupEntryRefList entries;
	bool visible;
	
	ChangeMarkupEntryVisibilityCommand ();
	ChangeMarkupEntryVisibilityCommand (const ChangeMarkupEntryVisibilityCommand& source);
	ChangeMarkupEntryVisibilityCommand& operator= (const ChangeMarkupEntryVisibilityCommand& source);

public:
	ChangeMarkupEntryVisibilityCommand (const PRMU::MarkupEntryRefList& entries, bool visible);

	virtual GS::ErrorStatus Execute (void) override;
};

}


#endif