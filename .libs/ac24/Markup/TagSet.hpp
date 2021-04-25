
// *********************************************************************************************************************
// Holds specific TagValues
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPTAGSET_HPP)
#define MARKUPTAGSET_HPP
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

class MARKUP_DLL_EXPORT TagSet : public TW::Object
{
	DECLARE_DYNAMIC_CLASS (TagSet)
public:
	TagSet ();
	TagSet (const GS::UniString& name);
	TagSet (const TagSet& oldTagSet);
	virtual ~TagSet ();

	virtual TagSet*			Clone						(void) const override;
	void					Empty						();

	GS::UniString			GetName						(void) const;

	void					UpdateValues				(TagValueRefList newValues);

	static void				AddValues					(TagSetRef tagSet, TagValueRefList valuesToAdd);
	static void				RemoveValues				(TagSetRef tagSet, TagValueRefList valuesToRemove);
	TagValueConstRefList	GetTagValues				() const;
	static TagValueRefList	GetTagValues				(TagSetRef tagSet);

	static TagSetRef		GetTagSetByValue			(TagValueRef value);
	static TagSetConstRef	GetTagSetByValue			(TagValueConstRef value);

	TagValueRef				GetTagValueByString			(const GS::UniString& name);
	TagValueConstRef		GetTagValueByString			(const GS::UniString& name) const;

	static TagValueRef		GetDefaultTagValue			(TagSetRef tagSet);
	static TagValueConstRef GetDefaultTagValue			(TagSetConstRef tagSet);

	static GS::Guid			GetTagSetTagValueAssocId	(void);

	void					GenerateIdForTagValues		(void) const;

	UIndex					GetPosition					(TagValueConstRef value) const;
};
}	//namespace PRMU