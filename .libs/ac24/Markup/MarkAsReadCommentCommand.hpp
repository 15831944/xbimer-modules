// *********************************************************************************************************************
// Description:		MarkAsReadCommentCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	UE
//
// *********************************************************************************************************************

#ifndef MARASREADCOMMENTCOMMAND_HPP
#define MARASREADCOMMENTCOMMAND_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "MarkupCommandBase.hpp"

#include "EntryComment.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT MarkAsReadCommentCommand : public MVC::CommandImp {
	DECLARE_DYNAMIC_CLASS_INFO (MarkAsReadCommentCommand)

private:
	PRMU::EntryCommentRef	entryComment;
	bool					markAsRead;

private:
	MarkAsReadCommentCommand ();
	MarkAsReadCommentCommand (const MarkAsReadCommentCommand& source);				//disabled
	MarkAsReadCommentCommand& operator= (const MarkAsReadCommentCommand& source);	//disabled

public:
	MarkAsReadCommentCommand (PRMU::EntryCommentRef entryComment, 
							  bool markAsRead);

	virtual GS::ErrorStatus Execute (void) override;
};

} // PRMU namespace

#endif