#ifndef INTERSECTION3D_H_
#define INTERSECTION3D_H_

#include "Ray3D.hpp"
#include "Variant.hpp"
#include "Sector3DData.h"
#include "Plane3D.hpp"

namespace Geometry
{
	struct EmptyIntersection3D {};

	// ==== Calculate intersection between line-like objects ====

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Line3D>				Intersect (const Line3D& line1, const Line3D& line2, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Ray3D>				Intersect (const Line3D& line, const Ray3D& ray, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Segment3D>			Intersect (const Line3D& line, const Segment3D& segment, const Tolerance& tol = {});

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Segment3D, Ray3D>		Intersect (const Ray3D& ray1, const Ray3D& ray2, const Tolerance& tol = Tolerance {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Segment3D>			Intersect (const Ray3D& ray, const Segment3D& segment, const Tolerance& tol = {});

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Segment3D>			Intersect (const Segment3D& segment1, const Segment3D& segment2, const Tolerance& tol = {});

	// ==== Calculate intersection between line-like objects & planes ====

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Line3D>				Intersect (const Line3D& line, const Plane3D& plane, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Ray3D>				Intersect (const Ray3D& ray, const Plane3D& plane, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Segment3D>			Intersect (const Segment3D& segment, const Plane3D& plane, const Tolerance& tol = {});

	// ==== Calculate intersection between planes ====

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Line3D, Plane3D>				Intersect (const Plane3D& plane1, const Plane3D& plane2, const Tolerance& tol = {});

	// ==== Intersection Convenience functions ====

	// Line-like vs line-like

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Ray3D>				Intersect (const Ray3D& ray, const Line3D& line, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Segment3D>			Intersect (const Segment3D& segment, const Line3D& line, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Segment3D>			Intersect (const Segment3D& segment, const Ray3D& ray, const Tolerance& tol = {});

	// Line-like vs plane

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Line3D>				Intersect (const Plane3D& plane, const Line3D& line, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Ray3D>				Intersect (const Plane3D& plane, const Ray3D& ray, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection3D, Point3D, Segment3D>			Intersect (const Plane3D& plane, const Segment3D& segment, const Tolerance& tol = {});

	// ==== Optional intersection versions ====

	template <typename T1, typename T2>
	GS::Optional<Point3D> IntersectInPoint3D (const T1& first, const T2& second, const Tolerance& tolerance = {})
	{
		auto intersection = Intersect (first, second, tolerance);
		GS::Optional<Point3D> returnValue;

		if (intersection.template Is<Point3D> ())
		{
			returnValue = intersection.template Get<Point3D> ();
		}

		return returnValue;
	}

	template <typename T1, typename T2>
	GS::Optional<Line3D> IntersectInLine3D (const T1& first, const T2& second, const Tolerance& tolerance = {})
	{
		auto intersection = Intersect (first, second, tolerance);
		GS::Optional<Line3D> returnValue;

		if (intersection.template Is<Line3D> ())
		{
			returnValue = intersection.template Get<Line3D> ();
		}

		return returnValue;
	}

}


#endif // INTERSECTION3D_H_
