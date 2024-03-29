// Contact person :	KiP

#ifndef COLUMN_QUANTITY_HPP
#define COLUMN_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "ColumnTypes.hpp"
#include "AssemblySegmentTypes.hpp"

// from PropertyOperations
#include "IColumnQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"
#include "SegmentedAssemblyQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST ColumnQuantityCalculator : public Property::IColumnQuantityCalculator, protected SegmentedAssemblyQuantityCalculator
{
public:
	ColumnQuantityCalculator (VBElem::ModelElementConstRef vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~ColumnQuantityCalculator ();

	virtual double											GetNetVolume						() const override final;
	virtual double											GetTotalSurfaceArea					() const override final;
	virtual double											GetHighestPoint						() const override;
	virtual double											GetLowestPoint						() const override;

	virtual double											GetCoreVolume						() const override;
	virtual double											GetVeneerVolume						() const override;
	virtual double											GetGrossVolume						() const override;
	virtual double											GetGrossCoreVolume					() const override;
	virtual double											GetGrossVeneerVolume				() const override;

	virtual double											GetSurfaceArea						(Int32 surfaceType) const override;
	virtual double											GetCoreSurfaceArea					(Int32 surfaceType) const override;
	virtual double											GetVeneerSurfaceArea				(Int32 surfaceType) const override;
	virtual double											GetGrossCoreSurfaceArea				(Int32 surfaceType) const override;
	virtual double											GetGrossVeneerSurfaceArea			(Int32 surfaceType) const override;

	virtual Geometry::MultiPolygon2D						GetBottomSurfaceProjectedPolygon	() const override;
	virtual double											GetBottomSurfaceProjectedArea		() const override;
	virtual double											GetPerimeterOfBase					() const override;
	virtual double											GetMinimumHeight					() const override;
	virtual double											GetMaximumHeight					() const override;
	virtual	double											GetProjected3DLength				() const override;
	virtual double											GetCrossSectionArea					() const override;

	virtual GS::HashSet<VBEO::ModelElemComponentId>			GetComponents						() const override;
	virtual	ADB::AttributeIndex								GetComponentBuildingMaterialIdx		(const VBEO::ModelElemComponentId& componentId) const override;
	virtual double											GetComponentVolume					(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	bool											HasComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	double											GetComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;

	virtual GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfaces					() const override;
	virtual GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfaces				() const override;
	virtual	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const override;

	// TODO AM

private:
	virtual void											EnumerateModelElemSubElements		(const std::function<void (const VBElem::ModelElementConstRef&)>& processor) const override;
	VBElem::ColumnConstRef									GetColumn							() const;
	
	virtual ModelCalculations::ProjectionCurveRef			GetProjectionCurve () const override;

	GS::Ref<Property::IColumnSegmentQuantityCalculator>		GetColumnSegmentQuantityCalculator  (VBElem::ColumnSegmentConstRef segment) const;

	double GetTopSideSurfaceArea () const;
	double GetBottomSideSurfaceArea () const;
	
	virtual	ModelCalculations::ProjectionSurfaceRef			GetProjectionSurface				(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	IPolygonSurfaceType*							GetPolygonSurfaceType				() const override;

	static CONV2LISTREC										GetNormalModelListParams			();
	static CONV2LISTREC										GetGrossModelListParams				();
	static CONV2LISTREC										GetCoreModelListParams				();
	static CONV2LISTREC										GetGrossCoreModelListParams			();
	static CONV2LISTREC										GetDetailedModelListParams			();

	GS::HashTable<StructureComponentId, double>				CalculateComponentVolumesNoPBC_Deprecated () const;
};

}

#endif
