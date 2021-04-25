// *********************************************************************************************************************
// Description:		ChangeEntryStatusCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef CHANGEENTRYSTATUSCOMMAND_HPP
#define CHANGEENTRYSTATUSCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupCommandBase.hpp"


namespace PRMU {

	class MARKUP_DLL_EXPORT ChangeEntryStatusCommand : public MarkupCommandBase {
		DECLARE_DYNAMIC_CLASS_INFO (ChangeEntryStatusCommand)

	private:
		TagValueRef	newStatus;

	private:
		ChangeEntryStatusCommand ();
		ChangeEntryStatusCommand (const ChangeEntryStatusCommand& source); //disabled
		ChangeEntryStatusCommand& operator= (const ChangeEntryStatusCommand& source); //disabled

	public:
		ChangeEntryStatusCommand (const IMarkupEditabilityChecker*	markupEditabilityChecker,
								  PRMU::MarkupEntryRefList			entries,
								  const TagValueRef&				status);

		virtual GS::ErrorStatus ExecuteInternal (void) override;
	};

}

#endif