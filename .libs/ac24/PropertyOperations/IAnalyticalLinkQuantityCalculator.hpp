// Contact person : MaK

#ifndef I_ANALYTICALLINK_QUANTITY_CALCULATOR_HPP
#define I_ANALYTICALLINK_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT IAnalyticalLinkQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~IAnalyticalLinkQuantityCalculator ();
};

}

#endif