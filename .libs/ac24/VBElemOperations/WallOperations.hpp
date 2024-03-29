#ifndef WALL_OPERATIONS__HPP
#define WALL_OPERATIONS__HPP

// from VBElemOperations
#include "VBElemOperationsExport.hpp"
#include "VBElemOperations.hpp"
#include "ProfileInterface.hpp"
#include "GDLGlobalCalculations.hpp"
#include "VBElemSurfaceDescriptor.hpp"

// from GSModeler
#include "Model3D/model.h"

// from VBElements
#include "WallTypes.hpp"
#include "GeneralElem.hpp"

// from VBAttributes
#include "BuildingMaterial.hpp"
#include "compwall.hpp"

// from VectorImage
#include "StructureComponentId.hpp"

// =====================================================================================================================
//  VBElemOperations
// =====================================================================================================================

class VB_ELEM_OPERATIONS_DLL_EXPORT WallOperations
{
public:
	enum ExplodeResult
	{
		KeepOriginal			= 1,
		SuccessfulExplode		= 0,
		AttributeError			= -1,
		CantHandleTrapezoid		= -2,
		OtherError				= -3
	};

	enum ExplodeRefLineMode
	{
		KeepOriginalRefLine		= 0,
		MoveRefLine				= 1
	};

	enum MaterialSelector {
		LeftMaterial,
		RightMaterial,
		RefSideMaterial,
		OppSideMaterial,
		HorizontalSideMaterial,		
		SideMaterial,
		OpeningLeftMaterial,
		OpeningRightMaterial,
		OpeningRefSideMaterial,
		OpeningOppSideMaterial,
		OpeningSideMaterial,
		CutElemMaterial,
		CropUpwardsMaterial,
		CropDownwardsMaterial
	};

	enum SkinOffsetLocation {
		SkinOutside,
		SkinCenter,
		SkinInside
	};

	template <class WallType>
	static VBElemSurfaceDescriptor GetMaterial (	const WallType& wall,
								const ADB::AttributeSetConstRef& attributeSet,
								MaterialSelector selector,
								bool pbcConversion,
								const ComponentIndex& componentIndex = ComponentIndex::EntireElement,
								const ProfileInterface* profile3DData = nullptr);

	template <class WallType>
	static VBElemSurfaceDescriptor GetStructureMaterial (	const WallType& wall,
										const ADB::AttributeSetConstRef& attributeSet,
										MaterialSelector selector,
										bool pbcConversion,
										const ComponentIndex& componentIndex = ComponentIndex::EntireElement,
										const ProfileInterface* profile3DData = nullptr);

	static void				GetStandaloneVisibleMaterials (VBElem::WallConstRef wall, bool pbcConversion, GS::HashSet<ADB::AttributeIndex>& materials);
	
	static void				SetSlantedHeight (VBElem::WallRef wall, double z, VBElemOperations::SetHeightLocation location, bool keepOpeningsAbsolutePosition);
	
	static ExplodeResult	ExplodeWall (const VBElem::WallConstRef& originalWall, ExplodeRefLineMode refLineMode, GS::Array<VBElem::WallRef>& resultWalls);
	
	static double			GetSkinOffset (VBElem::WallConstRef wall, short skinIndex, SkinOffsetLocation location);
	
	static bool				HasVisibleSkin	(VBElem::WallConstRef elemRef, EffectiveComposite::Structure structure);

	static UInt32			GetComponentNumber (VBElem::WallConstRef wall);

	static short			GetComponentFlags (VBElem::WallConstRef wall, const StructureComponentId& structureComponentId);

	template <typename WallType>
	static GS::Optional<GenArc>	GetReferenceLineArc (const WallType& wall);

	struct ZBounds 
	{ 
		double zMin; 
		double zMax; 
	};

	static ZBounds			GetZBounds (const VBElem::WallConstRef& wall);
	static Box3D			GetRawBounds3D (const VBElem::WallConstRef& wall);

	static void				SetHomeStory (VBElem::WallRef wall, const short homeStoryNum);

	static void				GetOffsetedRefLineEndPoints (const VBElem::WallConstRef& wall, Coord& offsetedBeg, Coord& offsetedEnd);

	static void				GetWallReferencePolyline2D (VBElem::WallConstRef pWall2, Geometry::Polyline2D& referenceLine);
	
