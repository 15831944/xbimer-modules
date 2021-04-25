// *********************************************************************************************************************
// Description:		Floor Plan Theoretical Cutting Plane Definition Class As Not Event Source
//
// Module:			VBD
// Namespace:		VBD
// Contact person:	ZM
//
// *********************************************************************************************************************


#ifndef CURRENTSTORYCUTLEVELS_HPP
#define CURRENTSTORYCUTLEVELS_HPP

#pragma once


// === Includes ========================================================================================================

// from GSRoot
#include "Md5.hpp"

// from ElementManager
#include "GeneralElem.hpp"
#include "FloorStructure.hpp"
#include "VBElementsBase/ModelElement.hpp"

#include "VBDocumentExport.hpp"
#include "VBDViewSetting.hpp"
#include "CurrentStoryCutLevelsTypes.hpp"

#include "Real.hpp"


// === Predeclarations =================================================================================================

namespace VBD {
	class ViewSetting;
	using ViewSettingRef      = ODB::Ref<ViewSetting>;
	using ViewSettingConstRef = ODB::ConstRef<ViewSetting>;
}


namespace VBD {


// *********************************************************************************************************************
// class FloorPlanCutLevels
// *********************************************************************************************************************

class VBDOCUMENT_DLL_EXPORT FloorPlanCutLevels final : public TW::Object,
													   public ViewSettingBase
{
	DECLARE_DYNAMIC_CLASS_INFO (FloorPlanCutLevels)

	friend class CurrentStoryCutLevels;
	friend VBDOCUMENT_DLL_EXPORT EDB::StoryWithRange	GetStoryWithRange (const FloorPlanCutLevelsConstRef& floorPlanCutLevels, const EDB::GeneralElemConstRef& elem, short floorNumber);

private:
#define FLOORPLANCUTLEVELS_DATA_MEMBERS						\
	GSTime				lastAttributeTime;					\
	double				currCutLevel;						\
	double				topCutLevel;						\
	double				bottomCutLevel;						\
	short				topCutBaseStoryRelativeIndex;		\
	short				bottomCutBaseStoryRelativeIndex;	\
	double				fixLevel2Absolute0;

	FLOORPLANCUTLEVELS_DATA_MEMBERS
	MD5::FingerPrint	cutDataCheckSum;

	class IsolatedState : public ODB::Object::IsolatedState {
	private:
		friend class FloorPlanCutLevels;

		FLOORPLANCUTLEVELS_DATA_MEMBERS

	public:
		virtual ~IsolatedState ();
	};

public:
	FloorPlanCutLevels ();

	void				operator= (const FloorPlanCutLevelsConstRef& ref);

	bool				Set (double		cutLevelCurrent,
							 double		cutLevelTop,
							 double		cutLevelBottom,
							 short		topStoryRelInd,
							 short		bottomStoryRelIndex,
							 double		levelFix2Absolute0);

	void				Get (double*	cutLevelCurrent,
							 double*	cutLevelTop,
							 double*	cutLevelBottom,
							 short*		topStoryRelInd,
							 short*		bottomStoryRelIndex,
							 double*	levelFix2Absolute0) const;


	double				GetBelowFixAbsoluteLevel (void) const;
	MD5::FingerPrint	GetCutDataCheckSum (void) const;

	bool				operator== (const FloorPlanCutLevels& rightOp) const;
	bool				operator!= (const FloorPlanCutLevels& rightOp) const;

private:
	MD5::FingerPrint				CalcCheckSum (void) const;
	CurrentStoryCutLevelsRef		GetDerivedData (void);
	CurrentStoryCutLevelsConstRef	GetDerivedData (void) const;

	static FloorPlanCutLevels		IsolatedCopyOrCreateDefault            (const FloorPlanCutLevelsConstRef& source);
	static CurrentStoryCutLevels	IsolatedCopyOrCreateDefaultDerivedData (const FloorPlanCutLevelsConstRef& owner);

public: 
	bool				HasDerivedData (void) const;
	static void			CopyDerivedData (const FloorPlanCutLevelsConstRef& from, const FloorPlanCutLevelsRef& to);
	double				GetCutPlaneAbsoluteLevel (void) const;
	double				GetAboveCutPlaneAbsoluteLevel (void) const;
	double				GetBelowPlaneAbsoluteLevel (void) const;
	short				GetCurrentFloor (void) const;

	void				CalculateCutAltitudes	(VBElem::ElemViewDepthLimitations	viewDepth,
												 double*							aboveAltitude,
												 double*							cutAltitude,
												 double*							belowAltitude) const;

	void				CalculateCutLevels		(VBElem::ElemViewDepthLimitations	viewDepth,
												 double*							aboveLevel,
												 double*							cutLevel,
												 double*							belowLevel) const;

	EDB::StoryWithRange	GetCurrStoryWithRange (void) const;

	double				GetCutPlaneLevel (void) const;
	double				GetAboveCutPlaneLevel (void) const;
	double				GetBelowPlaneLevel (void) const;

	double				GetBelowFixLevel (void) const;
	bool				IsRelativeCalculated (void) const;

	GSErrCode			WriteContentForCheckSum (GS::OChannel& oc) const;

// ... Overridden virtual methods (GS::Object) .........................................................................
public:
	virtual FloorPlanCutLevels*				Clone (void) const override;

// ... Transaction management methods ..................................................................................
public:
	virtual GSErrCode						StoreIsolatedState (ODB::Object::IsolatedState* iState) const override;
	virtual GSErrCode						RestoreIsolatedState (const ODB::Object::IsolatedState* iState) override;
	virtual void							Isolate (void) override;
	virtual ODB::Object::IsolatedState*		CreateIsolatedState (void) const override;
	virtual USize							GetIsolatedSize (void) const override;
	virtual GSErrCode						ReadIsolatedState (GS::IChannel& ic) override;
	virtual GSErrCode						WriteIsolatedState (GS::OChannel& oc) const override;

private:
	GSErrCode								ReadIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& iFrame);
	GSErrCode								WriteIsolatedStateVersion1 (GS::OChannel& oc, const GS::OutputFrame& oFrame) const;
	GSErrCode								ReadCoreIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& /*iFrame*/);
	GSErrCode								WriteCoreIsolatedStateVersion1 (GS::OChannel& oc, const GS::OutputFrame& /*oFrame*/) const;

