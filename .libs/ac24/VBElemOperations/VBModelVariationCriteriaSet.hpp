// *********************************************************************************************************************
// File:			VBModelVariationCriteriaSet.hpp
//
// Module:		    VBElemeOperations
// Namespace:		VBModel
// Purpose:			Collects all the criteria by which AC decides if an element is visible / elements will be connected
// Contact person:	FLT
//
// *********************************************************************************************************************

#if !defined VBModelVariationCriteriaSET_HPP
#define VBModelVariationCriteriaSET_HPP

#pragma once

// from self
#include "VBElemOperationsExport.hpp"

// from VBModel
#include "ModelVariationCriteriaSetBase.hpp"

// from Phasing
#include "PhasingTypes.hpp"

// from Markup
#include "MarkupModelVariationCriteria.hpp"

namespace VBD {
class View;
typedef ODB::ConstRef<View> ViewConstRef;

class ViewSetting;
typedef ODB::ConstRef<ViewSetting> ViewSettingConstRef;
}

namespace LM {
class LibrarySet;
}

namespace EDB {
class Project;
typedef ODB::ConstRef<Project> ProjectConstRef;
}

namespace AM { class VisibilitySettings; }


namespace VBModel {

class VB_ELEM_OPERATIONS_DLL_EXPORT VBModelVariationCriteriaSet : public ModelVariationCriteriaSetBase
{
public:
	VBModelVariationCriteriaSet (
		const VBD::ViewSettingConstRef& viewSetting,
		const EDB::ProjectConstRef& project,
		PRMU::MarkupModelVariationCriteria::OutOfModel outOfModel = PRMU::MarkupModelVariationCriteria::NotInPartition,
		const LM::LibrarySet* librarySet = nullptr
	);
		
	VBModelVariationCriteriaSet (
		const VBD::ViewConstRef& view,
		const EDB::ProjectConstRef& project,
		PRMU::MarkupModelVariationCriteria::OutOfModel outOfModel = PRMU::MarkupModelVariationCriteria::NotInPartition,
		const LM::LibrarySet* librarySet = nullptr
	);

	VBModelVariationCriteriaSet (
		const GS::HashTable<ADB::AttributeIndex, Int32>& layerConnectionClassIds,
		const Phasing::PlanTypeValueConstRef& planType,
		const EDB::ProjectConstRef& project,
		const GS::Optional<EffectiveComposite::Structure>& structureDisplay,
		const GS::Optional<AM::VisibilitySettings>& analyticalModelVisibility,
		PRMU::MarkupModelVariationCriteria::OutOfModel outOfModel = PRMU::MarkupModelVariationCriteria::NotInPartition,
		const LM::LibrarySet* librarySet = nullptr
	);
	
	virtual ~VBModelVariationCriteriaSet ();

	const GS::Array<IModelVariationCriteria*>& GetCriterias ();
};

}	//namespace VBModel


#endif