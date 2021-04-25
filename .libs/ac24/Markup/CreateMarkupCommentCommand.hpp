// *********************************************************************************************************************
// Description:		CreateMarkupCommentCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef CREATEMARKUPCOMMENTCOMMAND_HPP
#define CREATEMARKUPCOMMENTCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"
#include "MarkupEntry.hpp"
#include "MarkupCommandBase.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT CreateMarkupCommentCommand : public MVC::CommandImp {
	DECLARE_DYNAMIC_CLASS_INFO (CreateMarkupCommentCommand)

private:
	const IMarkupEditabilityChecker* markupEditabilityChecker;
	PRMU::MarkupEntryRef		 	 markupEntry;
	GS::UniString					 commentText;

private:
	CreateMarkupCommentCommand ();
	CreateMarkupCommentCommand (const CreateMarkupCommentCommand& source); //disabled
	CreateMarkupCommentCommand& operator= (const CreateMarkupCommentCommand& source); //disabled

public:
	CreateMarkupCommentCommand (const IMarkupEditabilityChecker* checker, MarkupEntryRef markupEntryParam,
								GS::UniString commentParam);

	virtual GS::ErrorStatus Execute (void) override;

	virtual GS::ErrorStatus	RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;
};
} // PRMU namespace


#endif