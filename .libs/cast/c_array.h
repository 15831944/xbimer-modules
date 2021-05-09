#pragma once

#ifndef __ARRAY_CAST_H__
#define __ARRAY_CAST_H__

#include "pybind11.h"
#include "stl.h"

using namespace GS;

namespace pybind11 {
	namespace detail {
		template <typename ArrayType, typename Value> struct base_array_caster {
			using value_conv = make_caster<Value>;

		public:
			bool load(handle src, bool convert) {
				if (!isinstance<sequence>(src)) {
					return false;
				}
					
				auto l = reinterpret_borrow<sequence>(src);

				value.EnsureSize(l.size());

				USize ctr = 0;
				for (auto it : l) {
					value_conv conv;
					if (!conv.load(it, convert)) {
						return false;
					}	
					value[ctr++] = cast_op<Value &&>(std::move(conv));
				}
				return true;
			}

			template <typename T>
			static handle cast(T &&src, return_value_policy policy, handle parent) {
				list l(src.GetSize());

				size_t index = 0;
				for (auto &&value : src) {
					auto value_ = reinterpret_steal<object>(value_conv::cast(forward_like<T>(value), policy, parent));
					if (!value_) {
						return handle();
					}
						
					PyList_SET_ITEM(l.ptr(), (ssize_t)index++, value_.release().ptr()); // steals a reference
				}

				return l.release();
			}

			PYBIND11_TYPE_CASTER(ArrayType, _("list[") + value_conv::name + _("]"));
		};

		template <typename Type> struct type_caster<Array<Type>>
			: base_array_caster<Array<Type>, Type> {
		};
	}
}


#endif // !__ARRAY_CAST_H__