public:
	virtual GSErrCode						ReadTWIsolatedState (GS::IChannel& ic) override;
	virtual GSErrCode						WriteTWIsolatedState (GS::OChannel& oc) const override;

private:
	GSErrCode								ReadTWIsolatedStateVersionLast (GS::IChannel& ic, const GS::InputFrame& iFrame);
	GSErrCode								WriteTWIsolatedStateVersionLast (GS::OChannel& oc, const GS::OutputFrame& oFrame) const;

// ... XML serialization ...............................................................................................
public:
	virtual GSErrCode						ReadIsolatedStateXML (GS::XMLIChannel& ix) override;
	virtual GSErrCode						WriteIsolatedStateXML (GS::XMLOChannel& ox) const override;

// ... Link management .................................................................................................
public:
	static ODB::Association11<ViewSetting, FloorPlanCutLevels>&	GetViewSettingAssociationID (void);
	static FloorPlanCutLevelsConstRef							GetAttribute (FloorPlanCutLevelsConstRef floorPlanCutLevels);
	static FloorPlanCutLevelsRef								GetAttribute (FloorPlanCutLevelsRef floorPlanCutLevels);

	GS::UniString							GetStoredName (void) const;
	void									SetLastConnectionTime (const GSTime& value);
	const GSTime&							GetLastConnectionTime (void) const;
	virtual bool							HasAttribute (void) const override;
	void									SetAttribute (FloorPlanCutLevelsRef dummy);

	bool									IsDerivedDataEqual (const CurrentStoryCutLevelsConstRef currentStoryCutLevels) const;
};


// *********************************************************************************************************************
// class CurrentStoryCutLevels
// *********************************************************************************************************************

class VBDOCUMENT_DLL_EXPORT CurrentStoryCutLevels final : public TW::Object {
	DECLARE_DYNAMIC_CLASS_INFO (CurrentStoryCutLevels)

	friend class FloorPlanCutLevels;
	friend VBDOCUMENT_DLL_EXPORT EDB::StoryWithRange	GetStoryWithRange (const FloorPlanCutLevelsConstRef& floorPlanCutLevels, const EDB::GeneralElemConstRef& elem, short floorNumber);

private:
	// temporary data dependent from the current story
#define CURRENTSTORYCUTLEVELS_DATA_MEMBERS			\
	bool				relativeCalculated;			\
	double				currCutLevelCalculated;		\
	double				topCutLevelCalculated;		\
	double				currentStoryLevel;			\
	double				topBase2Current;			\
	double				bottomBase2Current;			\
	short				currentFloorIndex;

	CURRENTSTORYCUTLEVELS_DATA_MEMBERS

private:
	class IsolatedState : public ODB::Object::IsolatedState {
	private:
		friend class CurrentStoryCutLevels;

		CURRENTSTORYCUTLEVELS_DATA_MEMBERS

	public:
		virtual ~IsolatedState ();
	};

private:
	CurrentStoryCutLevels ();

	bool				Set (double		cutLevelCurrent,
							 double		cutLevelTop,
							 double		cutLevelBottom,
							 short		topStoryRelInd,
							 short		bottomStoryRelIndex,
							 double		levelFix2Absolute0);

	void				Get (double*	cutLevelCurrent,
							 double*	cutLevelTop,
							 double*	cutLevelBottom,
							 short*		topStoryRelInd,
							 short*		bottomStoryRelIndex,
							 double*	levelFix2Absolute0) const;

	void				SetCurrentFloor (const FloorPlanCutLevels& floorPlanCutLevels, const EDB::FloorStructureConstRef& floorStructure, short floorIndex);
	short				GetCurrentFloor (void) const;

public:
	bool				operator== (const CurrentStoryCutLevels& rightOp) const;
	bool				operator!= (const CurrentStoryCutLevels& rightOp) const;

