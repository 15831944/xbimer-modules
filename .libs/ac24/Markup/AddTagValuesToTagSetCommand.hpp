// *********************************************************************************************************************
//  Add Tag Values To TagSet Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef ADDTAGVALUESTOTAGSETCOMMAND_HPP
#define ADDTAGVALUESTOTAGSETCOMMAND_HPP

#pragma once

// from ODB
#include "MVCCommand.hpp"

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "TagSet.hpp"
#include "TagValue.hpp"

// from GSRoot
#include "ClassInfo.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT AddTagValuesToTagSetCommand : public MVC::CommandImp {
	DECLARE_DYNAMIC_CLASS_INFO (AddTagValuesToTagSetCommand)

private:
	TagSetRef			tagSet;
	TagValueRefList	tagValues;

	AddTagValuesToTagSetCommand ();
	AddTagValuesToTagSetCommand (const AddTagValuesToTagSetCommand& source);
	AddTagValuesToTagSetCommand& operator= (const AddTagValuesToTagSetCommand& source);

public:
	AddTagValuesToTagSetCommand (TagSetRef tagSet, TagValueRefList tagValues);

	virtual GS::ErrorStatus Execute (void) override;

	virtual GS::ErrorStatus	RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;

	GS::ObjectState		GetResult (void) const override;
};

}


#endif