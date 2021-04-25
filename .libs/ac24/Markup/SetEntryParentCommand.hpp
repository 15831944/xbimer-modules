// *********************************************************************************************************************
// Set Parent Of Markup Entry
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef SETENTRYPARENTCOMMAND_HPP
#define SETENTRYPARENTCOMMAND_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "MarkupEntry.hpp"
#include "MarkupCommandBase.hpp"

// from GSRoot
#include "ClassInfo.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT SetEntryParentCommand : public MarkupCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (SetEntryParentCommand)

private:
	MarkupEntryRef			entry;
	MarkupEntryRef			parentEntry;

	SetEntryParentCommand ();
	SetEntryParentCommand (const SetEntryParentCommand& source);
	SetEntryParentCommand& operator= (const SetEntryParentCommand& source);

public:
	SetEntryParentCommand (const IMarkupEditabilityChecker* checker, 
						   MarkupEntryRef entry,
						   MarkupEntryRef parentEntry);

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};

}


#endif