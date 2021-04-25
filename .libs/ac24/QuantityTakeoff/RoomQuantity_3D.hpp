#ifndef GS_QT_ROOM_QUANTITY_3D_HPP
#define GS_QT_ROOM_QUANTITY_3D_HPP

#include "QuantityTakeoffExport.hpp"
#include "Model3D/Model3DFwd.hpp"
#include "Polygon2DClassDefinition.hpp"

struct WallPart;

namespace ModelCalculations {
	typedef Geometry::CustomMultiPolygon2D<bool, Geometry::PolyId, Geometry::PolyId, Geometry::PolyId>	ProjectedMultiPolygon;
}

namespace QT {
namespace Room {

using ConvertRoomFunction = std::function<Modeler::Model3DPtr (const VBElem::RoomConstRef& room)>;

QUANTITYTAKEOFF_DLL_EXPORT
void CalcSurfaceAndVolume (
	const ConvertRoomFunction& convertFunction,
	const VBElem::RoomConstRef& room,
	double *volume,
	double *bound_surf,
	double *top_surf,
	double *bot_surf,
	double *roof_top_surf,
	double *roof_bot_surf,
	double *slab_top_surf,
	double *slab_bot_surf,
	double *beam_top_surf,
	double *beam_bot_surf,
	double *wall_inset_top,
	double *wall_inset_back,
	double *wall_inset_side,
	ModelCalculations::ProjectedMultiPolygon* projected_floor,
	Modeler::Model3DPtr roomModel);

QUANTITYTAKEOFF_DLL_EXPORT
void CalcAddPars3D (
	const ConvertRoomFunction& convertFunction, 
	const VBElem::RoomRef& room, 
	GS::Array<WallPart>* wList, 
	Modeler::Model3DPtr roomModel);

}
}

#endif