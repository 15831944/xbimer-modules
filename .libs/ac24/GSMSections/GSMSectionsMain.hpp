// *********************************************************************************************************************
// Description:		LibraryManage common data
//
// Module:			LibraryManager
// Namespace:		LM
// Contact person:	AGY
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GSMSECTIONSMAIN_HPP)
#define GSMSECTIONSMAIN_HPP

#pragma once


#include "GSRoot.hpp"
#include "GSMSectionsExport.h"
#include "ODBReference.hpp"
#include "SymbolFile.hpp"

namespace GDL {
	class Parameters;
}

namespace LM {
	class LibPartId;
	typedef ODB::ConstRef<LibPartId>	LibPartIdConstRef;
	class LibrarySet;
}

GSMSECTIONS_DLL_EXPORT
GSErr	GSMSECTIONS_CALL	SwapLP_SectByType (GS::PlatformSign	inplatform,
											   UInt32			sectType,
											   GSHandle			syWorkHdl,
											   short			syVersion,
											   short			sectVersion,
											   GS::PlatformSign	toplatform);	// cel platform

GSMSECTIONS_DLL_EXPORT
bool	GSMSECTIONS_CALL	CreateCurrentLibPartParameters (const LPF::SymbolFile*	symbolFile,
														    GDL::Parameters&		coreParamList,
														    GDL::Parameters&		currentLibPartParamList);
GSMSECTIONS_DLL_EXPORT
GSErrCode	GSMSECTIONS_CALL GetFullGdlScript (const LPF::SymbolFile& symFile, UInt32 sectType,
											   GS::UniString& fullScript, Int32* masterSize = nullptr);

struct GlobalsFilter {
	enum E {
		All,
		ViewDependent,
		ViewIndependent
	};
};

#endif
