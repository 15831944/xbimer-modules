// *********************************************************************************************************************
// Remark data stucture of the MarkupEntry
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (REMARK_HPP)
#define REMARK_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

// own
#include "EntryComponent.hpp"

// VBElement
#include "WordTypes.hpp"

namespace PRMU {

// --- Type definitions	------------------------------------------------------------------------------------------------

class MARKUP_DLL_EXPORT Remark : public EntryComponent
{
	DECLARE_DYNAMIC_CLASS (Remark)
private:
	friend class MarkupEntry;

public:
	Remark ();
	Remark (const Remark& source);
	Remark (const GS::UniString& _string, bool _visible = true);
	Remark (EDB::GeneralElemRef elem, const GS::UniString& _string, bool _visible = true);
	virtual ~Remark () = default;

	virtual Remark* Clone () const override;
		// accessors
	const GS::UniString		GetText   () const;
	bool					IsPlaced  () const;
	bool					IsVisible () const;

	EDB::GeneralElemConstRef	GetElementOutOfModel () const override;
	EDB::GeneralElemRef			GetElementOutOfModel () override;

	VBElem::WordRef				GetWord ();
	VBElem::WordConstRef		GetWord () const;

		// Modifiers
	bool					SetText	(const GS::UniString& str);
	void					SetWord (EDB::GeneralElemRef newWord);
	void					RemoveWord ();
	void					ChangeVisibility (bool newVisibility);

	static EntryComponentConstRefList		GetComponent (EDB::GeneralElemConstRef);

	virtual bool			IsRelatedElement (const EDB::GeneralElemConstRef &elem) const override;

	static bool								IsRelatedElementStatic (EDB::GeneralElemConstRef elem);
};


} // namespace PRMU

#endif
