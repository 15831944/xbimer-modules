// *********************************************************************************************************************
// Description:		RenameEntryCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	VaLa
//
// *********************************************************************************************************************

#ifndef RENAMEENTRYCOMMAND_HPP
#define RENAMEENTRYCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupEntry.hpp"
#include "MarkupCommandBase.hpp"


namespace PRMU {

class MARKUP_DLL_EXPORT RenameEntryCommand : public MarkupCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (RenameEntryCommand)

private:
	PRMU::MarkupEntryRef			entry;
	GS::UniString					newName;

private:
	RenameEntryCommand ();
	RenameEntryCommand (const RenameEntryCommand& source); //disabled
	RenameEntryCommand& operator= (const RenameEntryCommand& source); //disabled

public:
	RenameEntryCommand (const IMarkupEditabilityChecker* checker, 
						PRMU::MarkupEntryRef entry,
						GS::UniString newName);

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};

}

#endif