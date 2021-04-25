
// *********************************************************************************************************************
// Holds specific Values
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPTAGVALUE_HPP)
#define MARKUPTAGVALUE_HPP
#endif

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"

// from TWRoot
#include "TWObject.hpp"

// --- Forward declarations	------------------------------------------------------------------------------------------------


// --- Type definitions -------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT TagValue : public TW::Object
{
	DECLARE_DYNAMIC_CLASS (TagValue)
	
	static GS::Guid tagValueMarkupEntryAssocId;
public:
	TagValue ();
	TagValue (const GS::UniString& value);
	TagValue (const TagValue& value);
	virtual ~TagValue ();

	virtual TagValue* Clone () const override;

	GS::UniString GetValue () const;
	void Rename (const GS::UniString& newName);

	static GS::Guid GetTagValueMarkupEntryAssociationId ();
	static void LinkToEntries (const TagValueRef& tagValue, MarkupEntryRefList entries);
	static void DisconnectFromEntries (const TagValueRef& tagValue, MarkupEntryRefList entries);

	MarkupEntryConstRefList GetLinkedEntries () const;
	static MarkupEntryRefList GetLinkedEntries (TagValueRef tagValue);

	static TagValueConstRefList GetLinkedValues (MarkupEntryConstRef entry);
	static TagValueRefList GetLinkedValues (MarkupEntryRef entry);
};
}	//namespace PRMU