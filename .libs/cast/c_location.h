#pragma once

#ifndef __LOCATION_CAST_H__
#define __LOCATION_CAST_H__

#include "pybind11.h"
#include "Location.hpp"

using namespace IO;
using namespace GS;

namespace pybind11 {
	namespace detail {
		template <> class type_caster<Location> {
		public:
			bool load(handle src, bool /*convert*/) {
				if (!src) {
					return false;
				}
				
				if (!PyUnicode_Check(src.ptr()) && PYBIND11_BYTES_CHECK(src.ptr())) {
					auto _bytes = PYBIND11_BYTES_AS_STRING(src.ptr());
					auto _byteLen = PYBIND11_BYTES_SIZE(src.ptr());

					if (_bytes) {
						GS::UniString path(_bytes, (USize)_byteLen, GSCharCode::CC_System);
						this->value = IO::Location(path);
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
				GS::UniString path(_bytes, (USize)_byteLen, CC_UTF8);
				this->value = IO::Location(path);
				return true;
			}

			static handle cast(IO::Location src, return_value_policy /* policy */, handle /* parent */) {
				auto _bytes = src.ToDisplayText().ToCStr().Get();
				auto _byteLen = strlen(_bytes);
				return PyUnicode_DecodeUTF8(_bytes, _byteLen, nullptr);
			}


			PYBIND11_TYPE_CASTER(Location, _(PYBIND11_STRING_NAME));
		};
	}
}

#endif // !__LOCATION_CAST_H__
