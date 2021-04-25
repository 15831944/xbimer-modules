// *********************************************************************************************************************
// Detach Entries From TagValue Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef DETACHENTRIESFROMTAGVALUECOMMAND_HPP
#define DETACHENTRIESFROMTAGVALUECOMMAND_HPP

#pragma once


// from ODB
#include "MVCCommand.hpp"

// from Markup
#include "MarkupEntry.hpp"
#include "TagValue.hpp"
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// from GSRoot
#include "ClassInfo.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT DetachEntriesFromTagValueCommand : public MVC::CommandImp {
	DECLARE_DYNAMIC_CLASS_INFO (DetachEntriesFromTagValueCommand)

private:
	MarkupEntryRefList entries;
	TagValueRef  tagValue;

	DetachEntriesFromTagValueCommand () = default;
	DetachEntriesFromTagValueCommand (const DetachEntriesFromTagValueCommand& source);
	DetachEntriesFromTagValueCommand& operator= (const DetachEntriesFromTagValueCommand& source);

public:
	DetachEntriesFromTagValueCommand (TagValueRef  tagValue, MarkupEntryRefList entries);

	virtual GS::ErrorStatus Execute (void) override;
};

}


#endif