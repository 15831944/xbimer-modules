#define ASSOCIATIVE_ELEM_TO_STATIC_EXTENSION_HPP
#pragma once

#include "Extension.hpp"
#include "VBElemOperationsExport.hpp"
#include "EDBGeneralDefinitions.hpp"
#include "Optional.hpp"
#include "ADBAttributeIndex.hpp"

namespace VBEO {
	
class VB_ELEM_OPERATIONS_DLL_EXPORT AssociativeElemToStaticExtension : public GS::Extension {
public:
	static GS::ExtensionId id;
	AssociativeElemToStaticExtension (GS::ClassInfo* target);
	virtual ~AssociativeElemToStaticExtension ();

	virtual void SetToStatic (const EDB::GeneralElemRef& elemRef) const = 0;
};

}