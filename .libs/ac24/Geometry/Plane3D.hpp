#ifndef PLANE3D_HPP_
#define PLANE3D_HPP_
#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "GeometricDefinitions.h"
#include "UnitVector3D.hpp"
#include "Optional.hpp"

// === Predeclarations =================================================================================================

struct PlaneEq;

namespace Geometry {
	class Plane;
	class Transformation3D;
	class OrthogonalTransformation3D;
}

// =====================================================================================================================

namespace Geometry {

class GEOMETRY_DLL_EXPORT Plane3D
{
public:
	Plane3D (const UnitVector_3D& planeNormal, const Coord3D& onPlanePoint);
	Plane3D (const PlaneEq& planeEq)												CAN_THROW (UnitVectorCreationError);

	static GS::Optional<Plane3D> CreateFromPoints (const Point3D& p1, const Point3D& p2, const Point3D& p3, double eps = EPS);

	Coord3D			GetAnOnPlanePoint	() const;
	UnitVector_3D	GetPlaneNormal		() const;
	PlaneEq			GetPlaneEq			() const;

	bool			IsPointOf			(const Coord3D& c) const;
	Coord3D			ProjectToPlane		(const Coord3D& c) const;
	Coord3D			ProjectToPlane_V	(const Vector3D& v) const;
	double			GetDistance			(const Coord3D& c) const;

	bool			IsParallelWith		(const Plane3D& other) const;
	bool			IsCoplanarWith		(const Plane3D& other) const;	// normal vectors may be opposite
	bool			IsEqualWith			(const Plane3D& other) const;	// coplanar and normals point to same direction

	Plane3D					Transform (const OrthogonalTransformation3D&) const;
	GS::Optional<Plane3D>	Transform (const Transformation3D&) const;

private:
	Plane3D ();

	UnitVector_3D planeNormal;
	double pD;					// for on plane points : planeNormal * c + pD = 0
};


GEOMETRY_DLL_EXPORT Plane3D ToPlane3D (const Plane& plane);

}

#endif
