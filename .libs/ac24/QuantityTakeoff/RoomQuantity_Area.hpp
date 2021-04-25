#ifndef GS_QT_ROOM_QUANTITY_AREA_HPP
#define GS_QT_ROOM_QUANTITY_AREA_HPP

#include "QuantityTakeoffExport.hpp"

#include <functional>
#include "GSProcessControl.hpp"
#include "Polygon2DClassDefinition.hpp"
#include "Model3D/Model3DFwd.hpp"
#include "RoomTypes.hpp"

namespace VBCalculations {
	class WallNotViewRelatedPolygons;
}

namespace VBD {
	class FloorPlanCutLevelsGuard;
}

namespace QT {
namespace Room {

enum class ReductionCode {
	Rest = -1,
	Wall = 0,
	Colu = 1,
	Hatch = 2,
	Gable = 3,
	CWall = 4
};

using PushPoly = std::function<void (const Geometry::Polygon2D&, ReductionCode, short)>;

enum class LinkCutElemsMode {
	LinkCutElemsToRoom,
	DontLinkCutElemsToRoom
};

class QUANTITYTAKEOFF_DLL_EXPORT ReductionPreferences {
public:
	virtual ~ReductionPreferences ();
	virtual UInt8		GetNLowAreas () const = 0;
	virtual double		GetHeightLimit (UIndex index) const = 0;
	virtual UInt8		GetRedPercent (UIndex index) const = 0;
	virtual bool		SubtractWalls () const = 0;
	virtual double		GetSubtractWallsSize () const = 0;
	virtual UInt8		GetSubtractWallsPercent () const = 0;
	virtual bool		SubtractColumns () const = 0;
	virtual double		GetSubtractColumnsSize () const = 0;
	virtual UInt8		GetSubtractColumnsPercent () const = 0;
};

class QUANTITYTAKEOFF_DLL_EXPORT ReductionEnv {
public:
	virtual ~ReductionEnv ();
	virtual const ReductionPreferences&		GetRoomReductionPreferences () = 0;
	virtual void							LinkElemToRoom (const VBElem::RoomConstRef& room, const EDB::GeneralElemConstRef& elem) = 0;
	virtual Phasing::RenovationStatusType	GetDerivedRenovationStatus (const EDB::GeneralElemConstRef& elem) = 0;
	virtual Modeler::Model3DPtr				TransformToTemp (const VBElem::RoomConstRef& room) = 0;
	virtual EDB::StoryWithRange				GetStoryWithRange (short floorNum) = 0;
	virtual VBD::FloorPlanCutLevelsGuard	GetFloorPlanCutLevelGuard (const VBElem::ModelElementConstRef& elem) = 0;
	virtual Geometry::Polygon2D				GetColumnPolygon (GS::ProcessControl& processControl, const VBElem::ColumnConstRef& column) = 0;
	virtual Geometry::MultiPolygon2D		GetCWPolygon (const VBElem::CurtainWallConstRef& curtainWall) = 0;
	virtual Geometry::IrregularPolygon2D	GetWallPoly (
		const VBElem::WallConstRef& wall,
		const EDB::FloorStructureConstRef& floorStructure,
		VBCalculations::WallNotViewRelatedPolygons& wallNotVRDPolys,
		VBD::FloorPlanCutLevelsGuard& curr2DCutData) = 0;
};

QUANTITYTAKEOFF_DLL_EXPORT
bool GetAdditionsUnion (Geometry::Polygon2D* geom1, const VBElem::RoomConstRef& room);

QUANTITYTAKEOFF_DLL_EXPORT
GSErrCode PolygonDataDifference (const Geometry::Polygon2D&		geomData1,
								 const Geometry::Polygon2D&		geomData2,
								 Geometry::MultiPolygon2D*		resultGeomData,
								 bool*							changed);

QUANTITYTAKEOFF_DLL_EXPORT
GSErrCode PolygonDataIntersection (const Geometry::Polygon2D&			geomData1,
								   const Geometry::Polygon2D&			geomData2,
								   Geometry::MultiPolygon2D*			resultGeomData);

QUANTITYTAKEOFF_DLL_EXPORT
bool SkipElement (ReductionEnv&							roomReductionEnv,
				  const Phasing::RenovationStatusType&	roomStatus, 
				  const EDB::GeneralElemConstRef&		elem);

QUANTITYTAKEOFF_DLL_EXPORT
GSErrCode CalcAddParsPolygonRelated (const VBElem::RoomRef& room);

QUANTITYTAKEOFF_DLL_EXPORT
GSErrCode CalcAddParsAreas (ReductionEnv&				roomReductionEnv,
							GS::ProcessControl&			processControl, 
							const VBElem::RoomRef&		room, 
							Modeler::Model3DPtr			cacheModel, 
							LinkCutElemsMode			linkCutElemsToRoomMode);

QUANTITYTAKEOFF_DLL_EXPORT
GSErrCode CalcReductions (ReductionEnv&					roomReductionEnv,
						  GS::ProcessControl&			processControl,
						  const VBElem::RoomConstRef&	room,
						  double&						wallReducedArea,
						  double&						cWallReducedArea,
						  double&						coluReducedArea,
						  double&						hatchReducedArea,
						  double&						gableReducedArea,
						  const PushPoly&				store,
						  Modeler::Model3DPtr			cacheModel,
						  LinkCutElemsMode				linkCutElemsToRoomMode);

}
}

#endif