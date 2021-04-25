// *********************************************************************************************************************
// File:			MarkupModelVariationCriteria.hpp
//
// Module:		    Markup
// Namespace:		PRMU
// Contact person:	VaLa
//
// *********************************************************************************************************************

#if !defined MARKUPModelVariationCriteria_HPP
#define MARKUPModelVariationCriteria_HPP

#pragma once

#include "MarkupExport.hpp"

#include "IModelVariationCriteria.hpp"

#include "MarkupTypes.hpp"

namespace PRMU {

class MARKUP_DLL_EXPORT MarkupModelVariationCriteria : public VBModel::IModelVariationCriteria
{
public:
	enum OutOfModel {
		InPartition,
		NotInPartition
	};
private:
	MarkupEntrySetConstRef entrySet;
	OutOfModel outOfModel;

	MarkupModelVariationCriteria () = default;
public:
	MarkupModelVariationCriteria (MarkupEntrySetConstRef entrySet, OutOfModel outOfModel = NotInPartition) : entrySet (entrySet), outOfModel (outOfModel) {}
	virtual ~MarkupModelVariationCriteria ();

	virtual IModelVariationCriteria* Clone (void) const override;
	virtual bool IsInPartition		(const EDB::GeneralElemConstRef& elem) const override;
	virtual bool AreInSamePartition (const EDB::GeneralElemConstRef& elem1, const EDB::GeneralElemConstRef& elem2) const override;
};


}		//namespace PRMU


#endif