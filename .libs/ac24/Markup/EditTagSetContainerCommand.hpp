// *********************************************************************************************************************
// Edit Multiple TagSets Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef EDITTAGSETCONTAINERCOMMAND_HPP
#define EDITTAGSETCONTAINERCOMMAND_HPP

#pragma once

// from ODB
#include "ODBIdSpace.hpp"
#include "ODBMD5DifferenceGenerator.hpp"

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "TagSetContainer.hpp"
#include "MarkupEntrySet.hpp"
#include "TagSetCommandBase.hpp"
#include "TraceAndMergeEntrySetChanges.hpp"

// from GSRoot
#include "AutoPtr.hpp"
#include "ClassInfo.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT EditTagSetContainerCommand : public TagSetCommandBase,
													 public TraceAndMergeEntrySetChanges 
{
	DECLARE_DYNAMIC_CLASS_INFO (EditTagSetContainerCommand)

private:
	EditTagSetContainerCommand ();
	EditTagSetContainerCommand (const EditTagSetContainerCommand& source);
	EditTagSetContainerCommand& operator= (const EditTagSetContainerCommand& source);

public:
	EditTagSetContainerCommand (const TWUserParams* twUserParams,
								PRMU::MarkupEntrySetConstRef entrySet);
	~EditTagSetContainerCommand ();

	virtual GS::ErrorStatus ExecuteCommand (void) override;
};

}


#endif