// *********************************************************************************************************************
//
// Description:		Utilities for the hash based containers and algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef HASHCOMMON_HPP
#define HASHCOMMON_HPP

#pragma once


#include "Definitions.hpp"
#include "TypeTraits.hpp"
#include "Container.hpp"
#include "AssociativeContainer.hpp"


// =====================================================================================================================

namespace GS {

// === HasInternalGenerateHashValue ============================================================================================

namespace Imp {

template <class Type>
constexpr bool	HasInternalGenerateHashValueMethod (decltype (ULong { std::declval<const Type> ().GenerateHashValue () })*) { return true; }

template <class Type>
constexpr bool	HasInternalGenerateHashValueMethod (...) { return false; }

template <class Type>
constexpr bool	HasInternalGenerateHashValue = Imp::HasInternalGenerateHashValueMethod<Type> (nullptr);

} // namespace Imp


template <class Type>
using HasGenerateHashValueMethod = EnableIf<Imp::HasInternalGenerateHashValue<Type>, bool>;

// =====================================================================================================================

GSROOT_DLL_EXPORT USize		GetNextHashCapacity     (USize oldCapacity);
GSROOT_DLL_EXPORT USize		GetPreviousHashCapacity (USize oldCapacity);

	// Predefined hash value generator functions

inline ULong	GenerateHashValue (Int8   value)		{ return value; }
inline ULong	GenerateHashValue (UInt8  value)		{ return value; }
inline ULong	GenerateHashValue (Int16  value)		{ return value; }
inline ULong	GenerateHashValue (UInt16 value)		{ return value; }
inline ULong	GenerateHashValue (Int32  value)		{ return value; }
inline ULong	GenerateHashValue (UInt32 value)		{ return value; }
inline ULong	GenerateHashValue (Int64  value)		{ return static_cast<ULong> (((UInt64 (value) >> 32) & 0xFFFFFFFFUL) + (UInt64 (value) & 0xFFFFFFFFUL)); }
inline ULong	GenerateHashValue (UInt64 value)		{ return static_cast<ULong> (((value >> 32) & 0xFFFFFFFFUL) + (value & 0xFFFFFFFFUL)); }

inline ULong	GenerateHashValue (float value)
{
	if (value == 0)    // 0 has two different forms: -0 and +0
		value = 0;
	return GenerateHashValue (reinterpret_cast<UInt32&> (value));
}


inline ULong	GenerateHashValue (double value)
{
	if (value == 0)    // 0 has two different forms: -0 and +0
		value = 0;
	return GenerateHashValue (reinterpret_cast<UInt64&> (value));
}


template <class Enum, EnumType<Enum> = true>
ULong	GenerateHashValue (Enum value)
{
	return GenerateHashValue (static_cast<UnderlyingType<Enum>> (value));
}


template <class T>
ULong	GenerateHashValue (const T* p)
{
	return GenerateHashValue (UIntPtr (p));
}


template <class Type, HasGenerateHashValueMethod<Type> = true>
ULong	GenerateHashValue (const Type& value)
{
	return value.GenerateHashValue ();
}


template <class T1, class T2, class... Ts>
ULong	GenerateHashValue (const T1& t1, const T2& t2, const Ts&... ts)
{
	return GenerateHashValue (t1) + 65599 * GenerateHashValue (t2, ts...);
}

GSROOT_DLL_EXPORT ULong		GenerateBinaryHashValue (const unsigned char* data, USize dataSize);


template <class T>
ULong	GenerateBinaryHashValue (const T& object)
{
	return GenerateBinaryHashValue (reinterpret_cast<const unsigned char*> (&object), sizeof (object));
}


GSROOT_DLL_EXPORT ULong		GenerateCStringHashValue (const char* cStr);

// === Hashable =========================================================================================

namespace Imp {

struct TestGenerateHashValueExternalFunction {
	template <class T>
	static std::true_type	Test (decltype (ULong {GenerateHashValue (std::declval<T> ())})*);

	template <class T>
	static std::false_type	Test (...);
};

} // namespace Imp

template <class T>
constexpr bool	HasGenerateHashValue = decltype (Imp::TestGenerateHashValueExternalFunction::Test<T> (nullptr))::value;


template <class Type>
inline ULong CallGenerateHashValue (const Type& arg)
{
	return GenerateHashValue (arg);
}


template <class Type>
class HashableContainer : public Container<Type> {
public:
	HashableContainer ()
	{
		static_assert (GS::HasGenerateHashValue<Type>, "Type doesn't have GenerateHashValue member or non-member function");
	}
};


template <class Key, class Value>
class HashableAssociativeContainer : public AssociativeContainer<Key, Value> {
public:
	HashableAssociativeContainer ()
	{
		static_assert (GS::HasGenerateHashValue<Key>, "Key doesn't have GenerateHashValue member or non-member function");
	}
};

}	// namespace GS


#endif