	static void				SplitWall (const VBElem::WallRef& originalWall, VBElem::WallRef& newWall, double splitParam, const VBCalculations::GDLGlobalCalcEnvir& gdlGlobalCalcEnvir, const LM::LibrarySet* librarySet, const IPropertyBasedReaderFactory& elemReaderFactory);


	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::WallConstRef& wall);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::WallConstRef& wall);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(const VBElem::WallRef& wall);

	static GS::Optional<VBEO::ModelElemStructureRef>			GetModelElemStructure			(const VBElem::WallDefault& wallDef);
	static GS::Optional<VBEO::FloorPlanAppearanceRef>			GetFloorPlanAppearance			(const VBElem::WallDefault& wallDef);
	static GS::Optional<VBEO::FloorPlanAppearanceModifierRef>	GetFloorPlanAppearanceModifier	(VBElem::WallDefault& wallDef);
	
	static double GetHomeStoryRelativeNominalBottom (const VBElem::WallDefault& wallDef);
	static double GetHomeStoryRelativeNominalTop	(const VBElem::WallDefault& wallDef);

};

template <class WallType>
inline bool IsCurvedWall (const WallType& wall)
{
	return fabs (wall->GetAngle ()) >= Eps;
}

template <>
inline bool IsCurvedWall (const VBElem::WallDefault* const & wall)
{
	UNUSED_PARAMETER (wall);
	return false;
}

template <class WallType>
bool	IsComplexWall (const WallType& wall)
{
	return wall->GetCrossSectType () != CrossSect_Simple;
}

template <class WallType>
bool	IsLogWall (const WallType& wall)
{
	return !IsComplexWall (wall) && wall->GetLogHeight () >= Eps && !IsCurvedWall (wall);
}

template <class WallType>
VBElemSurfaceDescriptor WallOperations::GetMaterial (const WallType& wall,
									const ADB::AttributeSetConstRef& attributeSet,
									MaterialSelector selector,
									bool pbcConversion,
									const ComponentIndex& componentIndex,
									const ProfileInterface* profile3DData)
{
	switch (selector) {
		case LeftMaterial:
			if (!wall->IsFlipped ()) {
				return GetMaterial (wall, attributeSet, RefSideMaterial, pbcConversion, componentIndex);
			} else {
				return GetMaterial (wall, attributeSet, OppSideMaterial, pbcConversion, componentIndex);
			}
			break;
		case RightMaterial:
			if (!wall->IsFlipped ()) {
				return GetMaterial (wall, attributeSet, OppSideMaterial, pbcConversion, componentIndex);
			} else {
				return GetMaterial (wall, attributeSet, RefSideMaterial, pbcConversion, componentIndex);
			}
			break;
		case RefSideMaterial:
			return GetStructureMaterial (wall, attributeSet, RefSideMaterial, pbcConversion, componentIndex, profile3DData);
			break;
		case OppSideMaterial:
			return GetStructureMaterial (wall, attributeSet, OppSideMaterial, pbcConversion, componentIndex, profile3DData);
			break;
		case HorizontalSideMaterial:			
			if (wall->GetKind () == WNormal && !IsCurvedWall (wall)) {
				if ((wall->GetLogBeamStatus () & LOG_REFMAT_TO_HORI) > 0)
					return GetStructureMaterial (wall, attributeSet, RefSideMaterial, pbcConversion, componentIndex, profile3DData);
				if ((wall->GetLogBeamStatus () & LOG_OPPMAT_TO_HORI) > 0)
					return GetStructureMaterial (wall, attributeSet, OppSideMaterial, pbcConversion, componentIndex, profile3DData);
			}
			return GetStructureMaterial (wall, attributeSet, SideMaterial, pbcConversion, componentIndex, profile3DData);
			break;
		case SideMaterial:
			return GetStructureMaterial (wall, attributeSet, SideMaterial, pbcConversion, componentIndex, profile3DData);
			break;
		case OpeningLeftMaterial:
			if (!wall->IsFlipped ()) {
				return GetMaterial (wall, attributeSet, OpeningRefSideMaterial, pbcConversion, componentIndex);
			} else {
				return GetMaterial (wall, attributeSet, OpeningOppSideMaterial, pbcConversion, componentIndex);
			}
			break;
		case OpeningRightMaterial:
			if (!wall->IsFlipped ()) {
				return GetMaterial (wall, attributeSet, OpeningOppSideMaterial, pbcConversion, componentIndex);
			} else {
				return GetMaterial (wall, attributeSet, OpeningRefSideMaterial, pbcConversion, componentIndex);
			}
			break;
		case OpeningRefSideMaterial:
			return GetStructureMaterial (wall, attributeSet, RefSideMaterial, pbcConversion, componentIndex, profile3DData);
			break;
		case OpeningOppSideMaterial:
			return GetStructureMaterial (wall, attributeSet, OppSideMaterial, pbcConversion, componentIndex, profile3DData);
			break;
		case OpeningSideMaterial:
			return GetStructureMaterial (wall, attributeSet, CutElemMaterial, pbcConversion, componentIndex, profile3DData);
			break;
		case CutElemMaterial:
			return GetStructureMaterial (wall, attributeSet, CutElemMaterial, pbcConversion, componentIndex, profile3DData);
			break;
		case CropUpwardsMaterial:
			return GetStructureMaterial (wall, attributeSet, SideMaterial, pbcConversion, componentIndex, profile3DData);
			break;
		default:
			DBBREAK ();
			//lint -fallthrough
		case CropDownwardsMaterial:
			return GetStructureMaterial (wall, attributeSet, SideMaterial, pbcConversion, componentIndex, profile3DData);
			break;
	}
}

