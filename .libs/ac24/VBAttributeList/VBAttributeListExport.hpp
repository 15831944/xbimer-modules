#ifndef VBATTRIBUTELIST_EXPORT
#define VBATTRIBUTELIST_EXPORT

#pragma once

#include "PlatformDLLExport.hpp"

#if defined (VBATTRIBUTELIST_DLL_COMPILE)
	#define VBATTRIBUTELIST_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define VBATTRIBUTELIST_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
