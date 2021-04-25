// *********************************************************************************************************************
// Description:		ChangeEntryPriorityCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef CHANGEENTRYPRIORITYCOMMAND_HPP
#define CHANGEENTRYPRIORITYCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupCommandBase.hpp"


namespace PRMU {

	class MARKUP_DLL_EXPORT ChangeEntryPriorityCommand : public MarkupCommandBase {
		DECLARE_DYNAMIC_CLASS_INFO (ChangeEntryPriorityCommand)

	private:
		TagValueRef	newPriority;

	private:
		ChangeEntryPriorityCommand ();
		ChangeEntryPriorityCommand (const ChangeEntryPriorityCommand& source); //disabled
		ChangeEntryPriorityCommand& operator= (const ChangeEntryPriorityCommand& source); //disabled

	public:
		ChangeEntryPriorityCommand (const IMarkupEditabilityChecker*	markupEditabilityChecker,
									PRMU::MarkupEntryRefList			entries,
									const TagValueRef&					priority);

		virtual GS::ErrorStatus ExecuteInternal (void) override;
	};

}

#endif