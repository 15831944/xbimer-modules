// *********************************************************************************************************************
// Add Elements To Entry Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef ATTACHELEMENTSTOENTYCOMMAND_HPP
#define ATTACHELEMENTSTOENTYCOMMAND_HPP

#pragma once


// from Markup
#include "ComponentChecker.hpp"
#include "ElementAttacher.hpp"
#include "MarkupEntry.hpp"
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// from GSRoot
#include "ClassInfo.hpp"
#include "MarkupCommandBase.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT AttachElementsToEntryCommand : public PRMU::MarkupCommandBase,
													   public PRMU::ElementAttacher
{
	DECLARE_DYNAMIC_CLASS_INFO (AttachElementsToEntryCommand)

protected:
	PRMU::MarkupEntryRef entry;
	PRMU::EntryViewRef entryView;
	bool needToTurnOn;
	bool recreateNewElements = true;

	ComponentChecker componentChecker;
	InPlanElementsByDesiredComponentTypes inPlanElementsByComponentTypes;

	AttachElementsToEntryCommand			();
	AttachElementsToEntryCommand			(const AttachElementsToEntryCommand& source);
	AttachElementsToEntryCommand& operator= (const AttachElementsToEntryCommand& source);

public:
	AttachElementsToEntryCommand (const IMarkupEditabilityChecker* checker, 
								  const ComponentChecker& componentChecker,
								  PRMU::MarkupEntryRef entry,
								  const InPlanElementsByDesiredComponentTypes& inPlanElementsByComponentTypes,
								  PRMU::EntryViewRef entryView = nullptr,
								  bool needToTurnOnIn = false,
								  bool recreateNewElements = true);

	~AttachElementsToEntryCommand ();

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};

}


#endif
