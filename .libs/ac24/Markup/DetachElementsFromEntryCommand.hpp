// *********************************************************************************************************************
// Detach Elements From Entry Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef DETACHELEMENTSFROMENTRYCOMMAND_HPP
#define DETACHELEMENTSFROMENTRYCOMMAND_HPP

#pragma once


// from Markup
#include "MarkupEntry.hpp"
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "MarkupCommandsUtils.hpp"
#include "MarkupCommandBase.hpp"

// from GSRoot
#include "ClassInfo.hpp"


namespace PRMU {

class MARKUP_DLL_EXPORT DetachElementsFromEntryCommand : public MarkupCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (DetachElementsFromEntryCommand)

private:
	PRMU::MarkupEntryRef entry;
	EDB::GeneralElemRefList elems;

	DetachElementsFromEntryCommand ();
	DetachElementsFromEntryCommand (const DetachElementsFromEntryCommand& source);
	DetachElementsFromEntryCommand& operator= (const DetachElementsFromEntryCommand& source);

public:
	DetachElementsFromEntryCommand (const IMarkupEditabilityChecker* checker, 
									PRMU::MarkupEntryRef entry,
								    EDB::GeneralElemRefList elems);

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};

}


#endif