// *********************************************************************************************************************
// Description:		ReserveEntriesCommand class
//
// Module:			Markup/Commands
// Namespace:		PRMU
// Contact person:	FLT
//
// *********************************************************************************************************************


#ifndef RESERVEENTRIESCOMMAND_HPP
#define RESERVEENTRIESCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupCommandBase.hpp"
#include "MarkupInterfaces.hpp"
#include "ChangeEntryOwnerCommand.hpp"


namespace PRMU {

class MARKUP_DLL_EXPORT ReserveEntriesCommand : public ChangeEntryOwnerCommand {
	DECLARE_DYNAMIC_CLASS_INFO (ReserveEntriesCommand)

private:
	ReserveEntriesCommand ();
	ReserveEntriesCommand (const ReserveEntriesCommand& source); //disabled
	ReserveEntriesCommand& operator= (const ReserveEntriesCommand& source); //disabled

public:
	ReserveEntriesCommand (const IMarkupEditabilityChecker*	markupEditabilityChecker,
						   PRMU::MarkupEntryRefList			entries);
};

}

#endif