#if !defined (BOX3DDATA_H)
#define BOX3DDATA_H

#pragma once

#include <cmath>

#include "GeometricDefinitions.h"
#include "Coord3d.h"
#include "Box2DData.h"

/****************************************************************************/
/*																			*/
/*						3D Box and its operations							*/
/*																			*/
/****************************************************************************/
// forward declarations

namespace GS
{

template<class T> class Array;

}


struct GEOMETRY_DLL_EXPORT F_Box3D {
	float	xMin;
	float	yMin;
	float	xMax;
	float	yMax;
	float	zMin;
	float	zMax;

	F_Box3D () : xMin (0.0), yMin (0.0), xMax (0.0), yMax (0.0), zMin (0.0), zMax (0.0) {}
	F_Box3D (float xMi, float yMi, float xMa, float yMa, float zMi, float zMa) : xMin (xMi), yMin (yMi), xMax (xMa), yMax (yMa), zMin (zMi), zMax (zMa) {}
	void WriteXML (GS::XMLOChannel& outXML, const char* tagName = "F_Box") const;
	void ReadXML (GS::XMLIChannel& inXML, const char* tagName = "F_Box");
};




struct Box3D {
	enum InvalidBoundsSelector { Invalid };

	double	xMin;
	double	yMin;
	double	xMax;
	double	yMax;
	double	zMin;
	double	zMax;

	constexpr Box3D () : xMin (0.0), yMin (0.0), xMax (0.0), yMax (0.0), zMin (0.0), zMax (0.0) {}
	// TODO TBa make this the default constructor
	constexpr Box3D (InvalidBoundsSelector) : xMin (BiggestDouble), yMin (BiggestDouble), xMax (-BiggestDouble), yMax (-BiggestDouble), zMin (BiggestDouble), zMax (-BiggestDouble) {}
	constexpr Box3D (double xMi, double yMi, double xMa, double yMa, double zMi, double zMa) : xMin (xMi), yMin (yMi), xMax (xMa), yMax (yMa), zMin (zMi), zMax (zMa) {}
	constexpr Box3D (const Box2DData& box, double elevation = 0.0) : xMin (box.xMin), yMin (box.yMin), xMax (box.xMax), yMax (box.yMax), zMin (elevation), zMax (elevation) {}
	constexpr explicit Box3D (const F_Box3D& fBox) : xMin (fBox.xMin), yMin (fBox.yMin), xMax (fBox.xMax), yMax (fBox.yMax), zMin (fBox.zMin), zMax (fBox.zMax) {}
};

#define	F_Box3DType	F_Box3D		/* temporary */
#define	Box3DType	Box3D		/* temporary */

namespace Geometry {

GEOMETRY_DLL_EXPORT void IVF_Box3D (GS::PlatformSign inplatform, F_Box3DType *b);

GEOMETRY_DLL_EXPORT void IVBox3DType (GS::PlatformSign inplatform, Box3DType *b);

GEOMETRY_DLL_EXPORT void	InitBox3D (Box3DType	*abox);

inline	void SetBox3D (
						Box3DType*	abox,
						double 		xMin,
						double 		yMin,
						double		zMin,
						double 		xMax,
						double 		yMax,
						double		zMax);

GEOMETRY_DLL_EXPORT bool IsEmptyBox3D (const Box3DType	*pCBox, 
												 Boundary			boundaries = Boundary_Opened);

GEOMETRY_DLL_EXPORT bool AreBox3DsEqual (const F_Box3DType& box1, const F_Box3DType& box2, double eps = SmallEps);
GEOMETRY_DLL_EXPORT bool AreBox3DsEqual (const Box3DType& box1, const Box3DType& box2, double eps = SmallEps);

GEOMETRY_DLL_EXPORT void InsetBox3D (Box3DType	*b,
									 double		dx,
									 double		dy,
									 double		dz);


GEOMETRY_DLL_EXPORT bool SectBox3D (const Box3DType	*pCSrcBox1,
								    const Box3DType	*srcBox2,
								    Box3DType		*pDstBox);

GEOMETRY_DLL_EXPORT void UnionBox3D (const Box3DType	*pCSrcBox1,
									 const Box3DType	*srcBox2,
									 Box3DType			*pDstBox);

// merge a point into the box
GEOMETRY_DLL_EXPORT void Box3DBound (Box3DType* boundbox, const Point3D* c);
GEOMETRY_DLL_EXPORT void Box3DBound (Box3DType& boundbox, const Point3D& c);

// merges more points into the box
GEOMETRY_DLL_EXPORT void Box3DBoundCoords (Int32 nCoords, const Point3D* c, Box3DType* boundbox, bool setFirst);
GEOMETRY_DLL_EXPORT void Box3DBoundCoords (const GS::Array<Point3D>& c, Box3DType* boundbox, bool setFirst = true);


GEOMETRY_DLL_EXPORT bool CheckBox3D (const Box3D& box, const double maxXY, const double maxZ);

GEOMETRY_DLL_EXPORT bool IsEqualBox3D (const Box3D& a, const Box3D& b, double epsilon);

GEOMETRY_DLL_EXPORT void CorrigateBox3D (const Box3D& inBox, Box3D& outBox, const double maxXY, const double maxZ);

GEOMETRY_DLL_EXPORT void CorrigateBox3D (Box3D& box, const double maxXY, const double maxZ);

// tests a srcBox1 against being in the srcBox2
GEOMETRY_DLL_EXPORT bool Box3DInBox3D (
										const Box3D&	srcBox1,
										const Box3D&	srcBox2,
										Boundary	boundaries,
										double eps);

GEOMETRY_DLL_EXPORT bool XBox3D (
										const Box3DType *box1,
										const Box3DType *box2,
										double eps,
										bool loose = false);

GEOMETRY_DLL_EXPORT	bool IsBox3DPointIntersect (
										const Box3D&		box,
										const Point3D&		pt,
										Boundary			boundaries,
										double				epsilon);

GEOMETRY_DLL_EXPORT bool IsBox3DsIntersect (
										const Box3D&		srcBox1,
										const Box3D&		srcBox2,
										Boundary			boundaries,
										double				eps);

inline	Box2DData	ToBox2D (const Box3DType& abox);

inline	F_Box3D		ToF_Box3D (const Box3D& box);


GEOMETRY_DLL_EXPORT GSErrCode ReadXMLBox3D (GS::XMLIChannel& ic, Box3DType& box, const char* tagName = nullptr);
GEOMETRY_DLL_EXPORT GSErrCode WriteXMLBox3D (GS::XMLOChannel& oc, const Box3DType& box, const char* tagName = nullptr);
GEOMETRY_DLL_EXPORT GSErrCode ReadXMLFBox3D (GS::XMLIChannel& ic, F_Box3DType& box, const char* tagName = "BOX3D");
GEOMETRY_DLL_EXPORT GSErrCode WriteXMLFBox3D (GS::XMLOChannel& oc, const F_Box3DType& box, const char* tagName = "BOX3D");

GEOMETRY_DLL_EXPORT GSErrCode ReadBox3D (GS::IChannel& ic, Box3DType& box);
GEOMETRY_DLL_EXPORT GSErrCode WriteBox3D (GS::OChannel& oc, const Box3DType& box);
GEOMETRY_DLL_EXPORT GSErrCode ReadFBox3D (GS::IChannel& ic, F_Box3DType& box);
GEOMETRY_DLL_EXPORT GSErrCode WriteFBox3D (GS::OChannel& oc, const F_Box3DType& box);

inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Box3D& box, const char* tagName = nullptr)		{ return Geometry::ReadXMLBox3D (ic, box, tagName); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Box3D& box, const char* tagName = nullptr)	{ return Geometry::WriteXMLBox3D (oc, box, tagName); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, F_Box3D& box)										{ return Geometry::ReadXMLFBox3D (ic, box); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const F_Box3D& box)								{ return Geometry::WriteXMLFBox3D (oc, box); }

