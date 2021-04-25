// *********************************************************************************************************************
// HistoryElement of a MarkupEntry
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (HISTORYENTRY_HPP)
#define HISTORYENTRY_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Geometry
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// from TW
#include "TWObject.hpp"

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT HistoryEntry : public TW::Object
{
	DECLARE_DYNAMIC_CLASS (HistoryEntry)
private :
	HistoryEntry ();
public:
	enum ModificationType {
		BCFExport,
		SceneCreated,
		SceneModified,
		SceneDeleted,
		ElementsAdded,
		ElementsAccepted,
		ElementsRemoved,
		CommentCreated,
		CommentModified,
		IssueCreated,
		IssueModified
	};

	HistoryEntry (const GSTime& when, const GS::Guid& userGuid, const ModificationType& subjectOfModification,
				  const GS::Array<GS::UniString>& newValues, const GS::UniString& userName = "");
	HistoryEntry (const HistoryEntry& source);
	virtual ~HistoryEntry ();

	GSTime							GetWhen () const;
	GS::Guid						GetWho () const;
	ModificationType				GetWhat () const;
	GS::Array<GS::UniString>		GetNewValues () const;
	GS::UniString					GetNameBackup () const;

	static PRMU::HistoryEntryRef	CreateAndAttachHistoryToMarkup (const PRMU::MarkupEntryRef& markupEntry,
																	const ModificationType& subjectOfModification,
																	const GS::Array<GS::UniString>& newValues = {},
																	const GSTime& when = 0,
																	const GS::Guid& userGuid = GS::NULLGuid,
																	const GS::UniString& userName = GS::EmptyUniString);
};

} // namespace PRMU

#endif