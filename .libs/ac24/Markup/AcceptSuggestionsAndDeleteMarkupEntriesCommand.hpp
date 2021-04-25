// *********************************************************************************************************************
//  Accept Suggestions And Delete Entries Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	BFA
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef ACCEPTSUGGESTIONSANDDELETEENTRIESCOMMAND_HPP
#define ACCEPTSUGGESTIONSANDDELETEENTRIESCOMMAND_HPP 

#pragma once

//from Markup
#include "MarkupCommandsUtils.hpp"
#include "MarkupTypes.hpp"
#include "MarkupExport.hpp"
#include "MarkupModuleUtils.hpp"
#include "AcceptSuggestionsCommandBase.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT AcceptSuggestionsAndDeleteMarkupEntriesCommand : public AcceptSuggestionsCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (AcceptSuggestionsAndDeleteMarkupEntriesCommand)

private:
	AcceptSuggestionsAndDeleteMarkupEntriesCommand ();
	AcceptSuggestionsAndDeleteMarkupEntriesCommand (const AcceptSuggestionsAndDeleteMarkupEntriesCommand& source);
	AcceptSuggestionsAndDeleteMarkupEntriesCommand& operator= (const AcceptSuggestionsAndDeleteMarkupEntriesCommand& source);

public:
	AcceptSuggestionsAndDeleteMarkupEntriesCommand (const IMarkupEditabilityChecker* checker,
													MarkupEntryRefList entries,
													GS::Owner<IAcceptedIssueElemPreparator>&& issueElemPreparator = nullptr);
	
	~AcceptSuggestionsAndDeleteMarkupEntriesCommand ();

	virtual GS::ErrorStatus ExecuteInternal (void) override;
};

}

#endif
