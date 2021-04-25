// *********************************************************************************************************************
// A comment of the MarkupEntry
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ENTRYCOMMENT_HPP)
#define ENTRYCOMMENT_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "GSTime.hpp"

// from TWRoot
#include "TWObject.hpp"

// own
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

namespace PRMU {

// --- Type definitions	------------------------------------------------------------------------------------------------

class MARKUP_DLL_EXPORT EntryComment : public TW::Object
{
	DECLARE_DYNAMIC_CLASS (EntryComment)

public:
	enum CommentStatus : UInt8 {
		First = 0,

		Error = 0,
		Warning = 1,
		Info = 2,
		Unknown = 3,

		Last = 3
	};

private:
	friend class MarkupEntry;

public:
	EntryComment ();
	EntryComment (const GS::UniString& comment, const GS::Guid& userId, CommentStatus status, const GS::UniString& verbalStatus, const GS::Guid& externalId, const GS::UniString& author, GSTime commentCreaTime);
	EntryComment (const EntryComment& source) : TW::Object (source) { };
	~EntryComment ();

	// operators
	EntryComment& operator= (const EntryComment& source);
	bool operator== (const EntryComment& source) const { return this->IsEqual (source); }
	bool operator<= (const EntryComment& source);

	// from GS::Object via ODB::Object
	virtual EntryComment*   Clone () const override;
	// accessors
	const GS::UniString	GetText () const;
	const GS::Guid		GetUserId () const;
	GSTime				GetCreationTime () const;
	const CommentStatus	GetStatus () const;
	const GS::UniString	GetVerbalStatus () const;
	GS::Guid			GetExternalId () const;
	const GS::UniString	GetAuthor () const;
	GS::Guid			GetIdForBCF () const;

	// modifiers
	bool				SetText (const GS::UniString& str);

	bool				IsConnected (PRMU::EntryViewRef view) const;
	GSErrCode			ConnectInView (PRMU::EntryViewRef view);
	GSErrCode			DisconnectFromView ();
	GSErrCode			DisconnectFromGivenView (PRMU::EntryViewRef view);
	EntryViewConstRef	GetEntryView () const;

	// Object realization
	virtual GSErrCode		Read (GS::IChannel& ic) override;

	virtual GSErrCode		WriteIsolatedState (GS::OChannel& oc) const override;
	virtual GSErrCode		ReadIsolatedState (GS::IChannel& ic) override;
	virtual	GSErrCode		WriteTWIsolatedState (GS::OChannel& oc) const override;
	virtual	GSErrCode		ReadTWIsolatedState (GS::IChannel& ic) override;

	static void				MarkAsRead (const EntryCommentRef& entryComment);
	static void				MarkAsUnread (const EntryCommentRef& entryComment);

	bool					IsRead () const;
	// ... Other private methods .......................................................................................

private:

	GSErrCode					ReadAsString (GS::IChannel& ic, GS::UniString& uniStr);
	GSErrCode					WriteAsString (GS::OChannel& oc, const GS::UniString& uniStr) const;

	GSErrCode					ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode					ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode					ReadVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteCoreIsolatedStateVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadCoreIsolatedStateVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteCoreIsolatedStateVersion3 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadCoreIsolatedStateVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					ReadIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteIsolatedStateVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadIsolatedStateVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteIsolatedStateVersion3 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadIsolatedStateVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteTWIsolatedStateVersion2 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadTWIsolatedStateVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode					WriteTWIsolatedStateVersion3 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode					ReadTWIsolatedStateVersion3 (GS::IChannel& ic, const GS::InputFrame& frame);
};

} // namespace PRMU

#endif
