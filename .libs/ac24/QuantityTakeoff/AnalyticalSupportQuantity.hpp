// Contact person : MaK

#ifndef ANALYTICALSUPPORT_QUANTITY_HPP
#define ANALYTICALSUPPORT_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IAnalyticalSupportQuantityCalculator.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT AnalyticalSupportQuantityCalculator : public Property::IAnalyticalSupportQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	AnalyticalSupportQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~AnalyticalSupportQuantityCalculator ();

	virtual	double											GetNetVolume						() const override;
	virtual	double											GetTotalSurfaceArea					() const override;

	virtual double											GetHighestPoint						() const override;
	virtual double											GetLowestPoint						() const override;

	virtual GS::HashSet<VBEO::ModelElemComponentId>			GetComponents						() const override;
	virtual	ADB::AttributeIndex								GetComponentBuildingMaterialIdx		(const VBEO::ModelElemComponentId& componentId) const override;
	virtual double											GetComponentVolume					(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	bool											HasComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	double											GetComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;

	virtual GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfaces					() const override;
	virtual GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfaces				() const override;
	virtual	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const override;

	virtual VBEO::ModelElemComponentId						GetComponentId						(const Modeler::MeshBody& body) const override;	
};


inline double		AnalyticalSupportQuantityCalculator::GetHighestPoint () const
{
	return NAN;
}

inline double		AnalyticalSupportQuantityCalculator::GetLowestPoint () const
{
	return NAN;
}


}

#endif