GEOMETRY_DLL_EXPORT GSErrCode Read (GS::IChannel& ic, F_Box3D& box);
GEOMETRY_DLL_EXPORT GSErrCode Write (GS::OChannel& oc, const F_Box3D& box);

}	// namespace Geometry


GEOMETRY_DLL_EXPORT GSErrCode Read (GS::IChannel& ic, Box3D& box);
GEOMETRY_DLL_EXPORT GSErrCode Write (GS::OChannel& oc, const Box3D& box);
GEOMETRY_DLL_EXPORT GSErrCode Store (GS::ObjectState& os, const F_Box3D& fBox);
GEOMETRY_DLL_EXPORT GSErrCode Restore (const GS::ObjectState& os, F_Box3D& fBox);
GEOMETRY_DLL_EXPORT GSErrCode Store (GS::ObjectState& os, const Box3D& fBox);
GEOMETRY_DLL_EXPORT GSErrCode Restore (const GS::ObjectState& os, Box3D& fBox);


void Geometry::SetBox3D (
						Box3DType*	abox,
						double 		xMin,
						double 		yMin,
						double		zMin,
						double 		xMax,
						double 		yMax,
						double		zMax)
{
	abox->xMin = xMin;
	abox->yMin = yMin;
	abox->zMin = zMin;
	abox->xMax = xMax;
	abox->yMax = yMax;
	abox->zMax = zMax;
}

Box2DData Geometry::ToBox2D (const Box3DType& abox)
{
	Box2DData tmp;
	SetBox (&tmp, abox.xMin, abox.yMin, abox.xMax, abox.yMax);
	return tmp;
}

F_Box3D	Geometry::ToF_Box3D (const Box3D& box)
{
	F_Box3D fBounds;

	fBounds.xMin = static_cast<float> (box.xMin);
	fBounds.xMax = static_cast<float> (box.xMax);
	fBounds.yMin = static_cast<float> (box.yMin);
	fBounds.yMax = static_cast<float> (box.yMax);
	fBounds.zMin = static_cast<float> (box.zMin);
	fBounds.zMax = static_cast<float> (box.zMax);

	if (fBounds.xMin > box.xMin)
		fBounds.xMin = std::nextafter (static_cast<float> (box.xMin), -INFINITY);
	if (fBounds.xMax < box.xMax)
		fBounds.xMax = std::nextafter (static_cast<float> (box.xMax), INFINITY);
	if (fBounds.yMin > box.yMin)
		fBounds.yMin = std::nextafter (static_cast<float> (box.yMin), -INFINITY);
	if (fBounds.yMax < box.yMax)
		fBounds.yMax = std::nextafter (static_cast<float> (box.yMax), INFINITY);
	if (fBounds.zMin > box.zMin)
		fBounds.zMin = std::nextafter (static_cast<float> (box.zMin), -INFINITY);
	if (fBounds.zMax < box.zMax)
		fBounds.zMax = std::nextafter (static_cast<float> (box.zMax), INFINITY);

	DBASSERT (fBounds.xMin <= box.xMin);
	DBASSERT (fBounds.xMax >= box.xMax);
	DBASSERT (fBounds.yMin <= box.yMin);
	DBASSERT (fBounds.yMax >= box.yMax);
	DBASSERT (fBounds.zMin <= box.zMin);
	DBASSERT (fBounds.zMax >= box.zMax);

	return fBounds;
}

#endif
