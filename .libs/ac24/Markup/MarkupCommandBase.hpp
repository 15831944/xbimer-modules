// *********************************************************************************************************************
// Markup Commands Base Abstract Class
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FLT
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef MARKUPCOMMANDBASE_HPP
#define MARKUPCOMMANDBASE_HPP

#pragma once

// from ODB
#include "MVCCommandWithSplitExecution.hpp"

// from Markup
#include "MarkupEntry.hpp"
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "MarkupCommandsUtils.hpp"

// from GSRoot
#include "Array.hpp"

// from TWRoot
#include "TWPermissionIDs.h"

namespace PRMU {

class MARKUP_DLL_EXPORT MarkupCommandBase : public MVC::CommandWithSplitExecution {

private:
	virtual GS::ErrorStatus ExecuteCoreImp (void) override final;

protected:
	const IMarkupEditabilityChecker* markupEditabilityChecker;
	GS::Array<TWCB::PermissionID>	 necessaryPermissions;
	PRMU::MarkupEntryRefList		 entries;
	PRMU::IssueRelatedOperation		 operation;
	bool							 isActuallyModified;

protected:
	MarkupCommandBase () = delete;
	MarkupCommandBase (const MarkupCommandBase& source);
	MarkupCommandBase (const IMarkupEditabilityChecker* markupEditabilityChecker,
					   const GS::Array<TWCB::PermissionID>& necessaryPermissions,
					   const PRMU::MarkupEntryRefList& entries);

	MarkupCommandBase (const IMarkupEditabilityChecker* markupEditabilityChecker,
					   const GS::Array<TWCB::PermissionID>& necessaryPermissions);

	MarkupCommandBase (const IMarkupEditabilityChecker* markupEditabilityChecker,
					   const PRMU::IssueRelatedOperation operation,
					   const PRMU::MarkupEntryRefList& entries);

	const PRMU::IMarkupEditabilityChecker* GetMarkupEditabilityChecker () const;

	virtual GS::ErrorStatus	StartImp (void) override final;
	virtual GS::ErrorStatus	StopImp (void) override final;

	virtual GS::ErrorStatus ExecuteInternal (void) = 0;

public:
	virtual ~MarkupCommandBase ();
};
}

#endif
