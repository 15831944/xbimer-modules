// Contact person : KiP
#ifndef PROFILE_TO_3D_TRANSFORMER_HPP
#define PROFILE_TO_3D_TRANSFORMER_HPP
#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "Matrix23.hpp"
#include "Plane.hpp"
#include "Plane3D.hpp"
#include "CoordinateSystem3D.hpp"
#include "GenArc2DData.h"

// from VBElements
#include "AssemblySegmentTypes.hpp"
#include "BeamTypes.hpp"
#include "BeamSegmentTypes.hpp"
#include "ColumnTypes.hpp"
#include "ColumnSegmentTypes.hpp"
#include "WallTypes.hpp"
#include "ProfileTypes.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

// =====================================================================================================================

namespace VBEO {

enum ProfileTrafoInclusion	//#KiP_Refactor_Profile ennek ProfileTo3DTransformer-en belul kell lennie
{
	IncludeProfileTrafo,
	OmitProfileTrafo
};

class VB_ELEM_OPERATIONS_DLL_EXPORT ProfileTo3DTransformer
{
public:
	static ProfileTo3DTransformer	CreateForSegmentBeginPlane (const VBElem::AssemblySegmentConstRef& segment, ProfileTrafoInclusion profileTrafoInclusion);
	static ProfileTo3DTransformer	CreateForSegmentEndPlane (const VBElem::AssemblySegmentConstRef& segment, ProfileTrafoInclusion profileTrafoInclusion);
	static ProfileTo3DTransformer	CreateForWallBeginPlane (const VBElem::WallConstRef& wall, ProfileTrafoInclusion profileTrafoInclusion);
	static ProfileTo3DTransformer	CreateForWallEndPlane (const VBElem::WallConstRef& wall, ProfileTrafoInclusion profileTrafoInclusion);

	Point3D					To3D (const Point2D& pointInProfile) const;
	Sector3D				To3D (const Sector& sectorInProfile) const;
	Vector3D				To3D (const Vector& vectorInProfile) const;

	GS::Optional<Point2D>	ToProfile (const Point3D& pointIn3D) const;
	GS::Optional<Sector>	ToProfile (const Sector3D& sectorIn3D) const;
	GS::Optional<Vector>	ToProfile_V (const Vector3D& vectorIn3D) const;

	bool					IsOnProfilePlane (const Point3D& point) const;
	Geometry::Plane3D		GetProfilePlane () const;

	ProfileTo3DTransformer	CopyAndOffset (const Vector3D& offset) const;

private:
	Geometry::Matrix23 profileTrafo;
	Geometry::Matrix23 invProfileTrafo;
	Geometry::OrthonormalizedCoordinateSystem3D localCoordSys;

	enum class RefLinePoint { Beg, End };
	enum class XAxisDirection { TowardsOrigo, FromOrigo };

	ProfileTo3DTransformer ();

	static ProfileTo3DTransformer CreateForSegment (const VBElem::AssemblySegmentConstRef& segment, ProfileTrafoInclusion profileTrafoInclusion, RefLinePoint refLinePoint);
	static ProfileTo3DTransformer CreateForWall (const VBElem::WallConstRef& wall, ProfileTrafoInclusion profileTrafoInclusion, RefLinePoint refLinePoint);

	void SetupProfileTrafo (const Geometry::Matrix23& trafo);
	void SetupIdentityProfileTrafo ();

	void SetupCoordinateSystemFromBeamSegment (const VBElem::AssemblySegmentConstRef& segment, const VBElem::BeamConstRef& ownerBeam, RefLinePoint refLinePoint);
	void SetupCoordinateSystemFromColumnSegment (const VBElem::AssemblySegmentConstRef& segment, const VBElem::ColumnConstRef& ownerColumn, RefLinePoint refLinePoint);
	void SetupCoordinateSystemFromWall (const VBElem::WallConstRef& wall, RefLinePoint refLinePoint);
	void SetupCoordinateSystemFromHorizontallyCurvedRefLine (const Point3D& beg, const Point3D& end, double arcAngle, RefLinePoint refLinePoint, XAxisDirection xAxisDirection);
};

}

#endif
