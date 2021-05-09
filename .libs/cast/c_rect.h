#pragma once

#ifndef __RECT_CATS_H__
#define __RECT_CATS_H__

#include "pybind11.h"
#include "Rect.hpp" // GS::Rect
#include "DGUtility.hpp" // DG::Rect DG::NativeRect

#define RECT_CASTER_FACTORY(type,dcls,scls)								\
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
		auto left = obj.attr("GetLeft")().cast<type>();					\
		auto top = obj.attr("GetTop")().cast<type>();					\
		auto right = obj.attr("GetRight")().cast<type>();				\
		auto bottom = obj.attr("GetBottom")().cast<type>();				\
		this->value = dcls(left,top,right,bottom);						\
		return true;													\
	}																	\
	static handle cast(dcls src, return_value_policy /* policy */, handle /* parent */) {	\
		auto Type = module::import("XiR").attr("shape").attr(#scls);	\
		auto left = static_cast<type>(src.GetLeft());					\
		auto top = static_cast<type>(src.GetTop());						\
		auto right = static_cast<type>(src.GetRight());					\
		auto bottom = static_cast<type>(src.GetBottom());				\
		return Type(left, top,right,bottom).release();					\
	}																	\
	PYBIND11_TYPE_CASTER(dcls, _("XiR.shape."#scls));					\
}


namespace pybind11 {
	namespace detail {
		RECT_CASTER_FACTORY(float, GS::Rect<float>, RectF);
		RECT_CASTER_FACTORY(double, GS::Rect<double>, RectF);
		RECT_CASTER_FACTORY(Int32, GS::Rect<Int32>, Rect);
		RECT_CASTER_FACTORY(short, DG::Rect, Rect);


		template<> class type_caster<DG::NativeRect> {
		public:
			bool load(handle src, bool /*convert*/) {
				if (!src) {
					return false;
				}
				auto obj = reinterpret_borrow<object>(src);
				auto Type = module::import("XiR").attr("shape").attr("Rect");
				if (!obj.get_type().is(Type)) {
					return false;
				}

				auto left = obj.attr("GetLeft")().cast<short>();					
				auto top = obj.attr("GetTop")().cast<short>();
				auto right = obj.attr("GetRight")().cast<short>();
				auto bottom = obj.attr("GetBottom")().cast<short>();

				this->value = DG::NativeRect(DG::NativeUnit(left), DG::NativeUnit(top), DG::NativeUnit(right), DG::NativeUnit(bottom));
				return true;
			}
			static handle cast(DG::NativeRect src, return_value_policy /* policy */, handle /* parent */) {
				auto Type = module::import("XiR").attr("shape").attr("Rect");

				auto left = src.GetLeft().GetValue();
				auto top = src.GetTop().GetValue();
				auto right = src.GetRight().GetValue();
				auto bottom = src.GetBottom().GetValue();
				return Type(left, top, right, bottom).release();
			}

			PYBIND11_TYPE_CASTER(DG::NativeRect, _("XiR.shape.Rect"));
		};
	}
}

#undef RECT_CASTER_FACTORY
#endif // !__RECT_CATS_H__
