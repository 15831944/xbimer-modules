#ifndef	VBELEMSURFACEDESCRIPTOR_HPP
#define	VBELEMSURFACEDESCRIPTOR_HPP

#pragma once

#include "HashCommon.hpp"

#include "ADBGeneralDefinitions.hpp"
#include "GSUtilsDefs.h"
#include "VBElemOperationsExport.hpp"

class VB_ELEM_OPERATIONS_DLL_EXPORT VBElemSurfaceDescriptor {
private:
	GSAttributeIndex buildingMaterialIndex; // TODO: M-357: because memmove and ADB::AttributeIndex virtual functions
	GSAttributeIndex surfaceIndex; // TODO: M-357: because memmove and ADB::AttributeIndex virtual functions

	VBElemSurfaceDescriptor (ADB::AttributeIndex buildingMaterialIndex, ADB::AttributeIndex surfaceIndex);

public:
	VBElemSurfaceDescriptor ();

	static VBElemSurfaceDescriptor FromSurface (const ADB::AttributeIndex& surfaceIndex);
	static VBElemSurfaceDescriptor FromBuildingMaterialCutSurface (const ADB::AttributeIndex& buildingMaterialIndex, const ADB::AttributeSetConstRef& attributeSet);

	bool IsSurfaceOfBuildingMaterial () const;
	ADB::AttributeIndex GetBuildMatIndex () const;
	ADB::AttributeIndex GetSurfaceIndex () const;

	GSErrCode		QuickRead (GS::IChannel& ic);
	GSErrCode		QuickWrite (GS::OChannel& oc) const;

	ULong			GenerateHashValue () const
	{
		return GS::GenerateHashValue (buildingMaterialIndex, surfaceIndex);
	}

	bool operator== (const VBElemSurfaceDescriptor& rhs) const 
	{
		return this->buildingMaterialIndex == rhs.buildingMaterialIndex && this->surfaceIndex == rhs.surfaceIndex;
	}

	bool operator != (const VBElemSurfaceDescriptor& rhs) const
	{
		return !this->operator == (rhs);
	}
};


#endif // VBELEMSURFACEDESCRIPTOR_HPP