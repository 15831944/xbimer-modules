#ifndef INTERSECTION2D_H_
#define INTERSECTION2D_H_

#include "Ray2D.hpp"
#include "Variant.hpp"
#include "Sector2DData.h"

namespace Geometry
{
	struct EmptyIntersection {};

	//  Calculate Intersection

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection, Point2D, Line2D>				Intersect (const Line2D& line1, const Line2D& line2, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection, Point2D, Ray2D>				Intersect (const Line2D& line, const Ray2D& ray, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection, Point2D, Segment2D>			Intersect (const Line2D& line, const Segment2D& segment, const Tolerance& tol = {});

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection, Point2D, Segment2D, Ray2D>	Intersect (const Ray2D& ray1, const Ray2D& ray2, const Tolerance& tol = Tolerance {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection, Point2D, Segment2D>			Intersect (const Ray2D& ray, const Segment2D& segment, const Tolerance& tol = {});

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection, Point2D, Segment2D>			Intersect (const Segment2D& segment1, const Segment2D& segment2, const Tolerance& tol = {});

	//  Intersection Convenience functions

	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection, Point2D, Ray2D>				Intersect (const Ray2D& ray, const Line2D& line, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection, Point2D, Segment2D>			Intersect (const Segment2D& segment, const Line2D& line, const Tolerance& tol = {});
	GEOMETRY_DLL_EXPORT GS::Variant<EmptyIntersection, Point2D, Segment2D>			Intersect (const Segment2D& segment, const Ray2D& ray, const Tolerance& tol = {});

	template <typename T1, typename T2>
	GS::Optional<Point2D> IntersectInPoint (const T1& first, const T2& second, const Tolerance& tolerance = {})
	{
		auto intersection = Intersect (first, second, tolerance);
		GS::Optional<Point2D> returnValue;

		if (intersection.template Is<Point2D> ())
		{
			returnValue = intersection.template Get<Point2D> ();
		}

		return returnValue;
	}

}


#endif // INTERSECTION2D_H_
