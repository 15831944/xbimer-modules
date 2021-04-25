// *********************************************************************************************************************
// Remark data structure of the MarkupEntry
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	VV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ENTRYREMARK_HPP)
#define ENTRYREMARK_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

// own
#include "MarkupExport.hpp"

// ObjectDatabase
#include "ODBDynamicObject.hpp"

// from VBElements
#include "VBElements/WordTypes.hpp"


namespace PRMU {

// --- Type definitions	------------------------------------------------------------------------------------------------

class MARKUP_DLL_EXPORT EntryRemark : public ODB::DynamicObject
{
	DECLARE_DYNAMIC_CLASS (EntryRemark)
private:
	friend class MarkupEntry;

public:
	EntryRemark ();
	EntryRemark (const EntryRemark& oldRemark);
	EntryRemark (const GS::UniString& _string, VBElem::WordRef _word = nullptr, bool _visible = true);
	EntryRemark (const EntryRemark& source, const EDB::NewElemRefList& newElemList);
	~EntryRemark ();

		// operators
	EntryRemark&	operator=	(const EntryRemark& source);
	bool			operator==	(const EntryRemark& right);
	bool			operator==	(const EntryRemark& right) const;

		// accessors
	const GS::UniString		GetText () const;
	VBElem::WordRef			GetWord ()	const;
	bool					IsPlaced () const;
	bool					IsVisible () const;

		// Modifiers
	bool	SetText				(const GS::UniString& str);

	// Object realization
	virtual GSErrCode		Write	(GS::OChannel& oc, EDB::IElemDatabase* db = nullptr) const;
	virtual GSErrCode		Read	(GS::IChannel& ic, EDB::IElemDatabase* db = nullptr);

private:

	virtual GSErrCode		ReadVersion1	(GS::IChannel& ic, const GS::InputFrame& frame, EDB::IElemDatabase* db);
	virtual GSErrCode		ReadVersion2	(GS::IChannel& ic, const GS::InputFrame& frame);
	virtual GSErrCode		ReadVersion3	(GS::IChannel& ic, const GS::InputFrame& frame);

	virtual GSErrCode		WriteVersion2	(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	virtual GSErrCode		WriteVersion3	(GS::OChannel& oc, const GS::OutputFrame& frame) const;

};


} // namespace PRMU

#endif
