
// *****************************************************************************
//
//                                  Class UnorderedList
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
//
//
// *****************************************************************************


#if !defined UNORDEREDLIST_HPP
#define UNORDEREDLIST_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Array.hpp"

// ================================ Class UnorderedList ================================

namespace GS {

template <class Type>
class UnorderedList;


template <class Type>
bool operator== (const Array<Type>& array, const UnorderedList<Type>& unorderedList);

template <class Type>
bool operator!= (const Array<Type>& array, const UnorderedList<Type>& unorderedList);

template <class Type>
bool operator== (const UnorderedList<Type>& unorderedList, const Array<Type>& array);

template <class Type>
bool operator!= (const UnorderedList<Type>& unorderedList, const Array<Type>& array);


template <class Type>
class UnorderedList {
private:
	Array<Type> array;

public:
	UnorderedList (std::initializer_list<Type> items);

	static bool IsEqual (const Array<Type>& array1, const Array<Type>& array2);

	// ================================ External Operators =============================
	
	friend bool operator==<Type> (const Array<Type>& array, const UnorderedList& unorderedList);

	friend bool operator!=<Type> (const Array<Type>& array, const UnorderedList& unorderedList);

	friend bool operator==<Type> (const UnorderedList& unorderedList, const Array<Type>& array);

	friend bool operator!=<Type> (const UnorderedList& unorderedList, const Array<Type>& array);
};


// ================================ Global Function ================================

template <class Type>
UnorderedList<Type> Unordered (std::initializer_list<Type> items);


// === Implementation ===================================================================================================

template <class Type>
UnorderedList<Type>::UnorderedList (std::initializer_list<Type> items) :
	array (items)
{
}


template <class Type>
bool UnorderedList<Type>::IsEqual (const Array<Type>& array1, const Array<Type>& array2)
{
	if (array1.GetSize () != array2.GetSize ())
		return false;

	for (const Type& item : array1) {
		if (array1.Count (item) != array2.Count (item))
			return false;
	}

	return true;
}


template <class Type>
bool operator== (const Array<Type>& array, const UnorderedList<Type>& unorderedList)
{
	return UnorderedList<Type>::IsEqual (array, unorderedList.array);
}


template <class Type>
bool operator!= (const Array<Type>& array, const UnorderedList<Type>& unorderedList)
{
	return !UnorderedList<Type>::IsEqual (array, unorderedList.array);
}


template <class Type>
bool operator== (const UnorderedList<Type>& unorderedList, const Array<Type>& array)
{
	return UnorderedList<Type>::IsEqual (array, unorderedList.array);
}


template <class Type>
bool operator!= (const UnorderedList<Type>& unorderedList, const Array<Type>& array)
{
	return !UnorderedList<Type>::IsEqual (array, unorderedList.array);
}


template <class Type>
UnorderedList<Type> Unordered (std::initializer_list<Type> items)
{
	return UnorderedList<Type> (items);
}


}	// namespace GS
// ________________________________ Class Array ________________________________



#endif
