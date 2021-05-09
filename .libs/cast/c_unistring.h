#pragma once

#ifndef __UNISTRING_CAST_H__
#define __UNISTRING_CAST_H__

#include "pybind11.h"
#include "UniString.hpp"

using namespace GS;

namespace pybind11 {
	namespace detail {
		template<> class type_caster<UniString> {
		public:
			bool load(handle src, bool /*convert*/) {
				if (!src) {
					return false;
				}

				if (!PyUnicode_Check(src.ptr()) && PYBIND11_BYTES_CHECK(src.ptr())) {
					auto _bytes = PYBIND11_BYTES_AS_STRING(src.ptr());
					if (_bytes) {
						auto _byteLen = PYBIND11_BYTES_SIZE(src.ptr());
						value = UniString(_bytes, (USize)_byteLen, CC_System);
						return true;
					}
				}

				auto utfBytes = PyUnicode_AsEncodedString(src.ptr(), "utf-8", nullptr);
				if (!utfBytes) {
					PyErr_Clear();
					return false;
				}

				auto _bytes = PYBIND11_BYTES_AS_STRING(utfBytes);
				auto _byteLen = PYBIND11_BYTES_SIZE(utfBytes) / sizeof(char);

				value = UniString(_bytes, (USize)_byteLen, CC_UTF8);
				return true;
			}

			static handle cast(UniString src, return_value_policy /* policy */, handle /* parent */) {
				auto _bytes = src.ToCStr().Get();
				auto _byteLen = strlen(_bytes);
				return PyUnicode_DecodeUTF8(_bytes, _byteLen, nullptr);
			}

			PYBIND11_TYPE_CASTER(UniString, _(PYBIND11_STRING_NAME));
		};
	}
}


#endif // !__UNISTRING_CAST_H__
