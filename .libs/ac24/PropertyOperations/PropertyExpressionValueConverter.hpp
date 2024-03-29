// Contact person : KiP

#ifndef PROPERTY_OPERATIONS_PROPERTYVSEXPRESSIONVALUECONVERTER_HPP
#define PROPERTY_OPERATIONS_PROPERTYVSEXPRESSIONVALUECONVERTER_HPP

#pragma once

#include "PropertyOperationsExport.hpp"

#include "DynamicValue.hpp"
#include "DynamicValueConversionRules.hpp"
#include "PropertyDefinitionExtension.hpp"
#include "ExpressionValue.hpp"
#include "EvaluationLocaleSettings.hpp"
#include "PropertyMeasure.hpp"

// =====================================================================================================================

namespace Property {


class PROPERTY_OPERATIONS_DLL_EXPORT IPropertyTypeInfo
{
public:
	IPropertyTypeInfo ();
	virtual ~IPropertyTypeInfo ();

	virtual Measure								GetMeasure () const = 0;
	virtual CollectionType						GetCollectionType () const = 0;
	virtual ValueType							GetValueType () const = 0;
	virtual const IValueDescriptor*				GetValueDescriptor () const = 0;
	virtual const GS::DynamicValueConversionRules&	GetVariantConversionRules () const = 0;
};


typedef GS::Ref<IPropertyTypeInfo>	IPropertyTypeInfoPtr;


class PROPERTY_OPERATIONS_DLL_EXPORT IResolvablePropertyTypeInfo : public IPropertyTypeInfo
{
public:
	IResolvablePropertyTypeInfo ();
	virtual ~IResolvablePropertyTypeInfo ();

	virtual GS::Owner<GS::DynamicValue>				ResolvePropertyValue (const PropertyValue& propertyValue) const = 0;
};


class PROPERTY_OPERATIONS_DLL_EXPORT UserDefinedPropertyTypeInfo : public IResolvablePropertyTypeInfo
{
public:
	UserDefinedPropertyTypeInfo (const UserDefinedPropertyDefinitionConstRef& propertyDefinition, 
								 const GS::DynamicValueConversionRules& variantConversionRules);
	virtual ~UserDefinedPropertyTypeInfo ();

	virtual Measure								GetMeasure () const override;
	virtual CollectionType						GetCollectionType () const override;
	virtual ValueType							GetValueType () const override;
	virtual const IValueDescriptor*				GetValueDescriptor () const override;
	virtual const GS::DynamicValueConversionRules&	GetVariantConversionRules () const override;
	virtual GS::Owner<GS::DynamicValue>				ResolvePropertyValue (const PropertyValue& propertyValue) const override;

private:
	UserDefinedPropertyDefinitionConstRef	propertyDefinition;
	const GS::DynamicValueConversionRules&		variantConversionRules;
};


class PROPERTY_OPERATIONS_DLL_EXPORT PropertyDefinitionExtensionTypeInfoForConversion : public IResolvablePropertyTypeInfo
{
public:
	PropertyDefinitionExtensionTypeInfoForConversion (const PropertyDefinitionExtensionConstPtr& propertyExtension,
													  const ADB::AttributeSetConstRef& attributeSet, 
													  const GS::DynamicValueConversionRules& variantConversionRules);
	virtual ~PropertyDefinitionExtensionTypeInfoForConversion ();

	virtual Measure								GetMeasure () const override;
	virtual CollectionType						GetCollectionType () const override;
	virtual ValueType							GetValueType () const override;
	virtual const IValueDescriptor*				GetValueDescriptor () const override;
	virtual const GS::DynamicValueConversionRules&	GetVariantConversionRules () const override;
	virtual GS::Owner<GS::DynamicValue>				ResolvePropertyValue (const PropertyValue& propertyValue) const override;

private:
	PropertyDefinitionExtensionConstPtr				propertyExtension;
	const ADB::AttributeSetConstRef&				attributeSet;
	const GS::DynamicValueConversionRules&				variantConversionRules;
};

PROPERTY_OPERATIONS_DLL_EXPORT
bool IsSupportedExpressionPropertyCollectionType (Property::CollectionType collectionType, const Property::IValueDescriptor* valueDescriptor);

PROPERTY_OPERATIONS_DLL_EXPORT
bool IsSupportedExpressionPropertyMeasure (const Property::Measure& measure);

PROPERTY_OPERATIONS_DLL_EXPORT
GS::Owner<GS::DynamicValueConversionRules> CreateVariantConversionRulesForExpression (Int32 nonUnitDecimalPrecision, const EP::IParsingLocaleSettings& localeSettings);

PROPERTY_OPERATIONS_DLL_EXPORT
EE::ExpressionValue		CreateUndefinedExpressionValueForProperty (const IPropertyTypeInfo& info);
PROPERTY_OPERATIONS_DLL_EXPORT
EE::ExpressionValue		PropertyValueToExpressionValue (const IResolvablePropertyTypeInfo& typeInfo, const PropertyValue& propertyValue, const EvaluationEnvironment<CallbackPermissions::NoPermissions>& env);

PROPERTY_OPERATIONS_DLL_EXPORT
EE::ExpressionValue		ResolvedPropertyValueToNativeExpressionValue (const IPropertyTypeInfo& typeInfo, const GS::DynamicValue* resolvedValue);

PROPERTY_OPERATIONS_DLL_EXPORT
GS::Owner<GS::DynamicValue>	ExpressionValueToPropertyValue (const IPropertyTypeInfo& typeInfo, const EE::ExpressionValue& expressionValue);

}

#endif
