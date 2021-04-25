// *********************************************************************************************************************
// Description:		AssignEntriesCommand class
//
// Module:			Markup/Commands
// Namespace:		PRMU
// Contact person:	FLT
//
// *********************************************************************************************************************


#ifndef ASSIGNENTRIESCOMMAND_HPP
#define ASSIGNENTRIESCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupCommandBase.hpp"
#include "MarkupInterfaces.hpp"
#include "ChangeEntryOwnerCommand.hpp"


namespace PRMU {

class MARKUP_DLL_EXPORT AssignEntriesCommand : public ChangeEntryOwnerCommand {
	DECLARE_DYNAMIC_CLASS_INFO (AssignEntriesCommand)

private:
	AssignEntriesCommand ();
	AssignEntriesCommand (const AssignEntriesCommand& source); //disabled
	AssignEntriesCommand& operator= (const AssignEntriesCommand& source); //disabled

public:
	AssignEntriesCommand (const IMarkupEditabilityChecker*	markupEditabilityChecker,
						  PRMU::MarkupEntryRefList			entries,
						  const GS::Guid&					newOwnerGuid);
};

}

#endif