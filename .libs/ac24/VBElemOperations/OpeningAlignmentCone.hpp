#ifndef _OPENING_ALIGNMENT_CONE_HPP_
#define _OPENING_ALIGNMENT_CONE_HPP_
#pragma once

// === Includes ========================================================================================================

#include "InfiniteCone.hpp"
#include "OpeningAlignmentSurfaceBase.hpp"

// =====================================================================================================================

namespace VBEO {
namespace Opening {

class VB_ELEM_OPERATIONS_DLL_EXPORT_FOR_TEST AlignmentCone : public AlignmentSurfaceBase
{
public:
	AlignmentCone (const Geometry::InfiniteCone& cone);
	virtual ~AlignmentCone ();

	virtual void Transform (const TRANMAT& trafo) override;

	Geometry::InfiniteCone GetCone () const;

private:
	using AlignmentSurfaceBase::FramePosition;
	
	virtual FramePosition CalculateAlignedFramePosition (const FramePosition& originalPosition) const override;

	Geometry::InfiniteCone cone;
};

}
}

#endif
