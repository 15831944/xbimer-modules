// *********************************************************************************************************************
// Description:		GDL Global handling utilities
//
// Module:			VBElemOperations
// Namespace:
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GDLGLOBALOPERATIONS_HPP
#define	GDLGLOBALOPERATIONS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

// from GSUtils
#include	"GSUnID.hpp"

// from InputOutput
#include	"FileTypeManager.hpp"

// from Graphics
#include	"GSPix.h"

// from GDL
#include	"GDLDefs.h"
#include	"GDLbits.h"
#include	"GDLParamTypes.hpp"

// from VectorImage
#include	"ProfileFillData.hpp"

// from ElementManager
#include	"EDBGeneralDefinitions.hpp"
#include	"ElementManagerTypes.hpp"
#include	"ProjectTypes.hpp"
#include	"VBElemSet/ElemSetType.hpp"

// from VBAttributes
#include	"EffectiveComposite.hpp"

// from VBElements
#include	"VBElements/GDLBasedElemTypes.hpp"
#include	"VBElements/LabelTypes.hpp"
#include	"VBElements/OpeningFillerTypes.hpp"
#include	"VBElements/WallOpeningFillerTypes.hpp"
#include	"VBElements/WallTypes.hpp"
#include	"VBElements/ShellTypes.hpp"
#include	"VBElements/CeilTypes.hpp"
#include	"VBElements/StairTypes.hpp"
#include	"VBElements/CrossSectType.hpp"
#include	"VBElements/NumFormat.hpp"
#include	"VBElements/OpeningSymbolParameters.hpp"
#include	"VBElements/OpeningSymbolTypes.hpp"
#include	"VBElements/OpeningExtrusionParameters.hpp"
#include	"VBElementsBase/ModelElementDefault.hpp"

// from LibraryManager
#include	"FileServices.hpp"

// from VBCalculations
#include	"GDLGlobalCalculations.hpp"

// from VBElemOperations
#include	"StairModelViewOption.hpp"
#include	"RailingModelViewOption.hpp"
#include	"CurtainWallModelViewOption.hpp"
#include	"VBElemOperationsTypes.hpp"

// from Phasing
#include	"PhasingTypes.hpp"

// from GSModeler
#include	"SunPosition.hpp"

// from Geometry
#include "Poly2DTypes.hpp"


#define	SkinDownPriorityCorr	10100
#define	SkinUpperPriorityCorr	20200
#define	SkinEmptyPriorityCorr	30300

// WDEXPR.H
#define EXPR_THICKGUSED		(1<<0) // Globals used in door/window thick expr
#define EXPR_INSETGUSED		(1<<1) // Globals used in door/window par. wall inset expr
#define EXPR_LFRAMGUSED		(1<<2) // Globals used in door/window wdLeftFram expr
#define EXPR_RFRAMGUSED		(1<<3) // Globals used in door/window wdRighFram expr
#define EXPR_TFRAMGUSED		(1<<4) // Globals used in door/window wdTopFram expr
#define EXPR_BFRAMGUSED		(1<<5) // Globals used in door/window wdBotFram expr
#define EXPR_THICK_STORED	(1<<6) // wdExprBits stored thick values
#define EXPR_INSET_STORED	(1<<7) // wdExprBits stored inset values
#define EXPR_LFRAM_STORED	(1<<8)  // wdExprBits stored left frame values	// FE #23919
#define EXPR_RFRAM_STORED	(1<<9)  // wdExprBits stored right frame values
#define EXPR_TFRAM_STORED	(1<<10) // wdExprBits stored top frame values
#define EXPR_BFRAM_STORED	(1<<11) // wdExprBits stored bottom frame values


class DetailHandler;

namespace LM {
	class AncestryInfo;
	class LibPart;
	class LibrarySet;
}

namespace EDB {
	class DefaultElem;
	class IElemDefaults;
}

namespace VBElem {
	class WallDefault;
	class WallOpeningFillerDefault;
	class OpeningFillerDefault;
	class SkylightDefault;
	class GDLObjectDefault;
	class SectionBaseDefault;
	class LabelDefault;
	class RoomDefault;
}

namespace ADB {
	class AttributeSet;
	typedef ODB::ConstRef<AttributeSet> AttributeSetConstRef;
}

namespace GDL {
	class ParamList;
	class Parameters;
	class GDLRequestComponentId;
}

class ComponentIndex;
struct OrientDispRec; 

namespace LPF {
	class SymbolFile;
}

namespace CompInfo {
	class CompositeInfo;
	class AttributeGetter;
}

namespace VBCalculations {
	struct WallCutPlaneData;
}

namespace VBD {
	class FloorPlanCutLevels;
	typedef ODB::Ref<FloorPlanCutLevels> FloorPlanCutLevelsRef;
	typedef ODB::ConstRef<FloorPlanCutLevels> FloorPlanCutLevelsConstRef;
}

class VectorImage;
class Box2DData;
class LibPartHandlerRegistry;
class IPropertyBasedReader;
class IPropertyBasedReaderFactory;


