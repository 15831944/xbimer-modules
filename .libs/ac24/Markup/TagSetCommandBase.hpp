// *********************************************************************************************************************
// TagSet Commands Base Abstract Class
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FLT
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef TAGSETCOMMANDBASE_HPP
#define TAGSETCOMMANDBASE_HPP

#pragma once

// from ODB
#include "MVCCommand.hpp"

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// from GSRoot
#include "Array.hpp"

// from TWRoot
#include "TWPermissionIDs.h"

// predeclarations
namespace TWCB {
enum PermissionID;
}

namespace PRMU { struct TWUserParams; }

namespace PRMU {

class MARKUP_DLL_EXPORT TagSetCommandBase : public MVC::CommandImp {

protected:
	const TWUserParams* twUserParams;
	GS::Array<TWCB::PermissionID> necessaryPermissions;

protected:
	TagSetCommandBase () = delete;
	TagSetCommandBase (const TWUserParams* twUserParams,
					   const GS::Array<TWCB::PermissionID>& necessaryPermissions);

	virtual ~TagSetCommandBase ();

	GS::ErrorStatus Execute (void) override final;
	virtual GS::ErrorStatus ExecuteCommand (void) = 0;
};
}


#endif