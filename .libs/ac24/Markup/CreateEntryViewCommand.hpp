// *********************************************************************************************************************
// Description:		LinkViewToEntryCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef LINKVIEWTOENTRYCOMMAND_HPP
#define LINKVIEWTOENTRYCOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "MarkupEntry.hpp"

#include "CaptureData.hpp"

#include "MarkupCommandsUtils.hpp"
#include "ClassInfo.hpp"
#include "MarkupCommandBase.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT CreateEntryViewCommand : public MarkupCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (CreateEntryViewCommand)

private:
	PRMU::MarkupEntryRef			currentMarkup;
	GS::UniString					entryViewName;
	PN::CaptureInterface*			captureInterface;

private:
	CreateEntryViewCommand ();
	CreateEntryViewCommand (const CreateEntryViewCommand& source); //disabled
	CreateEntryViewCommand& operator= (const CreateEntryViewCommand& source); //disabled

public:
	CreateEntryViewCommand (const IMarkupEditabilityChecker* checker, 
							PRMU::MarkupEntryRef currentMarkup,
							GS::UniString entryViewName, 
							PN::CaptureInterface* captureInterface);

	virtual GS::ErrorStatus ExecuteInternal (void) override;

	virtual GS::ErrorStatus	RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;

	GS::ObjectState		GetResult (void) const override;
};

}

#endif