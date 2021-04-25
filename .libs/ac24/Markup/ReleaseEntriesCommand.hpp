// *********************************************************************************************************************
// Description:		ReleaseEntriesCommand class
//
// Module:			Markup/Commands
// Namespace:		PRMU
// Contact person:	FLT
//
// *********************************************************************************************************************


#ifndef RELEASEENTRIESCOMMAND_HPP
#define RELEASEENTRIESCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupCommandBase.hpp"
#include "MarkupInterfaces.hpp"
#include "ChangeEntryOwnerCommand.hpp"


namespace PRMU {

class MARKUP_DLL_EXPORT ReleaseEntriesCommand : public ChangeEntryOwnerCommand {
	DECLARE_DYNAMIC_CLASS_INFO (ReleaseEntriesCommand)

private:
	ReleaseEntriesCommand ();
	ReleaseEntriesCommand (const ReleaseEntriesCommand& source); //disabled
	ReleaseEntriesCommand& operator= (const ReleaseEntriesCommand& source); //disabled

public:
	ReleaseEntriesCommand (const IMarkupEditabilityChecker*	markupEditabilityChecker,
						   PRMU::MarkupEntryRefList			entries,
						   bool								comment = false);
};

}

#endif