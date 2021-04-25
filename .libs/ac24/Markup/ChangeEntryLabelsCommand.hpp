// *********************************************************************************************************************
// Description:		ChangeEntryLabelsCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef CHANGEENTRYLABELSCOMMAND_HPP
#define CHANGEENTRYLABELSCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupCommandBase.hpp"


namespace PRMU {

	class MARKUP_DLL_EXPORT ChangeEntryLabelsCommand : public MarkupCommandBase {
		DECLARE_DYNAMIC_CLASS_INFO (ChangeEntryLabelsCommand)

	private:
		GS::HashSet<GS::UniString>	newLabels;

	private:
		ChangeEntryLabelsCommand ();
		ChangeEntryLabelsCommand (const ChangeEntryLabelsCommand& source); //disabled
		ChangeEntryLabelsCommand& operator= (const ChangeEntryLabelsCommand& source); //disabled

	public:
		ChangeEntryLabelsCommand (const IMarkupEditabilityChecker*	markupEditabilityChecker,
								  PRMU::MarkupEntryRefList			entries,
								  const GS::HashSet<GS::UniString>& newLabels);

		virtual GS::ErrorStatus ExecuteInternal (void) override;
	};

}

#endif