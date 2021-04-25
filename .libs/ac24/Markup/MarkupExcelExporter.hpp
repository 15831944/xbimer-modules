// *********************************************************************************************************************
// Markup Exporter 
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	FEs
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef MARKUPEXPORTER_HPP
#define MARKUPEXPORTER_HPP

#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------
// form Markup
#include "MarkupEntry.hpp"
#include "MarkupExport.hpp"
#include "MarkupInterfaces.hpp"

// from LibXL
#include "LibXL/libxl.h"

namespace PRMU {

class MARKUP_DLL_EXPORT MarkupExcelExporter {
	PRMU::MarkupEntryConstRefList	markupEntries;
	bool							isXLSX;
	GS::UniString					sheetName;
	GS::Ref<PRMU::TWUserParams>		twUserParams;
public:
	MarkupExcelExporter (PRMU::MarkupEntryConstRefList markupEntries, bool isXLSX, const GS::UniString& sheetName, GS::Ref<PRMU::TWUserParams> twUserParams);
	virtual ~MarkupExcelExporter ();

	GSErrCode			ToFile					(const IO::Location& location);

private:
	bool				AddMarkupAttributes		(libxl::Book* book, PRMU::MarkupEntryConstRefList markupEntries);
};
}
#endif