// *********************************************************************************************************************
// Description:		RenameSceneCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef RENAMESCENECOMMAND_HPP
#define RENAMESCENECOMMAND_HPP

#pragma once

#include "MarkupExport.hpp"

#include "EntryView.hpp"
#include "MarkupCommandBase.hpp"


namespace PRMU {

class MARKUP_DLL_EXPORT RenameSceneCommand : public MarkupCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (RenameSceneCommand)

private:
	PRMU::EntryViewRef				view;
	GS::UniString					newName;

private:
	RenameSceneCommand ();
	RenameSceneCommand (const RenameSceneCommand& source); //disabled
	RenameSceneCommand& operator= (const RenameSceneCommand& source); //disabled

public:
	RenameSceneCommand (const IMarkupEditabilityChecker* checker, 
						PRMU::EntryViewRef view,
						GS::UniString newName);

	virtual GS::ErrorStatus ExecuteInternal (void) override;

	virtual GS::ErrorStatus	RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;

};

}

#endif