// *********************************************************************************************************************
// Change Propagator for Model Change Evaluations 
//
// Module:			Phasing
// Namespace:		Phasing
// Contact person:	KKr
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef STANDARDCATEGORYPROPAGATORS_HPP
#define STANDARDCATEGORYPROPAGATORS_HPP

#include "PhasingExport.hpp"
#include "ODBDependencyNode.hpp"

namespace Phasing {

extern PHASING_DLL_EXPORT ODB::DependencyNode renovationStatusToElemPropagatorNode;
extern PHASING_DLL_EXPORT ODB::DependencyNode renovationStatusLinkToElemPropagatorNode;

extern PHASING_DLL_EXPORT ODB::DependencyNode planTypeToElemPropagatorNode;
extern PHASING_DLL_EXPORT ODB::DependencyNode planTypeLinkToElemPropagatorNode;

}

#endif
