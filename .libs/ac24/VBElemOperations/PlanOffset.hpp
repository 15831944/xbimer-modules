// *********************************************************************************************************************
// Description:		Plan file offset
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	KG
//
// SG compatible
// *********************************************************************************************************************

#ifndef	VBEO_PLAN_OFFSET_HPP
#define	VBEO_PLAN_OFFSET_HPP

#pragma once

// from VBElements
#include "VBElemSet/ElemSetType.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

namespace VBEO {


VB_ELEM_OPERATIONS_DLL_EXPORT
void		CalculateTheoreticalGravityPoint	(VBES::ElemSetRef elemSet, Coord* sumCoord, Box2DData* boundBox);

enum ShiftDBFlags {
	SkipStoringOffset		= 0x1,
	LogicalConstOperation	= 0x2
};

VB_ELEM_OPERATIONS_DLL_EXPORT
void		ShiftDB								(VBES::ElemSetRef elemSet, const Vector& v, const double trScalePer1000, const UInt32 flags);


}		// namespace VBEO


#endif	// VBEO_PLAN_OFFSET_HPP
