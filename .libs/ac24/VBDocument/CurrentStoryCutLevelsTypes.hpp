// *********************************************************************************************************************
// Description:		Predeclarations for VBD::FloorPlanCutLevels and VBD::CurrentStoryCutLevels.
//
// Module:			VBD
// Namespace:		VBD
// Contact person:	ZM
//
// *********************************************************************************************************************


#ifndef CURRENTSTORYCUTLEVELSTYPES_HPP
#define CURRENTSTORYCUTLEVELSTYPES_HPP

#pragma once


// === Predeclarations =================================================================================================

namespace VBD {
	class FloorPlanCutLevels;
	using FloorPlanCutLevelsRef			= ODB::Ref<FloorPlanCutLevels>;
	using FloorPlanCutLevelsConstRef	= ODB::ConstRef<FloorPlanCutLevels>;

	class CurrentStoryCutLevels;
	using CurrentStoryCutLevelsRef		= ODB::Ref<CurrentStoryCutLevels>;
	using CurrentStoryCutLevelsConstRef	= ODB::ConstRef<CurrentStoryCutLevels>;
}


#endif
