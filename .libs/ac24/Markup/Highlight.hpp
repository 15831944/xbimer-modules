// *********************************************************************************************************************
// Contains Highlighted elements of a Markup
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (HIGHLIGHT_HPP)
#define HIGHLIGHT_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "EntryComponent.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------
// --- Type definitions	------------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT Highlight : public EntryComponent
{
	DECLARE_DYNAMIC_CLASS (Highlight)
private:
	Highlight ();
	Highlight (const Highlight& source);
public:
	Highlight (EDB::GeneralElemRef elem);
	
	virtual ~Highlight () = default;

	virtual Highlight*						Clone () const override;

	EDB::GeneralElemConstRef				GetElementInModel () const override;
	EDB::GeneralElemRef						GetElementInModel () override;
	PRMU::EntryComponent::Type	GetElemType (const EDB::GeneralElemConstRef& elem) const override;
	static EntryComponentConstRefList		GetComponents (const EDB::GeneralElemConstRef& elem);

	virtual bool IsRelatedElement			(const EDB::GeneralElemConstRef &elem) const override;

	static bool								IsRelatedElementStatic (const EDB::GeneralElemConstRef& elem);
};

} // namespace PRMU

#endif