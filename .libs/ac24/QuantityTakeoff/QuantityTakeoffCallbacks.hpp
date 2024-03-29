// Contact person : KiP

#ifndef QUANTITY_TAKEOFF_CALLBACKS_HPP
#define QUANTITY_TAKEOFF_CALLBACKS_HPP

#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "IrregularPolygon2DClassDefinition.hpp"

// from GSModeler
#include "Sight.hpp"

// from DisplayDLL
#include "ScreenTypes.hpp"
#include "ScreenBasics.hpp"

// from VBAttributes
#include "EffectiveComposite.hpp"

// from VBElements
#include "BeamTypes.hpp"
#include "WallTypes.hpp"
#include "RoomTypes.hpp"

// from VBElemOperations
// #include "WallFloorPlanCalculations.hpp"
// #include "ColumnFloorPlanCalculations.hpp"

// from QuantityTakeoff
#include "QuantityTakeoffExport.hpp"

// === Predeclarations =================================================================================================

namespace ModelCalculations {
	typedef Geometry::CustomMultiPolygon2D<bool, Geometry::PolyId, Geometry::PolyId, Geometry::PolyId>	ProjectedMultiPolygon;
}

namespace VBElem {
	class WallConnectionList;
}

namespace VBCalculations {
	struct WallComputingEnvir;
	struct WallBeamConnectionEnvir;
	struct WallCutPlaneData;
	struct ColumnSectRec;
}

namespace Validator {
	class ElemValidator;
}

namespace SL {
	struct RebuildEnvirData;
}

namespace RoomRelations {
	class RoomRelationData;
}

struct WallPart;

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT QTCallBackInterface
{
public:
	virtual ~QTCallBackInterface ();

	// Used to calc wPoly, and wce, wbce. should be removed when wPoly calculation has implementation in lower modul, and other callbacks that use wce, wbce are removed.
	virtual Geometry::IrregularPolygon2D	CalculateWPoly  (VBElem::WallConstRef							pWall,
															 Int32											floor,
															 VBCalculations::WallComputingEnvir* const		wce = nullptr,
															 VBCalculations::WallBeamConnectionEnvir* const	wbce = nullptr) const = 0;

	// Used to get the number of the connected columns. Should use some kind of 3D calculation, and be removed when thats done.
	virtual	Int32	ConnectColumns (VBElem::WallConstRef						pWall,
									GS::Array<VBCalculations::ColumnSectRec>&	connColumns,
									SL::RebuildEnvirData*						rebuild,
									bool										from2D,
									bool										style2D,
									short										showElemFloor) const = 0;

	virtual	bool	CheckTLConn (short												showElemFloor,
								 VBElem::WallConstRef								whichWall,
								 VBElem::WallConstRef								connWall,
								 bool												conBegFl,
								 VBCalculations::WallComputingEnvir* const			wce,
								 VBCalculations::WallBeamConnectionEnvir* const		wbce) const = 0;

	virtual	void	ChooseWall2Conns (short									showElemFloor,
									  VBElem::WallConnectionList&			connections,
									  VBElem::WallConstRef					otherWall) const = 0;

	virtual	void	GetWallPartsAndZonesOfWall (VBElem::WallConstRef									wall,
												GS::Array< GS::Pair<WallPart, VBElem::RoomConstRef> >&	wallPartZoneList) const = 0;
	
	virtual void	GetRelationZone (const VBElem::RoomConstRef& rRoom, const GS::ClassInfo* otherElemClassInfo, RoomRelations::RoomRelationData& roomData) const = 0;
};

}

#endif
