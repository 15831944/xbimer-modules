// *********************************************************************************************************************
// Description:		ModifyEntryCommentCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	UE
//
// *********************************************************************************************************************

#ifndef MODIFYENTRYCOMMENTCOMMAND_HPP
#define MODIFYENTRYCOMMENTCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupTypes.hpp"
#include "MarkupCommandBase.hpp"


namespace PRMU {

class MARKUP_DLL_EXPORT ModifyEntryCommentCommand : public MarkupCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (ModifyEntryCommentCommand)

private:
	PRMU::EntryCommentRef			entryComment;
	const GS::UniString				newText;

private:
	ModifyEntryCommentCommand ();
	ModifyEntryCommentCommand (const ModifyEntryCommentCommand& source);			//disabled
	ModifyEntryCommentCommand& operator= (const ModifyEntryCommentCommand& source); //disabled

public:
	ModifyEntryCommentCommand (const IMarkupEditabilityChecker* checker, 
							   PRMU::EntryCommentRef comment,
							   const GS::UniString newText);

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};

}

#endif