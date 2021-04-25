// *********************************************************************************************************************
// Description:		RequestEntriesCommand class
//
// Module:			Markup/Commands
// Namespace:		PRMU
// Contact person:	FLT
//
// *********************************************************************************************************************


#ifndef REQUESTENTRIESCOMMAND_HPP
#define REQUESTENTRIESCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupCommandBase.hpp"
#include "MarkupInterfaces.hpp"
#include "ChangeEntryOwnerCommand.hpp"


namespace PRMU {

class MARKUP_DLL_EXPORT RequestEntriesCommand : public ChangeEntryOwnerCommand {
	DECLARE_DYNAMIC_CLASS_INFO (RequestEntriesCommand)

private:
	RequestEntriesCommand ();
	RequestEntriesCommand (const RequestEntriesCommand& source); //disabled
	RequestEntriesCommand& operator= (const RequestEntriesCommand& source); //disabled

public:
	RequestEntriesCommand (const IMarkupEditabilityChecker*	markupEditabilityChecker,
						   PRMU::MarkupEntryRefList			entries);
};

}

#endif