// *********************************************************************************************************************
// Description:		ParameterPack type traits
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, BIM, SzoBe
//
// *********************************************************************************************************************

#ifndef PARAMETERPACKTRAITS_HPP
#define PARAMETERPACKTRAITS_HPP

#pragma once


#include "TypeTraits.hpp"


namespace GS {


// === ParameterPackSize ===============================================================================================

template <class... Ts>
constexpr USize	ParameterPackSize = sizeof... (Ts);


// === ParameterPackType ===============================================================================================

namespace Imp {

template <UIndex I, class... Ts>
struct ParameterPackTypeHelper;

template <UIndex I, class T, class... Ts>
struct ParameterPackTypeHelper<I, T, Ts...>		{ using Type = typename ParameterPackTypeHelper<I - 1, Ts...>::Type; };

template <class T, class... Ts>
struct ParameterPackTypeHelper<0, T, Ts...>		{ using Type = T; };

}


template <UIndex I, class... Ts>
using ParameterPackType = typename Imp::ParameterPackTypeHelper<I, Ts...>::Type;


// === ParameterPack ===================================================================================================


template <typename... Args>
struct ParameterPack {
	template <UIndex index>
	using Parameter = ParameterPackType<index, Args...>;

	static constexpr USize Length = ParameterPackSize<Args...>;
};


// === SelectNthValue ==================================================================================================

namespace Imp {

template <UIndex Index>
struct LastValueHelper {
	template <class T, class... Tn>
	static ParameterPackType<Index, T, Tn...>		Get (const T&, const Tn&... tn)
	{
		return LastValueHelper<Index - 1>::Get (tn...);
	}
};


template <>
struct LastValueHelper<0> {
	template <class T, class... Tn>
	static const T&		Get (const T& t, const Tn&...)
	{
		return t;
	}
};

} // namespace Imp


template <UIndex Index, class... Ts>
ParameterPackType<Index, Ts...>		SelectNthValue (const Ts&... ts)
{
	return Imp::LastValueHelper<Index>::Get (ts...);
}


// === DecomposeFunction ===============================================================================================

namespace Imp {

template <class X>
struct DecomposeFunctionHelper {
	static_assert (AlwaysFalse<X>, "'X' is not a function type.");
};


template <class R, class... P>
struct DecomposeFunctionHelper<R (P...)> {
	using Arguments = ParameterPack<P...>;
	using Result = R;
};


template <class T, class K = RemovePointer<T>, class L = RemoveReference<K>>
using DecomposeFunction = DecomposeFunctionHelper<L>;

} // namespace Imp


template <class T>
using DecomposeFunction = Imp::DecomposeFunction<T>;


// === DecomposeMethod =================================================================================================


template <class X>
struct DecomposeMethod {
	static_assert (AlwaysFalse<X>, "'X' is not a method pointer type.");
};


template <class R, class C, class... P>
struct DecomposeMethod<R (C::*) (P...)> {
	using Class = C;
	using Arguments = ParameterPack<P...>;
	using Result = R;
	static constexpr bool IsConst = false;
};


template <class R, class C, class... P>
struct DecomposeMethod<R (C::*) (P...) const> {
	using Class = C;
	using Arguments = ParameterPack<P...>;
	using Result = R;
	static constexpr bool IsConst = true;
};


}	// namespace GS


#endif
