// *********************************************************************************************************************
// Description:		The class template GS::Variant represents a type-safe union. 
//					An instance of GS::Variant at any given time holds a value of one of its alternative types.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	KiP
//
// *********************************************************************************************************************

#ifndef _GSROOT_VARIANT_HPP_
#define _GSROOT_VARIANT_HPP_
#pragma once

// === Includes ========================================================================================================

#include "TypeTraits.hpp"
#include "GSDebug.hpp"

// =====================================================================================================================

namespace GS {

namespace VariantHelper {

template <size_t arg1, size_t ... others>
struct Max;

template <size_t arg>
struct Max<arg>
{
	static constexpr size_t value = arg;
};

template <size_t arg1, size_t arg2, size_t ... others>
struct Max<arg1, arg2, others...>
{
	static constexpr size_t value = arg1 >= arg2 ? Max<arg1, others...>::value : Max<arg2, others...>::value;
};




template <typename Type, typename... Types>
struct Contains;

template <typename Type, typename FirstType, typename... OtherTypes>
struct Contains<Type, FirstType, OtherTypes...>
{
	static constexpr bool value = GS::IsSame<Type, FirstType> ? true : Contains<Type, OtherTypes...>::value;
};

template <typename Type, typename OtherType>
struct Contains<Type, OtherType>
{
	static constexpr bool value = GS::IsSame<Type, OtherType>;
};




template <typename Type, typename... Types>
struct TypeToIndex;

template <typename Type, typename FirstType, typename... OtherTypes>
struct TypeToIndex<Type, FirstType, OtherTypes...>
{
	static constexpr UInt8 index = GS::IsSame<Type, FirstType> ? 0 : TypeToIndex<Type, OtherTypes...>::index + 1;
};

template <typename Type, typename LastType>
struct TypeToIndex<Type, LastType>
{
	static constexpr UInt8 index = GS::IsSame<Type, LastType> ? 0 : 1;
};




template <typename... Types>
struct FunctionTable;

template <typename Type, typename... OtherTypes>
struct FunctionTable<Type, OtherTypes...>
{
	static void Destroy (UInt8 typeIndex, void* data)
	{
		if (typeIndex == 0)
			reinterpret_cast<Type*> (data)->~Type ();
		else
			FunctionTable<OtherTypes...>::Destroy (typeIndex - 1, data);
	}

	static void CopyConstruct (UInt8 typeIndex, const void* source, void* target)
	{
		if (typeIndex == 0)
			new (target) Type (*reinterpret_cast<const Type*> (source));
		else
			FunctionTable<OtherTypes...>::CopyConstruct (typeIndex - 1, source, target);
	}

	static void MoveConstruct (UInt8 typeIndex, void* source, void* target)
	{
		if (typeIndex == 0) {
			new (target) Type (std::move (*reinterpret_cast<Type*> (source)));
		} else {
			FunctionTable<OtherTypes...>::MoveConstruct (typeIndex - 1, source, target);
		}
	}

	static void CopyAssign (UInt8 typeIndex, const void* source, void* target)
	{
		if (typeIndex == 0)
			*reinterpret_cast<Type*> (target) = *reinterpret_cast<const Type*> (source);
		else
			FunctionTable<OtherTypes...>::CopyAssign (typeIndex - 1, source, target);
	}

	static void MoveAssign (UInt8 typeIndex, void* source, void* target)
	{
		if (typeIndex == 0) {
			*reinterpret_cast<Type*> (target) = std::move (*reinterpret_cast<Type*> (source));
		} else {
			FunctionTable<OtherTypes...>::MoveAssign (typeIndex - 1, source, target);
		}
	}
};

template <> 
struct FunctionTable<>
{
	static void Destroy (UInt8 /*typeIndex*/, void* /*data*/) {}
	static void CopyConstruct (UInt8 /*typeIndex*/, const void* /*source*/, void* /*target*/) {}
	static void MoveConstruct (UInt8 /*typeIndex*/, void* /*source*/, void* /*target*/) {}
	static void CopyAssign (UInt8 /*typeIndex*/, const void* /*source*/, void* /*target*/) {}
	static void MoveAssign (UInt8 /*typeIndex*/, void* /*source*/, void* /*target*/) {}
};

}

template <typename... Types>
class Variant
{
private:
	static constexpr size_t DataSize = VariantHelper::Max<sizeof (Types)...>::value;
	static constexpr size_t DataAlign = VariantHelper::Max<alignof (Types)...>::value;

	alignas (DataAlign) char	buffer[DataSize];
	UInt8						typeIndex;


	using FunctionTable = VariantHelper::FunctionTable<Types...>;
	
	template <typename Type>
	using IsEnabledType = GS::EnableIf<VariantHelper::Contains<GS::Decay<Type>, Types...>::value && !GS::IsSame<GS::Decay<Type>, Variant<Types...>>>;

	template <typename Type>
	void ConstructFromValue (Type&& value);

