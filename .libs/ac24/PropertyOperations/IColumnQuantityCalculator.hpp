// Contact person : KiP

#ifndef I_COLUMN_QUANTITY_CALCULATOR_HPP
#define I_COLUMN_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

#include "IModelElementQuantityCalculator.hpp"
#include "Poly2DTypes.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IColumnQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IColumnQuantityCalculator ();

	virtual double		GetCoreVolume					() const = 0;
	virtual double		GetVeneerVolume					() const = 0;
	virtual double		GetGrossVolume					() const = 0;
	virtual double		GetGrossCoreVolume				() const = 0;
	virtual double		GetGrossVeneerVolume			() const = 0;

	virtual double		GetSurfaceArea					(Int32 surfaceType) const = 0;
	virtual double		GetCoreSurfaceArea				(Int32 surfaceType) const = 0;
	virtual double		GetVeneerSurfaceArea			(Int32 surfaceType) const = 0;
	virtual double		GetGrossCoreSurfaceArea			(Int32 surfaceType) const = 0;
	virtual double		GetGrossVeneerSurfaceArea		(Int32 surfaceType) const = 0;

	virtual Geometry::MultiPolygon2D	GetBottomSurfaceProjectedPolygon	() const = 0;
	virtual double						GetBottomSurfaceProjectedArea		() const = 0;
	virtual double						GetPerimeterOfBase					() const = 0;
	virtual double						GetMinimumHeight					() const = 0;
	virtual double						GetMaximumHeight					() const = 0;
	virtual double						GetProjected3DLength				() const = 0;
	virtual double						GetCrossSectionArea					() const = 0;
};

}

#endif
