#include "stdafx.h"
#include "./cColor.h"

#include "Color.hpp"

using namespace Gfx;

void loadColorClass(module &m) {
	class_<Color>(m, "Color")
		.def(init<>())
		.def(init<UINT8, UINT8, UINT8, UINT8>(),arg("r"),arg("g"),arg("b"),arg("a")=0xFF)
		.def("__str__", [](const Color &c) {
			return "(" + std::to_string(c.GetRed()) + "," + std::to_string(c.GetGreen()) + "," + std::to_string(c.GetBlue()) + "," + std::to_string(c.GetAlpha()) + ")";
		})
		.def(self==self)
		.def(self!=self)
		.def_property("Red", (UINT8(Color::*)(void) const)&Color::GetRed, (void(Color::*)(UINT8))&Color::SetRed)
		.def_property("Green", (UINT8(Color::*)(void) const)&Color::GetGreen, (void(Color::*)(UINT8))&Color::SetGreen)
		.def_property("Blue", (UINT8(Color::*)(void) const)&Color::GetBlue, (void(Color::*)(UINT8))&Color::SetBlue)
		.def_property("Alpha", (UINT8(Color::*)(void) const)&Color::GetAlpha, (void(Color::*)(UINT8))&Color::SetAlpha)

		.def_readonly_static("Black",&Color::Black)
		.def_readonly_static("DarkGray", &Color::DarkGray)
		.def_readonly_static("Gray", &Color::Gray)
		.def_readonly_static("LightGray", &Color::LightGray)
		.def_readonly_static("White", &Color::White)
		.def_readonly_static("Red", &Color::Red)
		.def_readonly_static("Green", &Color::Green)
		.def_readonly_static("Blue", &Color::Blue)
		.def_readonly_static("Cyan", &Color::Cyan)
		.def_readonly_static("Magenta", &Color::Magenta)
		.def_readonly_static("Yellow", &Color::Yellow)
		;


}