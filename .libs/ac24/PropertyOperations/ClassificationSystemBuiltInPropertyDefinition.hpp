// Contact person: KV

#ifndef CLASSIFICATIONSYSTEM_BUILTIN_PROPERTY_DEFINITION_HPP
#define CLASSIFICATIONSYSTEM_BUILTIN_PROPERTY_DEFINITION_HPP

#pragma once

// === Includes ========================================================================================================

// from Classification
#include "ClassificationTypes.hpp"

// from PropertyOperations
#include "DynamicBuiltInPropertyDefinition.hpp"
#include "SingleValueDescriptor.hpp"

// === Predeclarations =================================================================================================

namespace Property {
	class ClassificationSystemBuiltInPropertyDefinition;
	typedef GS::SharedPtr<ClassificationSystemBuiltInPropertyDefinition> ClassificationSystemBuiltInPropertyDefinitionPtr;
	typedef GS::ConstSharedPtr<ClassificationSystemBuiltInPropertyDefinition> ClassificationSystemBuiltInPropertyDefinitionConstPtr;

	class ClassificationSystemBuiltInPropertyDefinitionGroup;
	typedef ODB::Ref<ClassificationSystemBuiltInPropertyDefinitionGroup> ClassificationSystemBuiltInPropertyDefinitionGroupRef;
	typedef ODB::ConstRef<ClassificationSystemBuiltInPropertyDefinitionGroup> ClassificationSystemBuiltInPropertyDefinitionGroupConstRef;
}

// =====================================================================================================================

namespace Property {

class ClassificationSystemBuiltInPropertyDefinition;

class ClassificationValueDescriptor : public SingleValueDescriptor
{
public:
	ClassificationValueDescriptor (const ClassificationSystemBuiltInPropertyDefinition& definition);

	virtual	bool		IsValidValue (const GS::DynamicValue* value) const override;

	virtual	GSErrCode	WriteValueToXML (GS::XMLOChannel& oc, const GS::DynamicValue* value) const override;
	virtual	GSErrCode	ReadValueFromXML (GS::XMLIChannel& ic, GS::AutoPtr<GS::DynamicValue>& value) const override;

private:
	const ClassificationSystemBuiltInPropertyDefinition& definition;
};

class PROPERTY_OPERATIONS_DLL_EXPORT ClassificationSystemBuiltInPropertyDefinition : public DynamicBuiltInPropertyDefinition
{
public:
	ClassificationSystemBuiltInPropertyDefinition (const CLS::IClassificationSystemConstRef& system, const ClassificationSystemBuiltInPropertyDefinitionGroupConstRef& group);
	virtual ~ClassificationSystemBuiltInPropertyDefinition ();

	virtual	GS::Guid										GetGuid								() const override;
	virtual	GS::UniString									GetName								() const override;
	virtual	GS::Optional<NonLocalizedPropertyName>			GetNonLocalizedName					() const override;
	virtual	PropertyDefinitionUserId						GetUserId							() const override;
	virtual	GS::UniString									GetDescription						() const override;
	virtual	const IValueDescriptor*							GetValueDescriptor					() const override;
	virtual	PropertyValue									GetDefaultValue						() const override;
	virtual	DynamicBuiltInPropertyDefinitionGroupConstRef	GetGroup							() const override;
	virtual	Measure											GetMeasure							() const override;
	virtual	bool											ValueCanBeEditable					() const override;

	virtual	GSErrCode										WriteContentForChecksum				(GS::OChannel& oc) const override;
	virtual GS::AutoPtr<GS::DynamicValue>						ResolvePropertyValue				(const GS::DynamicValue* originalValue) const override;

	virtual bool											IsAvailable							(const PropertyOwner& propertyOwner) const override;
	virtual bool											IsEvaluable							(const PropertyOwner& propertyOwner) const override;
	virtual	PropertyValue									GetValue							(const PropertyOwner& propertyOwner, const GS::DynamicValueConversionRules& conversionRules) const override;
	virtual	bool											ValueIsEditable						(const PropertyOwner& propertyOwner) const override;
	virtual	void											SetValue							(const PropertyOwner& propertyOwner, const GS::DynamicValue* newValue) const override;
	virtual	void											RemoveCustomValue					(const PropertyOwner& propertyOwner) const override;
	virtual	Measure											GetPropertyOwnerDependentMeasure	(const PropertyOwner& propertyOwner) const override;
	virtual bool											UsesAnyOfTheseTechnologies			(const TechnologyList& technologies, Technology::ActionType actionType) const override;

			CLS::IClassificationSystemConstRef				GetSystem							() const;
			CLS::IClassificationItemConstRef				GetItemInSystem						(const GS::Guid& itemGuid) const;

	static GS::UniString									GetNameForSystem (const CLS::IClassificationSystemConstRef& system);

private:
	CLS::IClassificationSystemConstRef system;
	ClassificationValueDescriptor valueDescriptor;
	ClassificationSystemBuiltInPropertyDefinitionGroupConstRef group;
};

}

#endif
