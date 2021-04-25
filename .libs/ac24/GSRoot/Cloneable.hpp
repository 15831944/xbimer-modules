
// *****************************************************************************
//
//                                Class Cloneable
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined CLONEABLE_HPP
#define CLONEABLE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "Owner.hpp"

// ============================== Class Cloneable ==============================

namespace GS {

template <typename Type>
struct DefaultCloneOperations {
	static Type*	Clone  (const Type& data) { return data.Clone (); }
	static void		Delete (Type* data)		  { delete data; }
};


template <typename Type, template <typename> class CloneOperations = DefaultCloneOperations>
class Cloneable {
private:
	Type* value = nullptr;

	static_assert (IsDecayed<Type>, "'Type' should be decayed.");

public:
	Cloneable () = default;
	explicit Cloneable (const Type& value);
	explicit Cloneable (Owner<Type> value);

	Cloneable (const Cloneable& source);
	Cloneable (Cloneable&& source);
   ~Cloneable ();

	Cloneable&	operator= (const Cloneable& source);
	Cloneable&  operator= (Cloneable&& source);
	Cloneable&  operator= (const Type& source);
	Cloneable&  operator= (Owner<Type> source);
	Cloneable&  operator= (std::nullptr_t);

	Type&		operator* ();
	const Type&	operator* ()	const;
	Type*		operator-> ();
	const Type*	operator-> ()	const;
	Type*		Get ();
	const Type*	Get ()			const;

	Type*		Release ();

	bool		operator== (std::nullptr_t) const;
	bool		operator!= (std::nullptr_t) const;
};

}	// namespace GS


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>::Cloneable (const Type& value) :
	value (CloneOperations<Type>::Clone (value))
{
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>::Cloneable (Owner<Type> value) :
	value (value.Release ())
{
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>::Cloneable (const Cloneable& source) :
	value (source.value != nullptr ? CloneOperations<Type>::Clone (*source.value) : nullptr)
{
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>::Cloneable (Cloneable&& source) :
	value (source.value)
{
	source.value = nullptr;
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>::~Cloneable ()
{
	CloneOperations<Type>::Delete (value);
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>&	GS::Cloneable<Type, CloneOperations>::operator= (const Cloneable& source)
{
	if (&source != this) {
		CloneOperations<Type>::Delete (value);
		value = source.value != nullptr ? CloneOperations<Type>::Clone (*source.value) : nullptr;
	}

	return *this;
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>&  GS::Cloneable<Type, CloneOperations>::operator= (Cloneable&& source)
{
	CloneOperations<Type>::Delete (value);
	value = source.value;
	source.value = nullptr;

	return *this;
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>&  GS::Cloneable<Type, CloneOperations>::operator= (const Type& source)
{
	CloneOperations<Type>::Delete (value);
	value = CloneOperations<Type>::Clone (source);

	return *this;
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>&  GS::Cloneable<Type, CloneOperations>::operator= (Owner<Type> source)
{
	CloneOperations<Type>::Delete (value);
	value = source.Release ();

	return *this;
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>&  GS::Cloneable<Type, CloneOperations>::operator= (std::nullptr_t)
{
	CloneOperations<Type>::Delete (value);
	value = nullptr;

	return *this;
}


template <typename Type, template <typename> class CloneOperations>
Type&	GS::Cloneable<Type, CloneOperations>::operator* ()
{
	return *value;
}


template <typename Type, template <typename> class CloneOperations>
const Type&		GS::Cloneable<Type, CloneOperations>::operator* () const
{
	return *value;
}


template <typename Type, template <typename> class CloneOperations>
Type*	GS::Cloneable<Type, CloneOperations>::operator-> ()
{
	return value;
}


template <typename Type, template <typename> class CloneOperations>
const Type*		GS::Cloneable<Type, CloneOperations>::operator-> () const
{
	return value;
}


template <typename Type, template <typename> class CloneOperations>
Type*	GS::Cloneable<Type, CloneOperations>::Get ()
{
	return value;
}


template <typename Type, template <typename> class CloneOperations>
const Type*		GS::Cloneable<Type, CloneOperations>::Get () const
{
	return value;
}


template <typename Type, template <typename> class CloneOperations>
Type*	GS::Cloneable<Type, CloneOperations>::Release ()
{
	Type* result = value;
	value = nullptr;
	return result;
}


template <typename Type, template <typename> class CloneOperations>
inline bool		GS::Cloneable<Type, CloneOperations>::operator== (std::nullptr_t) const
{
	return value == nullptr;
}


template <typename Type, template <typename> class CloneOperations>
inline bool		GS::Cloneable<Type, CloneOperations>::operator!= (std::nullptr_t) const
{
	return value != nullptr;
}


#endif
