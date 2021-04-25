// Contact person : MaK

#ifndef I_ANALYTICALSUPPORT_QUANTITY_CALCULATOR_HPP
#define I_ANALYTICALSUPPORT_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

	class PROPERTY_OPERATIONS_DLL_EXPORT IAnalyticalSupportQuantityCalculator : public IModelElementQuantityCalculator
	{
	public:
		virtual ~IAnalyticalSupportQuantityCalculator ();
	};

}

#endif