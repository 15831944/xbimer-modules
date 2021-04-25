// *********************************************************************************************************************
// Description:		By calling the macro ENABLE_FLAG_SUPPORT () for an enum type, one can use that type as flags.
//
// Module:			GSRoot
// Namespace:		Fl
// Contact person:	BIM
//
// *********************************************************************************************************************


#ifndef FLAGSUPPORT_HPP
#define FLAGSUPPORT_HPP

#pragma once


#include "TypeTraits.hpp"


// === Macro to activate flag support functions for an enum ============================================================

#define ENABLE_FLAG_SUPPORT(E)																																	\
																																								\
static_assert (GS::IsEnum<E>, "ENABLE_FLAG_SUPPORT () can be used only with enum types.");																		\
																																								\
UNUSED_FUNCTION constexpr E				operator| (E leftOp, E rightOp)		{ return E (GS::UnderlyingType<E> (leftOp) | GS::UnderlyingType<E> (rightOp)); }	\
UNUSED_FUNCTION constexpr E				operator& (E leftOp, E rightOp)		{ return E (GS::UnderlyingType<E> (leftOp) & GS::UnderlyingType<E> (rightOp)); }	\
UNUSED_FUNCTION constexpr E				operator~ (E value)					{ return E (~GS::UnderlyingType<E> (value)); }										\
UNUSED_FUNCTION constexpr void			operator|= (E& target, E source)	{ target = target | source; }														\
UNUSED_FUNCTION constexpr void			operator&= (E& target, E source)	{ target = target & source; }														\


#define ENABLE_FLAG_SUPPORT_IN_CLASS(E)																															\
																																								\
static_assert (GS::IsEnum<E>, "ENABLE_FLAG_SUPPORT_IN_CLASS () can be used only with enum types.");																\
																																								\
UNUSED_FUNCTION friend constexpr E		operator| (E leftOp, E rightOp)		{ return E (GS::UnderlyingType<E> (leftOp) | GS::UnderlyingType<E> (rightOp)); }	\
UNUSED_FUNCTION friend constexpr E		operator& (E leftOp, E rightOp)		{ return E (GS::UnderlyingType<E> (leftOp) & GS::UnderlyingType<E> (rightOp)); }	\
UNUSED_FUNCTION friend constexpr E		operator~ (E value)					{ return E (~GS::UnderlyingType<E> (value)); }										\
UNUSED_FUNCTION friend constexpr void	operator|= (E& target, E source)	{ target = target | source; }														\
UNUSED_FUNCTION friend constexpr void	operator&= (E& target, E source)	{ target = target & source; }														\


// === Flag functions ==================================================================================================

namespace Fl {


template <class E>
constexpr void	Set (E& target, E flagsToSet)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	target |= flagsToSet;
}


template <class E>
constexpr void	Clear (E& target, E flagsToClear)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	target &= ~flagsToClear;
}


template <class E>
constexpr void	Flip (E& target, E flagsToFlip)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	target = E (GS::UnderlyingType<E> (target) ^ GS::UnderlyingType<E> (flagsToFlip));
}


template <class E>
constexpr bool	IsAllSet (E superset, E subset)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return (GS::UnderlyingType<E> (superset) & GS::UnderlyingType<E> (subset)) == GS::UnderlyingType<E> (subset);
}


template <class E>
constexpr bool	IsAnySet (E superset, E subset)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return (GS::UnderlyingType<E> (superset) & GS::UnderlyingType<E> (subset)) != 0;
}


template <class E>
constexpr bool	IsNoneSet (E superset, E subset)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return (GS::UnderlyingType<E> (superset) & GS::UnderlyingType<E> (subset)) == 0;
}


template <class E>
constexpr bool	IsSet (E superset, E subset)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return IsAllSet (superset, subset);
}


template <class E>
constexpr bool	IsSingleFlag (E flags)
{
	static_assert (GS::IsEnum<E>,                   "This function can be used only with enum types.");
	static_assert (GS::IsSame<decltype (~E {}), E>, "To use this function, enable flag support for 'E'.");

	return flags != 0 && (flags & (flags - 1)) == 0;
}


}	// namespace Fl


#endif
