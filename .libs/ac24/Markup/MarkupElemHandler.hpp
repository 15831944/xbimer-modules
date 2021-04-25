// *********************************************************************************************************************
// MarkupEntry: Markup related element collector
//
// Module:			Markup
// Namespace:		PRMU
// Contact person:	EB
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (MARKUPELEMHANDLER_HPP)
#define MARKUPELEMHANDLER_HPP

// --- Includes	--------------------------------------------------------------------------------------------------------

// from Markup
#include "EntryComponent.hpp"
#include "MarkupExport.hpp"

// === MarkupElemHandler class ===============================================================================================

namespace PRMU {

class MARKUP_DLL_EXPORT MarkupElemHandler {
public:
	static bool IsElemAssociativelyMarkupable (const EDB::GeneralElemConstRef& elem);
	static bool IsOnlyAssociativelyMarkupCompatible (const EDB::GeneralElemConstRef& elem);
	static EDB::GeneralElemConstRefList GetAssociatedElems (const EDB::GeneralElemConstRef& elem);

	static bool IsMarkupCompatibleSubelem (const EDB::GeneralElemConstRef& elem);

	static EDB::GeneralElemRefList CollectMarkupableElems (const PRMU::EntryComponent::Type& compType,
														   const EDB::GeneralElemRefList& selection);
};

}	// namespace PRMU

#endif