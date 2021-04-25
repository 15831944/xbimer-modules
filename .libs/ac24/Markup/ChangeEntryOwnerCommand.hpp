// *********************************************************************************************************************
// Description:		ChangeEntryOwnerCommand class
//
// Module:			Markup/Commands
// Namespace:		PRMU
// Contact person:	FLT
//
// *********************************************************************************************************************

#ifndef CHANGEENTRYASSIGNEECOMMAND_HPP
#define CHANGEENTRYASSIGNEECOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupCommandBase.hpp"
#include "MarkupInterfaces.hpp"


namespace PRMU {

	class MARKUP_DLL_EXPORT ChangeEntryOwnerCommand : public MarkupCommandBase {
		DECLARE_DYNAMIC_CLASS_INFO (ChangeEntryOwnerCommand)

	private:
		GS::Guid					assigneeGuid;
		MarkupEntryTWOperations		requestedTWOperationOnEntries;
		bool						comment;

	private:
		ChangeEntryOwnerCommand ();
		ChangeEntryOwnerCommand (const ChangeEntryOwnerCommand& source); //disabled
		ChangeEntryOwnerCommand& operator= (const ChangeEntryOwnerCommand& source); //disabled

	protected:
		ChangeEntryOwnerCommand (const IMarkupEditabilityChecker*	markupEditabilityChecker,
								 PRMU::MarkupEntryRefList			entries,
								 PRMU::MarkupEntryTWOperations		requestedTWOperationOnEntries,
								 const GS::Guid&					assigneeGuid,
								 bool								comment = false);

		virtual GS::ErrorStatus ExecuteInternal (void) override final;
	};

}

#endif