// *********************************************************************************************************************
// Description:		GRAPHISOFT Resource Localizer
//
// Namespaces:		-
// Contact persons:	SzaM
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (RS_KEY_RESOLVER_HPP)
#define	RS_KEY_RESOLVER_HPP

#pragma once

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS
{
}


// --- Includes	--------------------------------------------------------------------------------------------------------

// from GRoot
#include	"Definitions.hpp"
#include	"GSRootExport.hpp"
#include	"RS.hpp"
#include	"RSTypes.hpp"
#include	"UniString.hpp"


GSROOT_DLL_EXPORT GS::UniString RSResolveKey (GSResModule resModule, const GS::UniString& key);


#endif	// RS_KEY_RESOLVER_HPP
