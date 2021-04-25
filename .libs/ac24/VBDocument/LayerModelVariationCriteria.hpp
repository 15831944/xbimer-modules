// *********************************************************************************************************************
// File:			LayerModelVariationCriteria.hpp
//
// Module:		    VBDocument
// Namespace:		VBD
// Contact person:	VaLa
//
// *********************************************************************************************************************

#if !defined LAYERModelVariationCriteria_HPP
#define LAYERModelVariationCriteria_HPP

#pragma once

#include "VBDocumentExport.hpp"

// from VBModel
#include "IModelVariationCriteria.hpp"

// from VBAttributes
#include "ADBAttributeIndex.hpp"

// from GSRoot
#include "HashTable.hpp"

namespace VBAttr {
class LayerComb;
typedef ODB::ConstRef<LayerComb>	LayerCombConstRef;
}

namespace VBD {

class VBDOCUMENT_DLL_EXPORT LayerModelVariationCriteria : public VBModel::IModelVariationCriteria
{
	GS::HashTable<ADB::AttributeIndex, Int32>	layerConnectionClassIds;

	Int32 GetLayerConnClassId (const ADB::AttributeIndex& layerIndex) const;

	LayerModelVariationCriteria () = default;
public:
	LayerModelVariationCriteria (VBAttr::LayerCombConstRef layerComb);
	LayerModelVariationCriteria (const GS::HashTable<ADB::AttributeIndex, Int32>& layerConnectionClassIds);
	virtual ~LayerModelVariationCriteria ();

	virtual IModelVariationCriteria* Clone (void) const override;
	virtual inline bool IsInPartition	   (const EDB::GeneralElemConstRef& /*elem*/) const override { return true; };
	virtual bool		AreInSamePartition (const EDB::GeneralElemConstRef& elem1, const EDB::GeneralElemConstRef& elem2) const override;
};

}		//namespace VBD


#endif