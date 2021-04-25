// *********************************************************************************************************************
// Delete Entry Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef DELETEMARKUPENTYCOMMAND_HPP
#define DELETEMARKUPENTYCOMMAND_HPP

#pragma once


// from Markup
#include "MarkupTypes.hpp"
#include "MarkupCommandsUtils.hpp"

// from GSRoot
#include "ClassInfo.hpp"
#include "MarkupCommandBase.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT DeleteMarkupEntryCommand : public MarkupCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO(DeleteMarkupEntryCommand)

	private:
		DeleteMarkupEntryCommand ();
		DeleteMarkupEntryCommand (const DeleteMarkupEntryCommand& source);
		DeleteMarkupEntryCommand& operator= (const DeleteMarkupEntryCommand& source);

	public:
		DeleteMarkupEntryCommand (const IMarkupEditabilityChecker* checker, 
								  const PRMU::MarkupEntryRefList& entries);

		virtual GS::ErrorStatus ExecuteInternal (void) override;

		virtual GS::ErrorStatus RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;
};

}


#endif