class SymbolParametersSectionContent;

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace VBCalculations {

struct CW2StructRec;

class VB_ELEM_OPERATIONS_DLL_EXPORT IGDLLibraryEnvironment
{
public:
	virtual ~IGDLLibraryEnvironment ();

	virtual FileServices*								GetFileServices () const = 0;
	virtual const LibPartHandlerRegistry*				GetLibPartHandlerRegistry () const = 0;
	virtual const LM::LibrarySet::ThreadSafeModifier&	GetLibrarySetTSModifier () const = 0;

	virtual const FTM::GroupID&			GetSymbolFiles () const = 0;
	virtual const FTM::TypeID&			GetGdlFile () const = 0;
	virtual const FTM::GroupID&			GetAllImgFiles () const = 0;
	virtual const FTM::TypeID&			GetListSetupFile () const = 0;
	virtual const FTM::GroupID&			GetAllTextFiles () const = 0;
	virtual const FTM::TypeID&			GetBinListCritFile () const = 0;
	virtual const FTM::TypeID&			GetIesFile () const = 0;

	virtual GS::UnID					GetLibraryGlobalSettingsID () const = 0;
	virtual GS::UnID					GetModelElemID () const = 0;
	virtual GS::UnID					GetPropertiesID () const = 0;
	virtual GS::UnID					GetWallDoorID () const = 0;
	virtual GS::UnID					GetWallWindowID () const = 0;
	virtual GS::UnID					GetZoneStampID () const = 0;
	virtual GS::UnID					GetLightID () const = 0;
	virtual GS::UnID					GetSectionMarkerID () const = 0;
	virtual GS::UnID					GetSectElevBaseMarkerID () const = 0;
	virtual GS::UnID					GetElevationMarkerID () const = 0;
	virtual GS::UnID					GetCommonIntElevationMarkerID () const = 0;
	virtual GS::UnID					GetIntElevationMarkerID () const = 0;
	virtual GS::UnID					GetDetailMarkerID () const = 0;
	virtual GS::UnID					GetWorksheetMarkerID () const = 0;
	virtual GS::UnID					GetChangeMarkerID () const = 0;
	virtual GS::UnID					GetLabelID () const = 0;
	virtual GS::UnID					GetRoofOpeningID () const = 0;
	virtual GS::UnID					GetDesignStair2DComponentID () const = 0;
	virtual GS::UnID					GetWindowMarkerID () const = 0;
	virtual GS::UnID					GetDoorMarkerID () const = 0;
	virtual GS::UnID					GetSkylightMarkerID () const = 0;
	virtual GS::UnID					GetWindowDoorSkylightMarkerID () const = 0;
	virtual GS::UnID					GetOpeningSymbolID () const = 0;

};


struct	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLGlobalCalcEnvir : public IGDLLibraryEnvironment
{
// private:
// 	GDLGlobalCalcEnvir (const GDLGlobalCalcEnvir&);
// 	GDLGlobalCalcEnvir& operator = (const GDLGlobalCalcEnvir& src);
private:
	VBD::FloorPlanCutLevelsRef				floorPlanCutLevels;
public:
	EDB::ProjectConstRef			proj;
	Geometry::Vector2d				offset;

	const EDB::IElemDefaults*		currDef;

	double							listLayoutScale;
	double							dScaleLibrItem;
	double							spec_dScale;
	double							currEn_dScale;
	double							northDirection;
	double							longitude;
	double		    				latitude;
	double							altitude;

	// TODO: ezek kozul csak egy csoport kell!
	SunAngleSettings				plan3d_sunAngSets;
	double							plan3d_viewX;
	double							plan3d_viewY;
	double							plan3d_viewZ;
	double							plan3d_objX;
	double							plan3d_objY;
	double							plan3d_objZ;

	SunAngleSettings				symb3d_sunAngSets;
	double							symb3d_viewX;
	double							symb3d_viewY;
	double							symb3d_viewZ;
	double							symb3d_objX;
	double							symb3d_objY;
	double							symb3d_objZ;
	// -----------------------------------------

	GS_RGBColor						bkgColorRGB;
	EffectiveComposite::Structure	structure;

	FileServices*						fileServices;
	LM::LibrarySet::ThreadSafeModifier	librarySetTSModifier;
	const LibPartHandlerRegistry*		libPartHandlerRegistry;

	virtual FileServices*								GetFileServices () const override;
	virtual const LibPartHandlerRegistry*				GetLibPartHandlerRegistry () const override;
	virtual const LM::LibrarySet::ThreadSafeModifier&	GetLibrarySetTSModifier () const override;

	GS::UniString					archiCADLayerName;
	GS::UnID						wallEndID;
	GS::UnID						zoneStampID;
	GS::UnID						modelElemID;
	GS::UnID						wallDoorID;
	GS::UnID						wallWindowID;
	GS::UnID						lightID;
	GS::UnID						sectionMarkerID;
	GS::UnID						sectElevBaseMarkerID;
	GS::UnID						elevationMarkerID;
	GS::UnID						commonIntElevationMarkerID;
	GS::UnID						intElevationMarkerID;
	GS::UnID						detailMarkerID;
	GS::UnID						worksheetMarkerID;
	GS::UnID						changeMarkerID;
	GS::UnID						labelID;
	GS::UnID						roofOpeningID;
	GS::UnID						propertiesID;
	GS::UnID						libraryGlobalSettingsID;
	GS::UnID						wallExtraWindowID;
	GS::UnID						designStair2DComponentID;
	GS::UnID						pointCloudID;
	GS::UnID						pointCloudReplacementObjectID;
	GS::UnID						windowDoorSkylightMarkerID;
	GS::UnID						windowMarkerID;
	GS::UnID						doorMarkerID;
	GS::UnID						skylightMarkerID;
	GS::UnID						openingSymbolID;

	virtual GS::UnID						GetLibraryGlobalSettingsID () const override;
	virtual GS::UnID						GetModelElemID () const override;
	virtual GS::UnID						GetPropertiesID () const override;
	virtual GS::UnID						GetWallDoorID () const override;
	virtual GS::UnID						GetWallWindowID () const override;
	virtual GS::UnID						GetZoneStampID () const override;
	virtual GS::UnID						GetLightID () const override;
	virtual GS::UnID						GetSectionMarkerID () const override;
	virtual GS::UnID						GetSectElevBaseMarkerID () const override;
	virtual GS::UnID						GetElevationMarkerID () const override;
	virtual GS::UnID						GetCommonIntElevationMarkerID () const override;
	virtual GS::UnID						GetIntElevationMarkerID () const override;
	virtual GS::UnID						GetDetailMarkerID () const override;
	virtual GS::UnID						GetWorksheetMarkerID () const override;
	virtual GS::UnID						GetChangeMarkerID () const override;
	virtual GS::UnID						GetLabelID () const override;
	virtual GS::UnID						GetRoofOpeningID () const override;
	virtual GS::UnID						GetDesignStair2DComponentID () const override;
	virtual GS::UnID						GetWindowMarkerID () const override;
	virtual GS::UnID						GetDoorMarkerID () const override;
	virtual GS::UnID						GetSkylightMarkerID () const override;
	virtual GS::UnID						GetWindowDoorSkylightMarkerID () const override;
	virtual GS::UnID						GetOpeningSymbolID () const override;



	GS::Array<GS::UnID>				all2DElementsSubTypeIDs;

	StairModelViewOption			stairMVO;
	RailingModelViewOption			railingMVO;
	GS::UnID						treadSchematicMVOID;
	GS::UnID						riserSchematicMVOID;
	CurtainWallModelViewOption		curtainWallMVO;

	FTM::GroupID					symbolFiles;
	FTM::TypeID						gdlFile;
	FTM::GroupID					allImgFiles;
	FTM::TypeID						listSetupFile;
	FTM::GroupID					allTextFiles;
	FTM::TypeID						binListCritFile;
	FTM::TypeID						iesFile;

	virtual const FTM::GroupID&				GetSymbolFiles () const override;
	virtual const FTM::TypeID&				GetGdlFile () const override;
	virtual const FTM::GroupID&				GetAllImgFiles () const override;
	virtual const FTM::TypeID&				GetListSetupFile () const override;
	virtual const FTM::GroupID&				GetAllTextFiles () const override;
	virtual const FTM::TypeID&				GetBinListCritFile () const override;
	virtual const FTM::TypeID&				GetIesFile () const override;


	ADB::AttributeSetConstRef		attributes;

	GS::UniString					windRight;
	GS::UniString					windLeft;
	GS::UniString					doorRight;
	GS::UniString					doorLeft;

	GS::Array<GS::Array<GS::UniString>>		globIssueScheme;
	GS::Array<GS::Array<GS::UniString>>		globChangeScheme;
	GS::Array<GS::Array<GS::UniString>>		layoutRevisionHistory;
	GS::Array<GS::Array<GS::UniString>>		layoutChangeHistory;
	bool									layoutCurrentRevisionOpen;

	ADB::AttributeIndex						emptyHatchIndex;
	ADB::AttributeIndex						solidHatchIndex;

	bool							pbcConversion;

	ConstLibraryMVODataContainerPtr	libraryMVODataContainer;

	GDLGlobalCalcEnvir (void);
	virtual ~GDLGlobalCalcEnvir ();

	GDLGlobalCalcEnvir& operator= (const GDLGlobalCalcEnvir& source);
	GDLGlobalCalcEnvir (const GDLGlobalCalcEnvir& source);

	bool EqualForDebug (const GDLGlobalCalcEnvir& rhs) const;

	const ODB::ConstRef<VBD::FloorPlanCutLevels>& GetFloorPlanCutLevels () const
	{
		return floorPlanCutLevels.AsConst ();
	}
	void SetFloorPlanCutLeves (const ODB::ConstRef<VBD::FloorPlanCutLevels>& floorPlanCutLevels);
};



enum	VB_ELEM_OPERATIONS_DLL_EXPORT	CompResult {
	Comp_Invalid = 0,
	Comp_Invis   = 1,
	Comp_OK      = 2
};


enum	VB_ELEM_OPERATIONS_DLL_EXPORT	GlobalsMode { PlanMode, LibPartMode };


// --- Function declarations -------------------------------------------------------------------------------------------

enum	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLDiagnosticMode { DiagnosticModeOff, DiagnosticModeOn };

void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetFloorGdlGlobals_NoLabels (	GDL::ParameterAccessor&			globHdl,
																		const LM::LibPart*				libPart,
																		short							idElem,
																		const EDB::GeneralElemConstRef& elem,
																		const IPropertyBasedReaderFactory& elemReaderFactory,
																		GDL_ScriptType					scriptType,
																		GDLContext						context,
																		GlobalsMode						mode,
																		bool							setThickExpr,
																		bool							setInsetExpr,
																		bool							setFrameExpr,
																		const Int32*					globalsBits,
																		const GDLGlobalCalcEnvir&		gdlGlobals,
																		double							viewAngle = 0.0,
																		const EDB::DefaultElem*			slDat = nullptr,
																		short							labelParentIdElem = 0,
																	    GDLDiagnosticMode				gdlDiagnosticMode = DiagnosticModeOff);

class VB_ELEM_OPERATIONS_DLL_EXPORT IGetWallDefault {
public:
	virtual const VBElem::WallDefault* operator () () = 0;
	virtual ~IGetWallDefault ();
};

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetCutPlanesInfo (const EDB::GeneralElemConstRef&		elemPtr,
														  const IPropertyBasedReaderFactory&	elemReaderFactory,
														  const GDLGlobalCalcEnvir&				gdlGlobals,
														  const VBElem::OpeningFillerDefault*	wdDat,
														  const VBElem::GDLObjectDefault*		slDat,
														  IGetWallDefault*						getWallDef,
														  short									symbTyp,
														  double*								height,
														  double*								topLevel,
														  double*								botLevel,
														  double*								absolute);

void 	VB_ELEM_OPERATIONS_DLL_EXPORT	CalcHoleThickness (VBElem::WallConstRef pWall2, const VBElem::WallOpeningFillerConstRef& pHole,
														   const IPropertyBasedReaderFactory& elemReaderFactory, const GDLGlobalCalcEnvir& gdlGlobals,
														   double *holeThick);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetWidoHeadHeight (const VBElem::WallOpeningFillerConstRef& pHole,
														   const IPropertyBasedReaderFactory& elemReaderFactoryFactory,
														   const GDLGlobalCalcEnvir& gdlGlobals,
														   double *headHeight,
														   double *rSideHeadHeight,
														   double *oprSideHeadHeight);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetWidoOrientation (const VBElem::WallOpeningFillerConstRef&	pHole, const LM::LibrarySet* librarySet,
															const GS::UniString& windowRightOrientation, const GS::UniString& windowLeftOrientation,
															const GS::UniString& doorRightOrientation, const GS::UniString& doorLeftOrientation,
															GS::UniString& widoOrientation);	/* Gdl_WIDO_ORIENTATION */

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLExpr_Inset (const LM::LibPart*						libPart,
														  const GDLGlobalCalcEnvir&					gdlGlobals,
														  const VBElem::WallOpeningFillerConstRef&	elem,
														  const IPropertyBasedReaderFactory&		elemReaderFactory,
														  const GDL::ParameterGetter&				addParHdl,
														  double*									wdWallInset,
														  GDLContext								context,
														  GlobalsMode								mode);

GSErr	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLExpr_Frame (const LM::LibPart*					libPart,
														  const GDLGlobalCalcEnvir&				gdlGlobals,
														  const VBElem::OpeningFillerConstRef&  hole,
														  const IPropertyBasedReaderFactory&	elemReaderFactory,
														  double*								wdLeftFram,
														  double*								wdRighFram,
														  double*								wdTopFram,
														  double*								wdBotFram,
														  const GDL::ParameterGetter&			addParHdl,
														  GDL::Parameters*						globHdl = nullptr,
														  bool									forceRecalculate = false);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLExpr_Thick (const LM::LibPart*					libPart,
														  const GDLGlobalCalcEnvir&				gdlGlobals,
														  const VBElem::WallOpeningFillerConstRef&	elem,
														  const IPropertyBasedReaderFactory&		elemReaderFactory,
														  const GDL::ParameterGetter&				addParHdl,
														  double*									wdMirThick);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLExpr_ThickByElem (const VBElem::WallOpeningFillerConstRef&	elem,
																const IPropertyBasedReaderFactory&			elemReaderFactory,
															    const GDLGlobalCalcEnvir&					gdlGlobals,
																double*										wdMirThick);

GSErr	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLExpr_OpeningFrame (const VBElem::WallOpeningFillerConstRef&	hole,
																 const IPropertyBasedReaderFactory&			elemReaderFactory,
																 const GDLGlobalCalcEnvir&					gdlGlobals,
																 double*									wdLeftFram,
																 double*									wdRighFram,
																 double*									wdTopFram,
																 double*									wdBotFram);

EDB::GeneralElemConstRef VB_ELEM_OPERATIONS_DLL_EXPORT GetGDLBasedElem (const EDB::GeneralElemConstRef& elem);

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLParamWidthHeight (const LM::LibPart*				libPart,
																const IGDLLibraryEnvironment&			libraryEnvironment,
																const EDB::GeneralElemConstRef&	elem,
																double*							parWidth,
																double*							parHeight);


Int32	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLWallCrossSectType (CrossSectType vbElemCrossSectType);

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetGDLParamData (const LM::LibPart*					libPart,
														 const GDLGlobalCalcEnvir&			gdlGlobals,
														 const EDB::GeneralElemConstRef&	elem,
														 bool								isProp,
														 GDL::Parameters&					addPar,
														 GS::UInt64*						transientId = nullptr,
														 double*							parA = nullptr,
														 double*							parB = nullptr);

Owner<GDL::ParameterGetter> VB_ELEM_OPERATIONS_DLL_EXPORT CreateAddParInterface (	const LM::LibPart*					libPart,
																					const GDLGlobalCalcEnvir&			gdlGlobals,
																					const EDB::GeneralElemConstRef&		elem,
																					const GDL::ParameterGetter*			addParHdl);

VB_ELEM_OPERATIONS_DLL_EXPORT
const LM::LibPart*	GetEffectiveLibpart (const EDB::GeneralElemConstRef& elem, const GDLGlobalCalcEnvir& gdlGlobals, const LM::LibrarySet* librarySet);

VB_ELEM_OPERATIONS_DLL_EXPORT
const LM::LibPart*	GetEffectiveProxyLibpart (const EDB::GeneralElemConstRef& elem, const GDLGlobalCalcEnvir& gdlGlobals, const LM::LibrarySet* librarySet);

VB_ELEM_OPERATIONS_DLL_EXPORT
LM::AncestryInfo	GetAncestryInfoForDummyLibpart (const LM::LibrarySet* librarySet,
													IDElem					ownerID,
													const GS::UnID&			creatorUnId);

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	SetActualAddPars (const LM::LibPart*				libPart,
														  const LM::LibPart*				origLibPart,
														  const IGDLLibraryEnvironment&		libraryEnvironment,
														  const EDB::GeneralElemConstRef&	gdlElem,
														  GDL::Parameters&					addPar,
														  bool*								isReplaced = nullptr,
														  double*							defparA = nullptr,
														  double*							defparB = nullptr);

bool									IsUsingRotSkins (const VBElem::WallConstRef& wall, const VBElem::WallOpeningFillerConstRef& hole);

ADB::AttributeIndex						GetCompositeOrFillPatternIndex (const VBElem::WallConstRef& wall);
ADB::AttributeIndex						GetCompositeOrFillPatternIndex (const VBElem::WallDefault* wall2Def, const ADB::AttributeSetConstRef& attributeSet);
ADB::AttributeIndex						GetCompositeOrFillPatternIndex (const VBElem::ShellBaseConstRef& shellBase);
ADB::AttributeIndex						GetCompositeOrFillPatternIndex (const VBElem::CeilConstRef& pSlab);

void									GetCompositeValues (const GDLGlobalCalcEnvir&		gdlGlobals,
															const ADB::AttributeIndex&		compFillPatternIndex, 
															GS::UniString*					compositeName,
															short*							nSkins,
															double*							skinspars,
															GS::UniChar::Layout**			skins_bmat_names,
															bool							useCompContourLineTypePen,
															short							cutContourLinePen,
															const ADB::AttributeIndex&		cutContourLineType,
															bool							useCompInnerLineTypePen,
															short							cutInnerLinePen,
															const ADB::AttributeIndex&		cutInnerLineType,
															bool							useCompFillPen,
															short							cutFillPen,
															bool							useCompBackgroundPen,
															short							cutFillBackgroundPen,
															const ADB::AttributeIndex&		buildingMaterialIndex,
															bool							useCompSkinSurfaceIndex,
															const ADB::AttributeIndex&		surfaceIndex,
															bool							rotSkins,
															double							thickness,
															GS::Array<short>*				componentIds);

GS::Optional<GS::Array<GDL::GDLRequestComponentId>>	GetSkinsComponentIds (EDB::GeneralElemConstRef		parentElem,
																		  const GDLGlobalCalcEnvir&		gdlGlobals);


GSErr	VB_ELEM_OPERATIONS_DLL_EXPORT	CalculateShellBaseGlobals (const VBCalculations::GDLGlobalCalcEnvir& gdlGlobals,
																   VBElem::ShellBaseConstRef	shellBase,
																   GS::UniString*				compositName,
																   short*						nSkins,
																   double*						skinspars);

enum InfoBitsMode {
	EmptyGlobalsBitsForVarMacro,
	FillGlobalsBitsForVarmacro
};

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLGO_GetLPGdlInfoBits (GDL::IFileRef*											fileRef,
																	const IGDLLibraryEnvironment&									libraryEnvironment,
																	const LM::LibPart*										libPart,
																	GDL_ScriptType											scriptType,
																	GdlInfoBits*											infoBits,
																	InfoBitsMode											infoBitsMode = EmptyGlobalsBitsForVarMacro,
																	GS::HashSet<GS::Pair<GS::Int32, GS::UniString> >*		requestIDs = nullptr,
																	GS::HashSet<GS::UniString>*								applicationQueryNames = nullptr);

short	VB_ELEM_OPERATIONS_DLL_EXPORT	GetLibPartType (const LM::LibPart* libPart, const IGDLLibraryEnvironment& libraryEnvironment, bool *isText = nullptr);
short	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSymbolType_OBSOLETE (const LM::LibPart* libPart, const IGDLLibraryEnvironment& libraryEnvironment, bool *isText = nullptr);

EDB::Tool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetToolFromLibItem (const LM::LibPart* libPart, short idElem, const IGDLLibraryEnvironment& gdlGlobals);

enum class SkinMergeMode {
	ForScreenDisplay,
	Disabled
};


class VB_ELEM_OPERATIONS_DLL_EXPORT WallSkinMergeStrategy {
public:
	virtual ~WallSkinMergeStrategy ();

	virtual void MergeWallSkins (CW2StructRec* a_plCW2, VBElem::WallConstRef pWall) const = 0;
};

typedef GS::Ref<const WallSkinMergeStrategy> WallSkinMergeStrategyConstRef;


class VB_ELEM_OPERATIONS_DLL_EXPORT WallSkinMergeStrategyFactory {
public:
	enum KeepSkinsT { KeepSkins };

public:
	WallSkinMergeStrategyFactory (KeepSkinsT);
	WallSkinMergeStrategyFactory (bool nOnlyCalc, SkinMergeMode skinMergeMode, const DetailHandler* detailHandler);
	WallSkinMergeStrategyFactory (bool nOnlyCalc, const DetailHandler* detailHandler);
	WallSkinMergeStrategyFactory (const DetailHandler* detailHandler);
	WallSkinMergeStrategyFactory (SkinMergeMode skinMergeMode, const DetailHandler* detailHandler);
	WallSkinMergeStrategyFactory (SkinMergeMode skinMergeMode, WallSkinMergeStrategyConstRef skinMergeStrategy);

	WallSkinMergeStrategyConstRef GetStrategy () const;
private:
	const WallSkinMergeStrategyConstRef strategy;
};


struct CutAltitudes {
	double	above;
	double	cut;
	double	below;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT FloorHandler {
public:
	FloorHandler (const EDB::ProjectConstRef& project, const VBD::FloorPlanCutLevelsConstRef& floorPlanCutLevels, short showElemFloor);
	virtual ~FloorHandler ();

	virtual CutAltitudes GetCutAltitudes (VBElem::ElemViewDepthLimitations viewDepth) = 0;

	const EDB::FloorStructureConstRef		floorStructure;
	const VBD::FloorPlanCutLevelsConstRef	floorPlanCutLevels;
	const short								showElemFloor;
};


class VB_ELEM_OPERATIONS_DLL_EXPORT DefaultFloorHandler: public FloorHandler {
public:
	DefaultFloorHandler (const EDB::ProjectConstRef& project, const VBD::FloorPlanCutLevelsConstRef& floorPlanCutLevels, short showElemFloor);
	virtual ~DefaultFloorHandler ();

	virtual CutAltitudes GetCutAltitudes (VBElem::ElemViewDepthLimitations viewDepth) override;
};


struct MakeWall2PatEnvir {
	const GDLGlobalCalcEnvir&	gdlGlobals;
	CompInfo::AttributeGetter&	attributeGetter;
	FloorHandler&				floorHandler;
};


CompResult	VB_ELEM_OPERATIONS_DLL_EXPORT	MakeWall2PatStruct (const MakeWall2PatEnvir&				envir,
																const VBCalculations::WallCutPlaneData*		wCutPlane,
																const bool							   checkWall,
																VBElem::WallConstRef				   pWall,
																CW2StructRec*						   a_plCW2,
																bool								   ghostColor,
																bool								   turnFl,
																bool								   normalTurn,
																WallSkinMergeStrategyConstRef		   skinMergeStrategy,
																Phasing::RenovationStatusType		   wallStatus,
																EffectiveComposite::Structure		   structureDisplay,
																Geometry::IrregularPolygon2D&		   poly);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetWallDefault_Globals (const GDLGlobalCalcEnvir&			gdlGlobals,
																GDL::ParameterAccessor&				globHdl,
																Int32								globInd,
																IGetWallDefault*					getWallDef,
																const VBElem::WallOpeningFillerDefault*	wdDat = nullptr,
																bool								isWallEnd = false);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetSymbDefault_Globals (GDL::ParameterAccessor&			globHdl,
																const GDLGlobalCalcEnvir&		gdlGlobals,
																Int32							globInd,
																const EDB::Tool&				tool,
																short							symbTyp,
																const VBElem::OpeningFillerDefault*	wdDat,
																const EDB::DefaultElem*			slDat,
																bool							storyMarker);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetGdlGlobal_NoLabel (GDL::ParameterAccessor&			globHdl,
															  Int32								globInd,
															  short								symbTyp,
															  const LM::LibPart*				libPart,
															  short								idElem,
															  const EDB::GeneralElemConstRef&	elem,
															  const IPropertyBasedReaderFactory&	elemReaderFactory,
															  double*							framData,
															  const EDB::DefaultElem*			slDat,
															  GDL_ScriptType					scriptType,
															  GDLContext						context,
															  GlobalsMode						mode,
															  short								frameInd,
															  bool								setThickExpr,
															  bool								setInsetExpr,
															  bool								setFrameExpr,
															  EDB::GeneralElemConstRef			owner,
															  bool								placedElem,
															  const GDLGlobalCalcEnvir&			gdlGlobals,
															  IGetWallDefault*					getWallDef,
															  double							viewAngle = 0.0,
															  short								labelParentIdElem = 0,
															  bool								storyMarker = false,
															  EDB::Tool*						actualTool = nullptr,
															  GDLDiagnosticMode					gdlDiagnosticMode = DiagnosticModeOff);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetGlob_Global (GDL::ParameterAccessor&			globHdl,
														Int32							globInd,
														short							idElem,
														const EDB::GeneralElemConstRef&	elem,
														const IPropertyBasedReaderFactory&		elemReaderFactory,
														const VBElem::OpeningFillerDefault*	wdDat,
														const VBElem::GDLObjectDefault*	slDat,
														IGetWallDefault*				getWallDef,
														short							symbTyp,
														GDL_ScriptType					scriptType,
														GDLContext						context,
														GlobalsMode						mode,
														short							frameInd,
														short							labelParentIdElem,
														const GDLGlobalCalcEnvir&		gdlGlobals);


// --- Functions NOT using GDLGlobalCalcEnvir --------------------------------------------------------------------------


GSErr	VB_ELEM_OPERATIONS_DLL_EXPORT	ClearGdlGlobals (GDL::Parameters&	globParameters);

ADB::AttributeIndex	VB_ELEM_OPERATIONS_DLL_EXPORT	GetCW55SidePat (const ADB::AttributeSetConstRef&	attributes,
																		  ADB::AttributeIndex			wPat,
																		  bool							firstPat);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	CalcWallResolution (VBElem::WallConstRef pWall,
															double *refRadius,
															short *resolution);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	ConvertDefaultToFixHeight (EDB::DefaultElem* defElem, EDB::FloorStructureConstRef floorStructure);

Int32	VB_ELEM_OPERATIONS_DLL_EXPORT	SetFontStyle2GlobalValue (unsigned char wordFace, Int32 wordEffects);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	ExplodeFontStyleFromGlobalValue (Int32 gdlStyleValue, unsigned char& wordFaceOut, Int32& wordEffectsOut);


EDB::GeneralElemConstRef	VB_ELEM_OPERATIONS_DLL_EXPORT	GetLabeledElem (VBElem::LabelConstRef label, short *idBaseElem = nullptr);

GSErr		VB_ELEM_OPERATIONS_DLL_EXPORT	InitGDLGlobalOperations (void);
void		VB_ELEM_OPERATIONS_DLL_EXPORT	ExitGDLGlobalOperations (void);
GSErr		VB_ELEM_OPERATIONS_DLL_EXPORT	InitGdlGlobals (GDL::Parameters* globHdl);
VB_ELEM_OPERATIONS_DLL_EXPORT const GDL::Parameters&		GetGdlUserGlobals (void);
VB_ELEM_OPERATIONS_DLL_EXPORT void							SetGdlUserGlobals (const GDL::Parameters& newUserGlobals);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSymbolParametersRef (const LM::LibPart& libPart, const SymbolParametersSectionContent** syParSectOut);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	CreateDefaultSyParHandle (const GS::UnID&		parentLPFUnID,
																	  const LM::LibrarySet*	librarySet,
																	  GS::Owner<SymbolParametersSectionContent>* defaultSyParSectOut);

GDL::Parameters	VB_ELEM_OPERATIONS_DLL_EXPORT	GetDefaultParameters (const LM::LibPart* libPart,
																	  short symbolType,
																	  GS::UnID zoneStampID,
																	  GS::UnID modelElemID,
																	  const LM::LibrarySet* librarySet);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetDefaultParamsOfMacro (const IO::Location*			fileLoc,
																	 const LM::LibPart*				libPart,
																	 const LM::LibrarySet*			librarySet,
																	 const GS::UnID&				zoneStampID,
																	 const GS::UnID&				modelElemID,
																	 const FTM::TypeID&				gdlFileType,
																	 const FTM::GroupID&			allImgFileType,
																	 GS::Owner<GDL::Parameters>&	params);

GSErrCode VB_ELEM_OPERATIONS_DLL_EXPORT GetAddParData (const IO::Location*							fileLoc,
													   const LM::LibPart*							libPart,
													   const LM::LibrarySet::ThreadSafeModifier&	librarySetModifier,
													   const GS::UnID&								zoneStampID,
													   const GS::UnID&								modelElemID,
													   const FTM::TypeID&							gdlFileType,
													   const FTM::GroupID&							allImgFileType,
													   ConstGDLAddParDataPtr&						gdlAddParData);


GDLContext	VB_ELEM_OPERATIONS_DLL_EXPORT	ElemSetToContext (const VBES::ElemSetConstRef& elemSet);
GlobalsMode	VB_ELEM_OPERATIONS_DLL_EXPORT	ElemSetToGlobalsMode (const VBES::ElemSetConstRef& elemSet);

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetWDOrientDisp (const LM::LibPart*	libPart,
														 OrientDispRec*		odr);

bool	VB_ELEM_OPERATIONS_DLL_EXPORT	SymbolUseScript (const LM::LibPart* libPart, GDL_ScriptType scriptType, const LM::LibrarySet::IThreadSafeModifier& librarySetTSModifier);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSySection (const LM::LibPart*		libPart,
														  UInt32			sectType,
														  unsigned short	subIdent,
														  GSHandle*			sectData);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSySection (const LM::LibPart*		libPart,
														  UInt32			sectType,
														  unsigned short	subIdent,
														  GS::UniString*	sectStr);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLGO_GetDefaultObj_Hdls (const SymbolParametersSectionContent**	def_syParSect,
																  GS::UnID					id,
																  const LM::LibrarySet*		librarySet);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLGO_GetDefaultRoom_Hdls (const SymbolParametersSectionContent**	def_syParSect,
																   GS::UnID					id,
																   const LM::LibrarySet*	librarySet);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	GDLGO_FreeDefaultObjPar_Hdls (void);

GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSymbolComponentsRef	(const LM::LibPart* libPart, GSConstHandle* result);
GSErrCode	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSymbolBinary2dRef	(const LM::LibPart* libPart, VectorImage* image, bool* sectionFound = nullptr);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetSymbolHdl_EqBox (const LM::LibPart*		libPart,
															Box2DData*				syBox);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	CalcSwTill (double			thick,
													CW2StructRec*	a_plCW2);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	TurnSWWall2 (CW2StructRec*	a_plCW2);


void	VB_ELEM_OPERATIONS_DLL_EXPORT	MaskGlobalBitGroups (Int32 *globalsBits);



bool	VB_ELEM_OPERATIONS_DLL_EXPORT	GetLibraryGlobalRefs (const IGDLLibraryEnvironment& libraryEnvironment, const GDL::ParameterGetter& globHdl, const LM::LibPart* libPart, GDL::IFileRef* fileRef,
															  GDL_ScriptType scriptType, GS::HashSet<LM::LibPartId>& libraryGlobalRefs);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	GetExpressionGlobalsBits (const LM::LibPart* libPart, const GDLGlobalCalcEnvir& gdlGolbalCalcEnvir, Int32 *pExprGlobalsBits);

short	VB_ELEM_OPERATIONS_DLL_EXPORT	ElemId_To_GDLEltype (short idElem);

VB_ELEM_OPERATIONS_DLL_EXPORT
GSErrCode WriteLibraryGlobalsChecksum (GS::OChannel& oc,
									   const LM::LibPart* libPart,
									   GDL::IFileRef* fileRef,
									   const VBCalculations::IGDLLibraryEnvironment& libraryEnvironment,
									   const GS::Array<LibraryMVOData>& datas,
									   GDL_ScriptType	scriptType);

short	VB_ELEM_OPERATIONS_DLL_EXPORT	GetCalcStoryNumber (VBElem::WallOpeningFillerConstRef opening,
															const IPropertyBasedReaderFactory& elemReaderFactory,
															const EDB::FloorStructureConstRef& floorStructure,
															VBCalculations::GDLGlobalCalcEnvir* gdlGlobals = nullptr);

void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetRailingPostDefaultGlobals (GDL::ParameterAccessor& gdlGlobals, GSType typeId);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetRailingPanelDefaultGlobals (GDL::ParameterAccessor& gdlGlobals);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetRailDefaultGlobals (GDL::ParameterAccessor& gdlGlobals, GSType typeId);
void	VB_ELEM_OPERATIONS_DLL_EXPORT	SetRailingFinishGDLObjectDefaultGlobals (GDL::ParameterAccessor& gdlGlobals, GSType connectedRailTypeId);


VB_ELEM_OPERATIONS_DLL_EXPORT
Geometry::Polygon2D		CreateOpeningSymbolDefaultPolygon (VBElem::OpeningSymbolType symbolType,
														  const OpeningGeometry::ExtrusionParameters& extrusionParameters);

VB_ELEM_OPERATIONS_DLL_EXPORT
void	SetOpeningSymbolDefaultPolygonGlobals (GDL::ParameterAccessor&	 globHdl,
											   VBElem::OpeningSymbolType symbolType,
											   const OpeningGeometry::ExtrusionParameters& extrusionParameters);

VB_ELEM_OPERATIONS_DLL_EXPORT
void	SetLabelAssocElemGeometry (GDL::ParameterAccessor& globHdl, VBElem::LabelConstRef pLabel);

VB_ELEM_OPERATIONS_DLL_EXPORT
void	SetLabelDefaultAssocElemGeometry (GDL::ParameterAccessor& globHdl);

VB_ELEM_OPERATIONS_DLL_EXPORT
GDL::Dictionary	CreateStairBreakMarkGeometry (const VBElem::StairConstRef& stair, const GDLGlobalCalcEnvir& gdlGlobals);

}	// namespace VBCalculations

#endif	//GDLGLOBALOPERATIONS_HPP
