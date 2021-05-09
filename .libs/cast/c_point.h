#pragma once

#ifndef __POINT_CAST_H__
#define __POINT_CAST_H__

#include "pybind11.h"
#include "Point.hpp" //GS::Point
#include "DGUtility.hpp" // DG::Point DG::NativePoint

#define POINT_CASTER_FACTORY(type,dcls,scls)							\
template<> class type_caster<dcls> {									\
public:																	\
	bool load(handle src, bool /*convert*/) {							\
		if (!src) {														\
			return false;												\
		}																\
		auto obj = reinterpret_borrow<object>(src);						\
		auto Type = module::import("XiR").attr("shape").attr(#scls);	\
		if (!obj.get_type().is(Type)) {									\
			return false;												\
		}																\
		type x = obj.attr("GetX")().cast<type>();						\
		type y = obj.attr("GetY")().cast<type>();						\
		this->value = dcls(x, y);										\
		return true;													\
	}																	\
	static handle cast(dcls src, return_value_policy /* policy */, handle /* parent */) {	\
		auto Type = module::import("XiR").attr("shape").attr(#scls);	\
		type x = static_cast<type>(src.GetX());							\
		type y = static_cast<type>(src.GetY());							\
		return Type(x, y).release();									\
	}																	\
	PYBIND11_TYPE_CASTER(dcls, _("XiR.shape."#scls));					\
}


namespace pybind11 {
	namespace detail {
		POINT_CASTER_FACTORY(float, GS::Point<float>, PointF);
		POINT_CASTER_FACTORY(double, GS::Point<double>, PointF);
		POINT_CASTER_FACTORY(short, DG::Point, Point);


		template<> class type_caster<DG::NativePoint> {
		public:
			bool load(handle src, bool /*convert*/) {
				if (!src) {
					return false;
				}

				auto obj = reinterpret_borrow<object>(src);
				auto Type = module::import("XiR").attr("shape").attr("Point");
				if (!obj.get_type().is(Type)) {
					return false;
				}

				auto x = obj.attr("GetX")().cast<short>();
				auto y = obj.attr("GetY")().cast<short>();

				this->value = DG::NativePoint(DG::NativeUnit(x), DG::NativeUnit(y));
				return true;
			}
			static handle cast(DG::NativePoint src, return_value_policy /* policy */, handle /* parent */) {
				auto Type = module::import("XiR").attr("shape").attr("Point");
				auto x = src.GetX();
				auto y = src.GetY();
				return Type(x.GetValue(), y.GetValue()).release();
			}

			PYBIND11_TYPE_CASTER(DG::NativePoint, _("XiR.shape.Point"));
		};

	}
}


#undef POINT_CASTER_FACTORY
#endif // !__POINT_CAST_H__