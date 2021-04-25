#ifndef CREATE_OPENINGS_FROM_SELECTION_PARAMETERS_HPP
#define CREATE_OPENINGS_FROM_SELECTION_PARAMETERS_HPP
#pragma once

#include "VBElemOperationsExport.hpp"


namespace VBEO {
namespace Opening {


	class VB_ELEM_OPERATIONS_DLL_EXPORT CreateOpeningsFromSelectionParameters : public GS::Object {
		DECLARE_CLASS_INFO
	public:
		enum class PreferredShape {
			Automatic,
			Rectangle,
			Circle
		};

		enum class NumberOfOpenings {
			OneOpeningPerElement,
			CombineOpeningsIfCloserThanLowerBound
		};

		enum class LinkMergeValue {
			ChainMergeOpeningValue,
			UnChainMergeOpeningValue
		};

		enum class ElementIdType {
			Inherit,
			ToolDefaults
		};

		enum class LastOpeninhgsLowerBoundChanged {
			LengthwiseChanged,
			SidewayChanged
		};

	private:
		UInt32 mSelectedOriginalElementsNumber;
		PreferredShape mOpeningShape;
		double mOffset;
		bool mKeepOriginalElements;
		NumberOfOpenings mNumberOfOpeningsLengthwise;
		double mCombineOpeningsLengthwiseLowerBound;
		double mCombineOpeningsLengthwiseLowerBoundLastSet;
		NumberOfOpenings mNumberOfOpeningsSideway;
		double mCombineOpeningsSidewayLowerBound;
		double mCombineOpeningsSidewayLowerBoundLastSet;
		LastOpeninhgsLowerBoundChanged mCombineOpeningsLastChanged;
		LinkMergeValue mLinkMergeValue;
		ElementIdType mElementIdType;

	public:
		CreateOpeningsFromSelectionParameters ();
		CreateOpeningsFromSelectionParameters (UInt32 inSelectedOriginalElementsNumber, PreferredShape inShape,
			double inOffset, bool inKeepOriginalElements, NumberOfOpenings inNumberOfOpeningsLengthwise, double inCombineOpeningsLengthwiseLowerBound, double inCombineOpeningsLengthwiseLowerBoundLastSet, 
			NumberOfOpenings inNumberOfOpeningsSideway, double inCombineOpeningsSidewayLowerBound, double inCombineOpeningsSidewayLowerBoundLastSet, LastOpeninhgsLowerBoundChanged inCombineOpeningsLastChanged, LinkMergeValue inLinkMergeValue, ElementIdType inElementId);

		UInt32 GetSelectedOriginalElementsNumber () const;
		PreferredShape GetOpeningShape () const;
		double GetOffset () const;
		bool IsOriginalElementsKept () const;
		NumberOfOpenings GetNumberOfOpeningsLengthwise () const;
		double GetCombineOpeningsLengthwiseLowerBound () const;
		double GetCombineOpeningsLengthwiseLowerBoundLastSet () const;
		NumberOfOpenings GetNumberOfOpeningsSideway () const;
		double GetCombineOpeningsSidewayLowerBound () const;
		double GetCombineOpeningsSidewayLowerBoundLastSet () const;
		LastOpeninhgsLowerBoundChanged GetCombineOpeningsLastChanged () const;
		LinkMergeValue GetLinkMergeValue () const;
		ElementIdType GetElementIdType () const;

		void SetSelectedOriginalElementsNumber (const UInt32& value);
		void SetOpeningShape (const PreferredShape& value);
		void SetOffset (const double& value);
		void KeepOriginalElementsOn ();
		void KeepOriginalElementsOff ();
		void SetNumberOfOpeningsLengthwise (const NumberOfOpenings& value);
		void SetCombineOpeningsLengthwiseLowerBound (const double& value);
		void SetCombineOpeningsLengthwiseLowerBoundLastSet (const double& value);
		void SetNumberOfOpeningsSideway (const NumberOfOpenings& value);
		void SetCombineOpeningsSidewayLowerBound (const double& value);
		void SetCombineOpeningsSidewayLowerBoundLastSet (const double& value);
		void SetCombineOpeningsLastChanged (const LastOpeninhgsLowerBoundChanged& value);
		void SetLinkMergeValue (const LinkMergeValue& value);
		void SetElementIdType (const ElementIdType& value);

		virtual	GSErrCode	Read (GS::IChannel& ic) override;
		virtual	GSErrCode	Write (GS::OChannel& oc) const override;

	private:
		GSErrCode ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode ReadVersion2 (GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode WriteVersion1 (GS::OChannel& oc) const;
		GSErrCode WriteVersion2 (GS::OChannel& oc) const;

	};
}
}


#endif