template <class WallType>
VBElemSurfaceDescriptor WallOperations::GetStructureMaterial (	const WallType& wall,
												const ADB::AttributeSetConstRef& attributeSet,
												MaterialSelector selector,
												bool pbcConversion,
												const ComponentIndex& componentIndex,
												const ProfileInterface* profile3DData)
{
	const bool overrideRefSideMaterial = ((!wall->GetElemStructure ().IsProfile () && wall->GetOverrideRefSideMaterial ()) || (wall->GetElemStructure ().IsProfile () && wall->GetOverrideProfileSideMaterial ()));
	const bool overrideOppSideMaterial = ((!wall->GetElemStructure ().IsProfile () && wall->GetOverrideOppSideMaterial ()) || (wall->GetElemStructure ().IsProfile () && wall->GetOverrideProfileSideMaterial ()));
	const bool hasValidSideMaterial = (wall->GetElemStructure ().IsBasic () || !componentIndex.IsEntireElement ());

	switch (selector) {
		case RefSideMaterial:
			if (overrideRefSideMaterial || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (wall->GetRefSideMaterialIdx ());
			break;
		case OppSideMaterial:
			if (overrideOppSideMaterial || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (wall->GetOppSideMaterialIdx ());
			break;
		case SideMaterial:
			if (wall->GetOverrideCutSideMaterial () || !hasValidSideMaterial || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (wall->GetCutSideMaterialIdx ());
			break;
		case CutElemMaterial:
			if (componentIndex.IsEntireElement () || !pbcConversion)
				return VBElemSurfaceDescriptor::FromSurface (wall->GetCutSideMaterialIdx ());
			break;
		default:
			DBBREAK_STR ("Invalid material selector.");
			return VBElemSurfaceDescriptor::FromSurface (0);
	}

	ADB::AttributeIndex buildMat (0);

	if (wall->GetElemStructure ().IsBasic ()) {
		buildMat = wall->GetElemStructure ().GetBasicBuildMatIndex ();
	} else if (profile3DData != nullptr && profile3DData->IsValid ()) {
		profile3DData->GetComponentBuildingMaterialIndex (componentIndex, buildMat);		
	} else if (wall->GetElemStructure ().IsComposite ()) {
		VBAttr::CompWallConstRef compWall = VBAttr::GetConstCompWall (attributeSet, wall->GetElemStructure ().GetCompositeIndex ());
		if (compWall != nullptr) {
			short skinIndex = (selector == OppSideMaterial) ? compWall->GetSkinNumber () - 1 : 0;
			if (!componentIndex.IsEntireElement ()) {
				if (IsLogWall (wall)) {
					skinIndex = 0;
				} else if (DBVERIFY (componentIndex.GetSkinIndex () < compWall->GetSkinNumber ())) {
					skinIndex = componentIndex.GetSkinIndex ();
				}
			}
			buildMat = compWall->GetSkinBuildingMaterialIndex (skinIndex);
		}
	}

	return VBElemSurfaceDescriptor::FromBuildingMaterialCutSurface (buildMat.ToGSAttributeIndex (), attributeSet);
}


template <typename WallType>
GS::Optional<GenArc> WallOperations::GetReferenceLineArc (const WallType& wall)
{
	if (fabs (wall->GetAngle ()) > EPS) {
		return GenArc::CreateCircleArc (wall->GetBegC (), wall->GetEndC (), wall->GetAngle ());
	} else {
		return GS::NoValue;
	}
}


#endif // WALL_OPERATIONS__HPP 
