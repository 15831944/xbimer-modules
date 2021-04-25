
// *****************************************************************************
//
//                                  Class ConditionalView
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
//
//
// *****************************************************************************



#if !defined CONDITIONALVIEW_HPP
#define CONDITIONALVIEW_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Optional.hpp"

// ================================ Class ConditionalView ================================

namespace GS {

namespace ImpConditionalView {

template <class Type, class Condition>
constexpr bool TestIsFunctor (decltype (bool { std::declval<Condition> () (std::declval<const Type&> ()) })*) { return true; }

template <class...>
constexpr bool TestIsFunctor (...) { return false; }

template <class Type, class Condition>
constexpr bool IsFunctor = TestIsFunctor<Type, Condition> (nullptr);


template <class Type>
constexpr bool TestTransformCondition (decltype (TransformCondition (std::declval<const Type&> ()))*) { return true; }

template <class...>
constexpr bool TestTransformCondition (...) { return false; }

template <class T>
constexpr bool HasTransformCondition = TestTransformCondition<T> (nullptr);


template <bool hasTransformCondition>
struct ConditionalViewCreator;

template <>
struct ConditionalViewCreator<true> {
	template <class Container, class Condition>
	static decltype (auto) Create (Container&& container, Condition&& condition);
};

template <>
struct ConditionalViewCreator<false> {
	template <class Container, class Condition>
	static decltype (auto) Create (Container&& container, Condition&& condition);
};

} // namespace ImpConditionalView


template <class Container, class Condition>
decltype (auto) CreateConditionalView (Container&& container, Condition&& condition);


template <class Container, class Condition>
class ConditionalView {
public:
	using Type = typename Container::ValueType;

private:
	using ContainerIterator = typename Container::ConstIterator;

	static constexpr bool IsCompatible = ImpConditionalView::IsFunctor<Type, Condition>;
	static_assert (IsCompatible, "'Condition' must have an operator() (const T&) where 'Container::ValueType' should be convertible to 'T'!");
	static_assert (IsDecayed<Container>, "'Container' must be decayed!");
	static_assert (IsDecayed<Condition>, "'Condition' must be decayed!");

	Condition					condition;
	Optional<Container>			container;
	ContainerIterator			beginIt;
	ContainerIterator			endIt;

	ConditionalView (const Container& container, const Condition& condition);
	ConditionalView (const Container& container, Condition&& condition);
	ConditionalView (Container&& container, const Condition& condition);
	ConditionalView (Container&& container, Condition&& condition);

	template <bool hasTransformCondition>
	friend struct ImpConditionalView::ConditionalViewCreator;

public:
	class Iterator;

	Iterator begin () const;
	Iterator end () const;

	class Iterator {
	private:
		ContainerIterator		iterator;
		const ConditionalView*	view;		// nullptr if it's an "end iterator"

	public:
		Iterator (const ConditionalView* view, ContainerIterator iterator);

		const Type&		operator*	() const;
		Iterator&		operator++	();
		bool			operator==	(const Iterator& rightOp) const;
		bool			operator!=	(const Iterator& rightOp) const;
	};
};

// ================================  ConditionalViewCreator<false>  =========================================


template <class Container, class Condition>
decltype (auto) ImpConditionalView::ConditionalViewCreator<false>::Create (Container&& container, Condition&& condition)
{
	return ConditionalView<Decay<Container>, Decay<Condition>> (std::forward<Container> (container), std::forward<Condition> (condition));
}

// ================================  ConditionalViewCreator<true>  ==========================================

template <class Container, class Condition>
decltype (auto) ImpConditionalView::ConditionalViewCreator<true>::Create (Container&& container, Condition&& condition)
{
	using TransformConditionType = decltype (TransformCondition (std::forward<Condition> (condition)));
	return ConditionalView<Decay<Container>, Decay<TransformConditionType>> (std::forward<Container> (container), TransformCondition (std::forward<Condition> (condition)));
}


// ================================  CreateConditionalView  =======================================

template <class Container, class Condition>
decltype (auto) CreateConditionalView (Container&& container, Condition&& condition)
{
	using namespace ImpConditionalView;
	constexpr bool hasTransformCondition = HasTransformCondition<Decay<Condition>>;
	return ConditionalViewCreator<hasTransformCondition>::Create (std::forward<Container> (container), std::forward<Condition> (condition));
}


// ================================  ConditionalView Class  =======================================


template <class Container, class Condition>
ConditionalView<Container, Condition>::ConditionalView (const Container& container, const Condition& condition) :
	condition (condition),
	beginIt (container.Begin ()),
	endIt (container.End ())
{
}


template <class Container, class Condition>
ConditionalView<Container, Condition>::ConditionalView (const Container& container, Condition&& condition) :
	condition (std::move (condition)),
	beginIt (container.Begin ()),
	endIt (container.End ())
{
}


template <class Container, class Condition>
ConditionalView<Container, Condition>::ConditionalView (Container&& container, const Condition& condition) :
	condition (condition),
	container (std::move (container)),
	beginIt (this->container->Begin ()),
	endIt (this->container->End ())
{
}


template <class Container, class Condition>
ConditionalView<Container, Condition>::ConditionalView (Container&& container, Condition&& condition) :
	condition (condition),
	container (std::move (container)),
	beginIt (this->container->Begin ()),
	endIt (this->container->End ())
{
}


template <class Container, class Condition>
typename ConditionalView<Container, Condition>::Iterator ConditionalView<Container, Condition>::begin () const
{
	return Iterator (this, beginIt);
}


template <class Container, class Condition>
typename ConditionalView<Container, Condition>::Iterator ConditionalView<Container, Condition>::end () const
{
	return Iterator (nullptr, endIt);
}

// ================================  ConditionalView::Iterator Class  =============================

template <class Container, class Condition>
ConditionalView<Container, Condition>::Iterator::Iterator (const ConditionalView* view, ContainerIterator iterator) :
	iterator (iterator),
	view (view)
{
	if (view == nullptr)
		return;							// "end iterator"

	if (view->endIt == iterator)		// If "begin iterator" equals with "end iterator" must return
		return;

	if (view->condition (*iterator))
		return;

	++(*this);
}


template <class Container, class Condition>
const typename ConditionalView<Container, Condition>::Type& ConditionalView<Container, Condition>::Iterator::operator* () const
{
	return *iterator;
}


template <class Container, class Condition>
typename ConditionalView<Container, Condition>::Iterator& ConditionalView<Container, Condition>::Iterator::operator++ ()
{
	DBASSERT (view != nullptr);
	DBASSERT (iterator != view->endIt);

	do {
		++iterator;
	} while (iterator != view->endIt && !view->condition (*iterator));

	return *this;
}


template <class Container, class Condition>
bool ConditionalView<Container, Condition>::Iterator::operator== (const Iterator& rightOp) const
{
	return iterator == rightOp.iterator;
}


template <class Container, class Condition>
bool ConditionalView<Container, Condition>::Iterator::operator!= (const Iterator& rightOp) const
{
	return iterator != rightOp.iterator;
}


} // namespace GS

#endif
