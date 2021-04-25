// *********************************************************************************************************************
// EntryComponent base class
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ENTRYCOMPONENT_HPP)
#define ENTRYCOMPONENT_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "MarkupExport.hpp"
#include "EntryComponentTypes.hpp"

// from VBElements
#include "EDBGeneralDefinitions.hpp"

// from Teamwok
#include "TWObject.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT EntryComponent : public TW::Object
{
	DECLARE_ABSTRACT_DYNAMIC_CLASS(EntryComponent)
protected:
	EntryComponent (const ODB::DynamicClass* finalDynamicClass);

public:
	enum Type {
		Creation,
		Highlight,
		Deletion,
		Modification,
		Unaffected
	};

	EntryComponent ();

	virtual ~EntryComponent () = default;

	EDB::GeneralElemConstRefList			GetRelatedElements () const;
	virtual bool							IsRelatedElement (const EDB::GeneralElemConstRef &elem) const = 0;

	virtual EDB::GeneralElemConstRef		GetElementInModel () const;
	virtual EDB::GeneralElemConstRef		GetElementOutOfModel () const;

	EDB::GeneralElemRefList					GetRelatedElements ();

	virtual EDB::GeneralElemRef				GetElementInModel ();
	virtual EDB::GeneralElemRef				GetElementOutOfModel ();

	struct ConstMethods : public ODB::ConstMethods<EntryComponent> {
		EDB::GeneralElemRef					GetElementInModel ()		{ return GetPtr ()->GetElementInModel (); };
		EDB::GeneralElemRef					GetElementOutOfModel ()		{ return GetPtr ()->GetElementOutOfModel (); };
		EDB::GeneralElemRefList				GetRelatedElements ()		{ return GetPtr ()->GetRelatedElements (); };
	};

	bool									HasElementInModel () const;
	bool									HasElementOutOfModel () const;

	virtual Type							GetElemType (const EDB::GeneralElemConstRef& elem) const;

	virtual void	ConvertToAC22 () {};
};

} // namespace PRMU

#endif