// *********************************************************************************************************************
// Description:		RedefineByCurrentViewCommand class
//
// Module:			ARCHICAD/Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// *********************************************************************************************************************

#ifndef REDEFINEBYCURRENTVIEWCOMMAND_HPP
#define REDEFINEBYCURRENTVIEWCOMMAND_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"

#include "ComponentChecker.hpp"
#include "EntryView.hpp"
#include "ElementAttacher.hpp"
#include "MarkupCommandBase.hpp"
#include "MarkupModuleUtils.hpp"
#include "ElementDuplicator.hpp"

// from GSRoot
#include "EventReceiver.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT RedefineByCurrentViewCommand : public MarkupCommandBase,
													   public ElementAttacher
{
	DECLARE_DYNAMIC_CLASS_INFO (RedefineByCurrentViewCommand)

private:
	PRMU::EntryViewRefList			entryViews;
	PN::CaptureInterface*			captureInterface;
	ElementsFromDiff3DByComponentTypes		elementsFromDiff3DByComponentTypes;

	ElemDuplicator*									elemDuplicator;
	ComponentChecker									componentChecker;
private:
	RedefineByCurrentViewCommand ();
	RedefineByCurrentViewCommand (const RedefineByCurrentViewCommand& source); //disabled
	RedefineByCurrentViewCommand& operator= (const RedefineByCurrentViewCommand& source); //disabled

public:
	RedefineByCurrentViewCommand (const IMarkupEditabilityChecker* checker, 
								  PRMU::EntryViewRefList entryViews,
								  PN::CaptureInterface* captureInterface,
								  const PRMU::ElementsFromDiff3DByComponentTypes& elementsFromDiff3DByComponentTypes,
								  ElemDuplicator* elemDuplicator,
								  const ComponentChecker& componentChecker);

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};

}

#endif