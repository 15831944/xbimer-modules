// *********************************************************************************************************************
// Description:		ChangeEntryDueDateCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef CHANGEENTRYDUEDATECOMMAND_HPP
#define CHANGEENTRYDUEDATECOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupCommandBase.hpp"


namespace PRMU {

	class MARKUP_DLL_EXPORT ChangeEntryDueDateCommand : public MarkupCommandBase {
		DECLARE_DYNAMIC_CLASS_INFO (ChangeEntryDueDateCommand)

	private:
		GSTime	newDueDate;

	private:
		ChangeEntryDueDateCommand ();
		ChangeEntryDueDateCommand (const ChangeEntryDueDateCommand& source); //disabled
		ChangeEntryDueDateCommand& operator= (const ChangeEntryDueDateCommand& source); //disabled

	public:
		ChangeEntryDueDateCommand (const IMarkupEditabilityChecker*	markupEditabilityChecker,
								   PRMU::MarkupEntryRefList			entries,
								   const GSTime&					newDueDate);

		virtual GS::ErrorStatus ExecuteInternal (void) override;
	};

}

#endif