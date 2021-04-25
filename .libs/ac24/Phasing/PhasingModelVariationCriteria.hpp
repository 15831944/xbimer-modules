// *********************************************************************************************************************
// File:			PhasingModelVariationCriteria.hpp
//
// Module:		    Phasing
// Namespace:		Phasing
// Contact person:	EB
//
// *********************************************************************************************************************

#if !defined PHASINGModelVariationCriteria_HPP
#define PHASINGModelVariationCriteria_HPP

#pragma once

// from Phasing
#include "PhasingExport.hpp"

// from VBElements
#include "Project.hpp"

// from VBModel
#include "IModelVariationCriteria.hpp"

// from Phasing
#include "PlanTypeValue.hpp"

// from LibraryManager
#include "LibrarySet.hpp"

namespace Phasing {

class PHASING_DLL_EXPORT PhasingModelVariationCriteria : public VBModel::IModelVariationCriteria
{
private:
	PlanTypeValueConstRef planTypeValue;
	EDB::ProjectConstRef project;
	const LM::LibrarySet* librarySet;

	PhasingModelVariationCriteria () = default;

	RenovationStatusType GetRenovationInfo (const EDB::GeneralElemConstRef& elem,
													 bool* outIsElemVisible, bool* outIsOverrideSymbolic) const;

	bool						  IsAnyPartOfOpeningVisible (const EDB::GeneralElemConstRef& opening, const RenovationStatusType openingElemStatus,
									        				 const PlanTypeConstRef&	planTypeCategory, const RenovationStatusConstRef& renovationStatusCategory,
															 const PlanTypeValueConstRef& actualPlanTypeValue) const;

public:
	PhasingModelVariationCriteria (const PlanTypeValueConstRef& planTypeValue, const EDB::ProjectConstRef& project, const LM::LibrarySet* librarySet = nullptr);
	virtual ~PhasingModelVariationCriteria ();

	virtual IModelVariationCriteria* Clone (void) const override;
	virtual bool IsInPartition		(const EDB::GeneralElemConstRef& elem) const override;
	virtual bool AreInSamePartition (const EDB::GeneralElemConstRef& elem1, const EDB::GeneralElemConstRef& elem2) const override;

	bool IsElemVisibleByPhasing (const EDB::GeneralElemConstRef&			elem,
								 const PlanTypeConstRef&			planType,
								 const RenovationStatusConstRef&	renovationStatusCategory) const;
};

}		//namespace Phasing


#endif