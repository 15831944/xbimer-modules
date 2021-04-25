// *********************************************************************************************************************
//  Accept Markup Entry Suggestions Command
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FLT
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef ACCEPTMARKUPENTRYSUGGESTIONCOMMAND_HPP
#define ACCEPTMARKUPENTRYSUGGESTIONCOMMAND_HPP

#pragma once

// from Markup
#include "MarkupExport.hpp"
#include "Suggestion.hpp"
#include "MarkupTypes.hpp"
#include "MarkupCommandsUtils.hpp"
#include "MarkupModuleUtils.hpp"
#include "AcceptSuggestionsCommandBase.hpp"

// from GSRoot
#include "ClassInfo.hpp"

namespace PRMU {
	
class MARKUP_DLL_EXPORT AcceptMarkupEntrySuggestionsCommand : public AcceptSuggestionsCommandBase {
	DECLARE_DYNAMIC_CLASS_INFO (AcceptMarkupEntrySuggestionsCommand)

private:
	PRMU::SuggestionRefList suggestionList;
	const GS::HashSet<Suggestion::AcceptType>& acceptType;

	AcceptMarkupEntrySuggestionsCommand () :
		acceptType (PRMU::Suggestion::fullAcceptSet),
		AcceptSuggestionsCommandBase (nullptr, GS::Array<TWCB::PermissionID> (), nullptr)
	{};
	AcceptMarkupEntrySuggestionsCommand (const AcceptMarkupEntrySuggestionsCommand& source) = delete;
	AcceptMarkupEntrySuggestionsCommand& operator= (const AcceptMarkupEntrySuggestionsCommand& source) = delete;

public:
	AcceptMarkupEntrySuggestionsCommand (const IMarkupEditabilityChecker* checker,
										 PRMU::SuggestionRefList entryComponents,
										 const GS::HashSet<Suggestion::AcceptType>& acceptType,
										 GS::Owner<IAcceptedIssueElemPreparator>&& issueElemPreparator = nullptr);

	~AcceptMarkupEntrySuggestionsCommand ();

	virtual GS::ErrorStatus ExecuteInternal (void) override;

	virtual GS::ErrorStatus RestoreValidated (const GS::ObjectState& os, const ODB::ObjectRef& context) override;
};

}

#endif