	template <typename Type>
	void AssignSameType (Type&& value);

public:
	Variant (const Variant<Types...>& source);
	Variant (Variant<Types...>&& source);

	template <typename Type, typename = IsEnabledType<Type>>
	Variant (Type&& value);

	~Variant ();

	Variant<Types...>& operator= (const Variant<Types...>& source);
	Variant<Types...>& operator= (Variant<Types...>&& source);

	template <typename Type, typename = IsEnabledType<Type>>
	Variant<Types...>& operator= (Type&& source);

	template <typename Type>	bool			Is () const;
	template <typename Type>	Type&			Get () &;
	template <typename Type>	const Type&		Get () const&;
	template <typename Type>	Type&&			Get () &&;
};


template <typename... Types>
template <typename Type>
void Variant<Types...>::ConstructFromValue (Type&& value)
{
	typeIndex = VariantHelper::TypeToIndex<GS::Decay<Type>, Types...>::index;
	new (buffer) GS::Decay<Type> (std::forward<Type> (value));
}


template <typename... Types>
template <typename Type>
void Variant<Types...>::AssignSameType (Type&& value)
{
	// DBASSERT (typeIndex == VariantHelper::TypeToIndex<GS::Decay<Type>, Types...>::index);

	reinterpret_cast<GS::Decay<Type>&> (buffer) = std::forward<Type> (value);
}


template <typename... Types>
Variant<Types...>::Variant (const Variant<Types...>& source) :
	typeIndex (source.typeIndex)
{
	FunctionTable::CopyConstruct (source.typeIndex, &source.buffer, &buffer);
}


template <typename... Types>
Variant<Types...>::Variant (Variant<Types...>&& source) :
	typeIndex (source.typeIndex)
{
	FunctionTable::MoveConstruct (source.typeIndex, &source.buffer, &buffer);
}


template <typename... Types>
template <typename Type, typename /*= IsEnabledType<Type>*/>
Variant<Types...>::Variant (Type&& value)
{
	ConstructFromValue (std::forward<Type> (value));
}


template <typename... Types>
Variant<Types...>::~Variant ()
{
	FunctionTable::Destroy (typeIndex, &buffer);
}


template <typename... Types>
Variant<Types...>& Variant<Types...>::operator= (const Variant<Types...>& source)
{
	if (this != &source) {
		if (typeIndex != source.typeIndex) {
			FunctionTable::Destroy (typeIndex, &buffer);
			typeIndex = source.typeIndex;
			FunctionTable::CopyConstruct (typeIndex, &source.buffer, &buffer);
		} else {
			FunctionTable::CopyAssign (typeIndex, &source.buffer, &buffer);
		}
	}
	return *this;
}


template <typename... Types>
Variant<Types...>& Variant<Types...>::operator= (Variant<Types...>&& source)
{
	if (this != &source) {
		if (typeIndex != source.typeIndex) {
			FunctionTable::Destroy (typeIndex, &buffer);
			typeIndex = source.typeIndex;
			FunctionTable::MoveConstruct (typeIndex, &source.buffer, &buffer);
		} else {
			FunctionTable::MoveAssign (typeIndex, &source.buffer, &buffer);
		}
	}
	return *this;
}


template <typename... Types>
template <typename Type, typename /*= IsEnabledType<Type>*/>
Variant<Types...>& Variant<Types...>::operator= (Type&& source)
{
	const size_t sourceTypeIndex = VariantHelper::TypeToIndex<GS::Decay<Type>, Types...>::index;
	if (typeIndex != sourceTypeIndex) {
		FunctionTable::Destroy (typeIndex, &buffer);
		ConstructFromValue (std::forward<Type> (source));
	} else {
		AssignSameType (std::forward<Type> (source));
	}
	return *this;
}


template <typename... Types>
template <typename Type>
bool Variant<Types...>::Is () const
{
	static_assert (GS::IsDecayed<Type>, "'Type' should be decayed.");
	
	return (typeIndex == VariantHelper::TypeToIndex<GS::Decay<Type>, Types...>::index);
}


template <typename... Types>
template <typename Type>
Type& Variant<Types...>::Get () &
{
	static_assert (GS::IsDecayed<Type>, "'Type' should be decayed.");

	DBASSERT (Is<Type> ());

	return reinterpret_cast<Type&> (buffer);
}


template <typename... Types>
template <typename Type>
const Type& Variant<Types...>::Get () const&
{
	static_assert (GS::IsDecayed<Type>, "'Type' should be decayed.");
	
	DBASSERT (Is<Type> ());

	return reinterpret_cast<const Type&> (buffer);
}


template <typename... Types>
template <typename Type>
Type&& Variant<Types...>::Get () &&
{
	static_assert (GS::IsDecayed<Type>, "'Type' should be decayed.");
	
	DBASSERT (Is<Type> ());

	return std::move (reinterpret_cast<Type&> (buffer));
}

}

#endif
