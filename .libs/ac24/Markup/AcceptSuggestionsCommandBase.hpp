// *********************************************************************************************************************
// Accept Suggestions Command Base Abstract Class
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	TZ
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef PRMU_ACCEPTSUGGESTIONSCOMMANDBASE_HPP
#define PRMU_ACCEPTSUGGESTIONSCOMMANDBASE_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "MarkupCommandBase.hpp"


namespace PRMU {

class MARKUP_DLL_EXPORT AcceptSuggestionsCommandBase : public MarkupCommandBase {

private:
	GS::Owner<IAcceptedIssueElemPreparator> issueElemPreparator;

	AcceptSuggestionsCommandBase (const AcceptSuggestionsCommandBase& source) = delete;
	AcceptSuggestionsCommandBase& operator= (const AcceptSuggestionsCommandBase& source) = delete;

protected:
	AcceptSuggestionsCommandBase (const IMarkupEditabilityChecker* markupEditabilityChecker,
								  const GS::Array<TWCB::PermissionID>& necessaryPermissions,
								  const PRMU::MarkupEntryRefList& entries,
								  GS::Owner<IAcceptedIssueElemPreparator>&& issueElemPreparator);

	AcceptSuggestionsCommandBase (const IMarkupEditabilityChecker* markupEditabilityChecker,
								  const GS::Array<TWCB::PermissionID>& necessaryPermissions,
								  GS::Owner<IAcceptedIssueElemPreparator>&& issueElemPreparator);

	AcceptSuggestionsCommandBase (const IMarkupEditabilityChecker* markupEditabilityChecker,
								  const PRMU::IssueRelatedOperation operation,
								  const PRMU::MarkupEntryRefList& entries,
								  GS::Owner<IAcceptedIssueElemPreparator>&& issueElemPreparator);

	virtual ~AcceptSuggestionsCommandBase ();

	const IAcceptedIssueElemPreparator* GetIssueElemPreparator () const;
};

}

#endif
