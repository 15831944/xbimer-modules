// *********************************************************************************************************************
// A snapshot of the MarkupEntry
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (ENTRYVIEW_HPP)
#define ENTRYVIEW_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Geometry
#include "Vector3D.hpp"

// from TWRoot
#include "TWObject.hpp"

// Markup - own
#include "EntryComponentTypes.hpp"
#include "MarkupExport.hpp"
#include "MarkupTypes.hpp"
#include "MarkupEntry.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------
namespace EDB {
class GeneralElem;
typedef ODB::Ref<EDB::GeneralElem> GeneralElemRef;
typedef ODB::ConstRef<EDB::GeneralElem> GeneralElemConstRef;
typedef ODB::ConstRefList<EDB::GeneralElem> GeneralElemConstRefList;
}

namespace PN {
class CaptureData;
typedef ODB::Ref<CaptureData> CaptureDataRef;
typedef ODB::ConstRef<CaptureData> CaptureDataConstRef;
}

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace PRMU {

class MARKUP_DLL_EXPORT EntryView : public TW::Object
{
	DECLARE_DYNAMIC_CLASS (EntryView)

private:								
	friend class MarkupEntry;			

public:
	EntryView ();

	EntryView (GS::Guid mGuid,
			   GS::UniString fileName);

	EntryView (GS::Guid mGuid,
			   GS::UniString fileName,
			   Geometry::Coord3D mLocation,
			   Geometry::Vector3D normalVector,
			   Geometry::Vector3D upVector);

	EntryView (const EntryView& source) : TW::Object (source) {	};

	~EntryView ();

	EntryView*			Clone () const override;

	GS::Guid			GetIdForBCF () const;
	GS::Guid			GetGuid () const;
	GS::UniString		GetName () const;
	void				Rename (GS::UniString newName);

	Geometry::Coord3D	GetLocation () const;
	Geometry::Vector3D	GetNormalVector () const;
	Geometry::Vector3D	GetUpVector () const;

	void				GenerateNameWithGuid ();

	void				LinkComponents (EntryComponentRefList);
	void				RemoveComponents (EntryComponentRefList);
	
	bool				ContainsComponent (EntryComponentConstRef component) const;
	bool				ContainsElement (EDB::GeneralElemConstRef elem) const;
	bool				HasComponents () const;

	EntryComponentConstRefList				GetComponents () const;
	EntryComponentConstRefList				GetComponentsByType (EntryComponent::Type type) const;
	RemarkConstRefList						GetRemarks () const;

	EDB::GeneralElemConstRefList			GetRelatedElements () const;
	EDB::GeneralElemConstRefList			GetSuggestionForModificationInModelElements () const;
	EDB::GeneralElemConstRefList			GetElementsByComponentType (PRMU::EntryComponent::Type type) const;
	EDB::GeneralElemConstRefList			GetRemarkElements () const;
	EDB::GeneralElemConstRefList			GetElementsInModel () const;
	EDB::GeneralElemConstRefList			GetElementsOutOfModel () const;

	static EntryViewConstRefList			GetEntryViews (EntryComponentConstRef);
	static EntryViewConstRefList			GetEntryViewsByElem (EDB::GeneralElemConstRef);
	static EntryViewConstRefList			GetEntryViewsInModel (EDB::GeneralElemConstRef);
	static EntryViewConstRefList			GetEntryViewsOutOfModel (EDB::GeneralElemConstRef);

	static EntryComponentRefList			GetComponents (EntryViewRef);
	static EntryComponentConstRefList		GetComponentsByElem (EDB::GeneralElemConstRef);
	static EntryComponentConstRefList		GetComponentsInModel (EDB::GeneralElemConstRef);
	static EntryComponentConstRefList		GetComponentsOutOfModel (EDB::GeneralElemConstRef);

	static PN::CaptureDataRef				GetCaptureDataOfEntryView (PRMU::EntryViewRef view);
	static PN::CaptureDataConstRef			GetCaptureDataOfEntryView (PRMU::EntryViewConstRef view);
	static PRMU::EntryViewRef				GetEntryViewOfCaptureData (PN::CaptureDataRef captureData);
	static PRMU::EntryViewConstRef			GetEntryViewOfCaptureData (PN::CaptureDataConstRef captureData);
	void									SetCaptureDataForEntryView (const PN::CaptureDataRef& newCaptureData);
	void									RemoveCaptureDataOfEntryView ();
	void									ReleaseCaptureDataOfEntryView ();
};

} // namespace PRMU

#endif