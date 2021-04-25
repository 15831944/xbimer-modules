/****************************************************************************/
// Filename:		MarkupEventLogger.hpp
// Description:
// Project:			B-205
// Contact person:	SJ
/****************************************************************************/
#if !defined (MARKUPEVENTLOGGER_HPP)
#define MARKUPEVENTLOGGER_HPP

#pragma once

#include "MarkupExport.hpp"

// from UsageLogger
#include "UsageLogger.hpp"

// from Markup
#include "Suggestion.hpp"

static USL::UsageRecord uslMUImportExport		(GS::Guid ("6CF6B09E-32FD-455A-BA43-8A0E1AEFB1F1"));
static USL::UsageRecord uslMUDragAndDrop		(GS::Guid ("8B394102-7B50-44C9-BD3A-2980C07E71D1"));
static USL::UsageRecord uslMUCreated			(GS::Guid ("BE01DFF6-B2CE-4417-A517-F29602980F18"));
static USL::UsageRecord uslMUComponentEvent		(GS::Guid ("D9B535B8-F90D-4E33-ABE2-D6376876E381"));


namespace PRMUtils {

class MARKUP_DLL_EXPORT EventLogger
{
public:
	enum MUIOLogParam {
		BCFImport		= 1,
		BCFExport		= 2,
		DWFImport		= 3
	};
	enum ErrorType {
		NoError			= 1,
		MissingTWRights = 2,
		DuplicatesFound	= 3,
		FileWriteError	= 4,
		FileReadError	= 5
	};
	enum CreateType {
		Simple			= 1,
		Response		= 2
	};
	enum ComponentEventType {
		Created = 1,
		Accepted = 2,
		Deleted = 3
	};

	static void	MarkUpDropped ();
	static void	ImportExport (MUIOLogParam formatAndDirection, ErrorType errType);
	static void	MarkUpCreated (CreateType type);
	static void MarkUpComponentCreated (const PRMU::EntryComponentConstRef& entryComponent);
	static void MarkUpComponentAccepted (const PRMU::EntryComponentConstRef& entryComponent, const GS::HashSet<PRMU::Suggestion::AcceptType>& acceptType);
	static void MarkUpComponentDeleted (const PRMU::EntryComponentConstRef& entryComponent);
};


} //PRMUtils


#endif