	static void			SetCurrentFloor (const FloorPlanCutLevelsRef& floorPlanCutLevelsRef, const EDB::FloorStructureConstRef& floorStructure, short floorIndex);
	static short		GetCurrentFloor (FloorPlanCutLevelsConstRef floorPlanCutLevelsRef);

private:
	double				GetCutPlaneAbsoluteLevel (void) const;
	double				GetAboveCutPlaneAbsoluteLevel (void) const;
	double				GetBelowPlaneAbsoluteLevel (const FloorPlanCutLevels& owner) const;

	void				CalculateCutAltitudes	(VBElem::ElemViewDepthLimitations	viewDepth,
												 double*							aboveAltitude,
												 double*							cutAltitude,
												 double*							belowAltitude) const;

	void				CalculateCutLevels		(VBElem::ElemViewDepthLimitations	viewDepth,
												 double*							aboveLevel,
												 double*							cutLevel,
												 double*							belowLevel) const;

	EDB::StoryWithRange	GetCurrStoryWithRange (const FloorPlanCutLevels& owner) const;

	double				GetCutPlaneLevel (void) const;
	double				GetAboveCutPlaneLevel (void) const;
	double				GetBelowPlaneLevel (void) const;

	double				GetBelowFixLevel (void) const;
	bool				IsRelativeCalculated (void) const;

// ... Core Data Setters getters .......................................................................................
private:
	FloorPlanCutLevelsConstRef		GetFloorPlanCutLevels (void) const;
	FloorPlanCutLevelsRef			GetFloorPlanCutLevels (void);

// ... Overridden virtual methods (GS::Object) .........................................................................
public:
	virtual CurrentStoryCutLevels*			Clone (void) const override;

// ... Transaction management methods ..................................................................................
public:
	virtual GSErrCode						StoreIsolatedState (ODB::Object::IsolatedState* iState) const override;
	virtual GSErrCode						RestoreIsolatedState (const ODB::Object::IsolatedState* iState) override;
	virtual void							Isolate (void) override;
	virtual ODB::Object::IsolatedState*		CreateIsolatedState (void) const override;
	virtual USize							GetIsolatedSize (void) const override;
	virtual GSErrCode						ReadIsolatedState (GS::IChannel& ic) override;
	virtual GSErrCode						WriteIsolatedState (GS::OChannel& oc) const override;

private:
	GSErrCode								ReadIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& iFrame);
	GSErrCode								WriteIsolatedStateVersion1 (GS::OChannel& oc, const GS::OutputFrame& oFrame) const;
	GSErrCode								ReadCoreIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& /*iFrame*/);
	GSErrCode								WriteCoreIsolatedStateVersion1 (GS::OChannel& oc, const GS::OutputFrame& /*oFrame*/) const;

public:
	virtual GSErrCode						ReadTWIsolatedState (GS::IChannel& ic) override;
	virtual GSErrCode						WriteTWIsolatedState (GS::OChannel& oc) const override;

private:
	GSErrCode								ReadTWIsolatedStateVersionLast (GS::IChannel& ic, const GS::InputFrame& iFrame);
	GSErrCode								WriteTWIsolatedStateVersionLast (GS::OChannel& oc, const GS::OutputFrame& oFrame) const;

// ... XML serialization ...............................................................................................
public:
	virtual GSErrCode						ReadIsolatedStateXML (GS::XMLIChannel& ix) override;
	virtual GSErrCode						WriteIsolatedStateXML (GS::XMLOChannel& ox) const override;
};


// *********************************************************************************************************************
// class FloorPlanCutLevelsGuard
// *********************************************************************************************************************

class VBDOCUMENT_DLL_EXPORT FloorPlanCutLevelsGuard final {
public:
	explicit FloorPlanCutLevelsGuard (const FloorPlanCutLevelsConstRef& ref = nullptr);

	FloorPlanCutLevelsGuard (FloorPlanCutLevelsGuard&& source) = default;	// disables copying and move assignment

	FloorPlanCutLevelsRef		GetFloorPlanCutLevels ();
	FloorPlanCutLevelsConstRef	GetFloorPlanCutLevels () const;

private:
	FloorPlanCutLevels			floorPlanLevels;
};



// *********************************************************************************************************************
// Global functions
// *********************************************************************************************************************

struct FloorAltitudes {
	double aboveAltitude;
	double cutAltitude;
	double belowAltitude;
};


VBDOCUMENT_DLL_EXPORT EDB::StoryWithRange	GetStoryWithRange   (const FloorPlanCutLevelsConstRef& floorPlanCutLevels, const EDB::GeneralElemConstRef& elem, short floorNumber);
VBDOCUMENT_DLL_EXPORT double				GetFloorCutAltitude (const EDB::FloorStructureConstRef& floorStructure, const FloorPlanCutLevelsConstRef& floorPlanCutLevels, short floorNumber);
VBDOCUMENT_DLL_EXPORT FloorAltitudes		GetFloorAltitudes   (const EDB::FloorStructureConstRef& floorStructure, const FloorPlanCutLevelsConstRef& floorPlanCutLevels, short floorNumber);


}	// namespace VBD


#endif
