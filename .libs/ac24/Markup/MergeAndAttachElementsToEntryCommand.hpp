// *********************************************************************************************************************
// Description:		MergeAndAttachElementsToEntryCommand class
//
// Module:			ARCHICAD/ProjectMarkup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef MERGEANDATTACHELEMENTTOENTRYCOMMAND_HPP
#define MERGEANDATTACHELEMENTTOENTRYCOMMAND_HPP

#pragma once

// from Markup
#include "AttachElementsToEntryCommand.hpp"
#include "ComponentChecker.hpp"
#include "MarkupModuleUtils.hpp"
#include "ElementDuplicator.hpp"

// from VBElements
#include "GeneralElem.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT MergeAndAttachElementsToEntryCommand : public AttachElementsToEntryCommand
{
	DECLARE_DYNAMIC_CLASS_INFO (MergeAndAttachElementsToEntryCommand)

private:
	EDB::ProjectRef										targetProject;
	GetDiff3DElemExistenceAndStateInfoFunctionPtr		GetGeometricalSourceChange;
	ElemDuplicator*										elemDuplicator;

	ElementsFromDiff3DByComponentTypes elementsFromDiff3DByComponentTypes;

	MergeAndAttachElementsToEntryCommand ();
	MergeAndAttachElementsToEntryCommand (const MergeAndAttachElementsToEntryCommand& source);
	MergeAndAttachElementsToEntryCommand& operator= (const MergeAndAttachElementsToEntryCommand& source);

public:
	MergeAndAttachElementsToEntryCommand (const IMarkupEditabilityChecker* checker, 
										  const ComponentChecker& componentChecker,
										  EDB::ProjectRef targetProject,
										  PRMU::MarkupEntryRef entry,
										  const ElementsFromDiff3DByComponentTypes& elementsFromDiff3DByComponentTypes,
										  const PRMU::GetDiff3DElemExistenceAndStateInfoFunctionPtr& GetGeometricalSourceChange,
										  ElemDuplicator* elemDuplicator,
										  PRMU::EntryViewRef entryView = nullptr,
										  bool needEntryTurnOn = false);

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};
}

#endif