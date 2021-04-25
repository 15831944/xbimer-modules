#ifndef GS_VBEO_SYMBOL_STATISTICS_LOGGER_HPP
#define GS_VBEO_SYMBOL_STATISTICS_LOGGER_HPP

#include "VBElemOperationsExport.hpp"
#include "UniString.hpp"

namespace ODB {
	class Database;
}

namespace LM {
	class LibrarySet;
}

namespace VBEO {

enum class SymbolStatisticsLogEventType {
	LogOnOpen = 0,
	LogOnClose = 1,
	LogOnSave = 2
};

VB_ELEM_OPERATIONS_DLL_EXPORT void LogSymbolStatistics (const LM::LibrarySet& librarySet, const ODB::Database& database, const GS::UniString& projectId, SymbolStatisticsLogEventType type);

}

#endif