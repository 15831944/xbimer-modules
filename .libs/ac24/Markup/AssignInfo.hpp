// *********************************************************************************************************************
// AssignInfo: Class to store user guid used in MarkUpEntry assign Operations
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	TVT
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (PRMUASSIGNINFO_HPP)
#define PRMUASSIGNINFO_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from TWRoot
#include "TWObject.hpp"

// own
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

namespace PRMUAC22 {

// --- Type definitions	------------------------------------------------------------------------------------------------


// === AssignInfo class ===============================================================================================


class MARKUP_DLL_EXPORT AssignInfo : public TW::Object
{
	DECLARE_DYNAMIC_CLASS (AssignInfo)

protected:
	mutable UInt64		revisionNumber;		// latest version received from server (runtime data)
	mutable bool		wasReceive;			// runtime data

public:
	enum UserIdType {
		CreaOwner,
		PrevOwner,
		Owner
	};

	// ... Constructors / destructor ...................................................................................

public:
	AssignInfo ();
	AssignInfo (const GS::Guid& creatorId,
				const GS::Guid& lastModifierId,
				const GS::Guid& assigneeId,
				const GS::UniString& creatorFullName,
				const GS::UniString& lastModifierFullName,
				const GS::UniString& assigneeFullName);
	
	AssignInfo	(const AssignInfo& source) :
		TW::Object (source),
		revisionNumber (source.revisionNumber),
		wasReceive (source.wasReceive)
	{	}
	
	~AssignInfo ();

public:
	AssignInfo& operator= (const AssignInfo& source);


public:
	virtual AssignInfo* Clone (void) const override;

	// ... Accessors methods ...........................................................................................

public:
	void	Reset ();

	GS::Guid	GetCreatorGuid () const;
	GS::Guid	GetLastModifierGuid () const;
	GS::Guid	GetAssigneeGuid () const;

	void		SetCreator (const GS::Guid& pCreatorId, const GS::UniString& pCreatorFullName);
	void		SetLastModifier (const GS::Guid& pLastModifierId, const GS::UniString& pLastModifierFullName);
	void		SetAssignee (const GS::Guid& pAssigneeId, const GS::UniString& pAssigneeFullName);

public:
	GS::UniString	GetCreatorFullName () const;
	GS::UniString	GetLastModifierFullName () const;
	GS::UniString	GetAssigneeFullName () const;

public:
	void			SetRevisionNumber (UInt64 revision) const { revisionNumber = revision; }
	UInt64			GetRevisionNumber () const { return revisionNumber; }
	void			SetWasReceive () const { wasReceive = true; }
	void			ClearWasReceive () const { wasReceive = false; }
	bool			WasReceive () const { return wasReceive; }

	// ... Serialization methods .......................................................................................

public:
	GSErrCode	Read (GS::IChannel& ic) override;

	virtual GSErrCode	WriteIsolatedState (GS::OChannel& oc) const override;
	virtual GSErrCode	ReadIsolatedState (GS::IChannel& ic) override;
	virtual	GSErrCode	WriteTWIsolatedState (GS::OChannel& oc) const override;
	virtual	GSErrCode	ReadTWIsolatedState (GS::IChannel& ic) override;

private:
	GSErrCode		WriteCoreIsolatedStateVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode		ReadCoreIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode		WriteIsolatedStateVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode		ReadIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode		ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

	GSErrCode		WriteTWIsolatedStateVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode		ReadTWIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);


	// ... Transaction management methods ..............................................................................

};

}	// namespace PRMU

#endif		// PRMUASSIGNINFO_HPP