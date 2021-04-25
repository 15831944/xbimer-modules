// *********************************************************************************************************************
// Description:		ChangeEntryResponsiblesCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	BFA
//
// *********************************************************************************************************************

#ifndef CHANGEENTRYRESPONSIBLESCOMMAND_HPP
#define CHANGEENTRYRESPONSIBLESCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupCommandBase.hpp"


namespace PRMU {

	class MARKUP_DLL_EXPORT ChangeEntryResponsiblesCommand : public MarkupCommandBase {
		DECLARE_DYNAMIC_CLASS_INFO (ChangeEntryResponsiblesCommand)

	private:
		GS::HashSet<GS::UniString>	newResponsibles;

	private:
		ChangeEntryResponsiblesCommand ();
		ChangeEntryResponsiblesCommand (const ChangeEntryResponsiblesCommand& source); //disabled
		ChangeEntryResponsiblesCommand& operator= (const ChangeEntryResponsiblesCommand& source); //disabled

	public:
		ChangeEntryResponsiblesCommand (const IMarkupEditabilityChecker*	markupEditabilityChecker,
										PRMU::MarkupEntryRefList			entries,
										const GS::HashSet<GS::UniString>&	newResponsibles);

		virtual GS::ErrorStatus ExecuteInternal (void) override;
	};

}

#endif