// *********************************************************************************************************************
// Description:		CreateEntryViewWithElementsDiff3DCommand class
//
// Module:			Archicad/ProjectMarkup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef NEWENTRYVIEWWITHELEMENTSCOMMAND3DCOMPARE_HPP
#define NEWENTRYVIEWWITHELEMENTSCOMMAND3DCOMPARE_HPP

#pragma once

// from Markup
#include "ComponentChecker.hpp"
#include "ElementAttacher.hpp"
#include "MarkupCommandsUtils.hpp"
#include "MarkupEntry.hpp"
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "ElementDuplicator.hpp"

// from ProjectNavigator
#include "CaptureData.hpp"

// from GSRoot
#include "ClassInfo.hpp"
#include "MarkupCommandBase.hpp"
#include "MarkupModuleUtils.hpp"

// from GSRoot
#include "EventReceiver.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT CreateEntryViewWithElementsDiff3DCommand : public MarkupCommandBase,
																   public ElementAttacher
{
	DECLARE_DYNAMIC_CLASS_INFO (CreateEntryViewWithElementsDiff3DCommand)

private:
	PRMU::MarkupEntryRef								currentMarkup;
	GS::UniString										entryViewName;
	PN::CaptureInterface*								captureInterface;
	ElementsFromDiff3DByComponentTypes					elementsFromDiff3DByComponentTypes;
	EDB::ProjectRef										targetEDBProject;
	PRMU::ComponentChecker								componentChecker;
	ElemDuplicator*										elemDuplicator;

private:
	CreateEntryViewWithElementsDiff3DCommand ();
	CreateEntryViewWithElementsDiff3DCommand (const CreateEntryViewWithElementsDiff3DCommand& source); //disabled
	CreateEntryViewWithElementsDiff3DCommand& operator= (const CreateEntryViewWithElementsDiff3DCommand& source); //disabled

public:
	CreateEntryViewWithElementsDiff3DCommand (const IMarkupEditabilityChecker* checker, 
											  EDB::ProjectRef targetEDBProject,
											  const PRMU::ComponentChecker& ComponentChecker,
											  ElemDuplicator* elemDuplicator,
											  PRMU::MarkupEntryRef currentMarkup,
											  GS::UniString entryViewName,
											  PN::CaptureInterface* captureInterface,
											  const PRMU::ElementsFromDiff3DByComponentTypes& elementsFromDiff3DByComponentTypes);

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};

}
#endif