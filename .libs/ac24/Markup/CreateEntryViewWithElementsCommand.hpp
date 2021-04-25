// *********************************************************************************************************************
// Description:		CreateEntryViewWithElementsCommand class
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef CREATEENTRYVIEWWITHELEMENTSCOMMAND_HPP
#define CREATEENTRYVIEWWITHELEMENTSCOMMAND_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "MarkupEntry.hpp"
#include "MarkupTypes.hpp"
#include "MarkupCommandsUtils.hpp"
#include "MarkupCommandBase.hpp"

// from ProjectNavigator
#include "CaptureData.hpp"

// from GSRoot
#include "ClassInfo.hpp"
#include "EventReceiver.hpp"


namespace PRMU {

class MARKUP_DLL_EXPORT CreateEntryViewWithElementsCommand : public MarkupCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (CreateEntryViewWithElementsCommand)

protected:
	PRMU::MarkupEntryRef				currentMarkup;
	GS::UniString						entryViewName;
	PN::CaptureInterface*				captureInterface;	
	EDB::GeneralElemRefList				elems;
	PRMU::EntryComponent::Type			type;

	CreateEntryViewWithElementsCommand ();
	CreateEntryViewWithElementsCommand (const CreateEntryViewWithElementsCommand& source); //disabled
	CreateEntryViewWithElementsCommand& operator= (const CreateEntryViewWithElementsCommand& source); //disabled

public:
	CreateEntryViewWithElementsCommand (const IMarkupEditabilityChecker* checker, 
										PRMU::MarkupEntryRef currentMarkup,
										GS::UniString entryViewName,
										PN::CaptureInterface* captureInterface,
										EDB::GeneralElemRefList elems,
										const PRMU::EntryComponent::Type& type);

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};

}

#endif