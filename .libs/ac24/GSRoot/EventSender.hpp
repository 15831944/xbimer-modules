
// *****************************************************************************
//
//                              Class EventSender
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined EVENTSENDER_HPP
#define EVENTSENDER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"

#include "Array.hpp"
#include "EventReceiver.hpp"
#include "TypeTraits.hpp"
#include "ParameterPackTraits.hpp"
#include <functional>


// ============================= Class EventSender =============================

namespace GS {


class GSROOT_DLL_EXPORT EventSenderBase {
protected:


	friend class EventReceiver;		// to access ReceiverDeleted

	virtual ~EventSenderBase ();

	virtual void	ReceiverDeleted (EventReceiver& receiver) = 0;
public:
	enum class RecieverType {
		Function,
		Method,
	};
};


namespace ImpEventSender {

template <EventSenderBase::RecieverType>
struct Attacher;

} // namespace ImpEventSender

template <class... Args>
class EventSenderBaseImp : public EventSenderBase {
public:
	using CallbackFunction = std::function<void (const Args&...)>;

private:
	struct Receiver {
		EventReceiver*	 receiver;
		CallbackFunction callbackFunction;

		Receiver () : receiver (nullptr) {}
		Receiver (EventReceiver* receiver, const CallbackFunction& callbackFunction) : receiver (receiver), callbackFunction (callbackFunction) {}
	};

	template <RecieverType>
	friend struct ImpEventSender::Attacher;

	template <class T>
	static constexpr RecieverType Classify = GS::IsMethodPointer<T> ? RecieverType::Method : RecieverType::Function;

	Array<Receiver>	receivers;			// receivers of the sender
	bool			sending;			// true during sending
	bool			reverseSendOrder;	// true if receivers are notified in the reverse order during sending, it is alternated after each send

	virtual void	ReceiverDeleted (EventReceiver& receiver) override;

	void			AttachCallbackFunction (EventReceiver& receiver, const CallbackFunction& callbackFunction);

	using InvokerFunction = std::function<void (const CallbackFunction&)>;
	void CallSend (const InvokerFunction& invoker);

protected:
	template <class... Args2>
	void Send (const Args2&... args2);

public:
	EventSenderBaseImp ();
	EventSenderBaseImp (const EventSenderBaseImp& source) = delete;
	EventSenderBaseImp&	operator=	(const EventSenderBaseImp& source) = delete;
	~EventSenderBaseImp ();

 	template <class EventReceiverType, class Callable>
 	void	Attach (EventReceiverType& receiver, const Callable& callable);

	template <class Target, class MethodPointer>
	void	Attach (EventReceiver& receiver, Target& object, const MethodPointer& method);

	void	Detach (EventReceiver& receiver);

	bool	IsAttached (const EventReceiver& receiver) const;
};


namespace ImpEventSender {


template <>
struct Attacher<EventSenderBase::RecieverType::Function> {

	template <class... Args>
	static void	Attach (EventSenderBaseImp<Args...>& eventSender, EventReceiver& receiver, EventReceiver&, const typename EventSenderBaseImp<Args...>::CallbackFunction& function)
	{
		eventSender.AttachCallbackFunction (receiver, function);
	}
};


template <>
struct Attacher<EventSenderBase::RecieverType::Method> {

	template <class TargetReciever, class Target, class Result, class... Args>
	static void	Attach (EventSenderBaseImp<Args...>& eventSender, EventReceiver& receiver, TargetReciever& object, Result (Target::*method) (Args...))
	{
		static_assert (IsCompatible<TargetReciever, Target>, "object must be compatible with method's class");

		eventSender.Attach (receiver, [&, method] (Args... args) { (object.*method) (args...); });
	}

	template <class TargetClass, class TargetBaseClass, class Result, class... Args>
	static void	Attach (EventSenderBaseImp<Args...>& eventSender, EventReceiver& receiver, TargetClass& object, Result (TargetBaseClass::*method) (Args...) const)
	{
		static_assert (IsCompatible<TargetClass, TargetBaseClass>, "object must be compatible with method's class");

		eventSender.Attach (receiver, [&, method] (Args... args) { (object.*method) (args...); });
	}
};


} // namespace ImpEventSender








template <class T>
struct SendCaller;

template <class... Args>
class EventSender : public EventSenderBaseImp<Args...> {
public:
	using EventSenderBaseImp<Args...>::Send;
};


template <class Caller, class... Args>
class EventSender<SendCaller<Caller>, Args...> : public EventSenderBaseImp<Args...> {
	friend Caller;
};









// ================ EventSenderBaseImp ================ 

template <class... Args>
EventSenderBaseImp<Args...>::EventSenderBaseImp () :
	sending (false),
	reverseSendOrder (false)
{
}


template <class... Args>
EventSenderBaseImp<Args...>::~EventSenderBaseImp ()
{
	for (UInt32 i = 0; i < receivers.GetSize (); i++)
		receivers[i].receiver->eventSenders.DeleteFirst (this);
}


template <class... Args>
void	EventSenderBaseImp<Args...>::AttachCallbackFunction (EventReceiver& receiver, const CallbackFunction& callbackFunction)
{
	receivers.Push (Receiver (&receiver, callbackFunction));
	receiver.eventSenders.Push (this);
}


template <class... Args>
template <class IReceiver, class ArgumentType>
void	EventSenderBaseImp<Args...>::Attach (IReceiver& receiver, const ArgumentType& callbackFunction)
{
	using namespace ImpEventSender;

	DBASSERT (&receiver != nullptr);
	DBASSERT (&callbackFunction != nullptr);
	DBASSERT (!receivers.Contains ([&] (const Receiver& r) { return r.receiver == &receiver; }));
	DBASSERT (!sending);	// it needs further development to enable Attach during event sending (new receivers should be added only after event sending has been finished)

	static_assert (IsCompatible<IReceiver, EventReceiver>, "object must be compatible with EventReceiver");
	static_assert (!GS::IsConst<IReceiver>, "Receiver must be non-const!");

	EventReceiver& receiverObject = static_cast<EventReceiver&> (receiver);
	Attacher<Classify<Decay<ArgumentType>>>::Attach (*this, receiverObject, receiver, callbackFunction);
}


template <class... Args>
template <class Target, class MethodPointer>
void	EventSenderBaseImp<Args...>::Attach (EventReceiver& receiver, Target& object, const MethodPointer& methodPointer)
{
	using namespace ImpEventSender;

	DBASSERT (&receiver != nullptr);
	DBASSERT (&methodPointer != nullptr);
	DBASSERT (!receivers.Contains ([&] (const Receiver& r) { return r.receiver == &receiver; }));
	DBASSERT (!sending);	// it needs further development to enable Attach during event sending (new receivers should be added only after event sending has been finished)

	static_assert (IsMethodPointer<MethodPointer>, "methodPointer must be a MethodPointer");
	constexpr bool isConstMethod = DecomposeMethod<MethodPointer>::IsConst;
	static_assert (isConstMethod || !IsConst<Target>, "If the methodPointer is non-const, the targetObject must be a non-const");

	Attacher<RecieverType::Method>::Attach (*this, receiver, object, methodPointer);
}


template <class... Args>
void	EventSenderBaseImp<Args...>::Detach (EventReceiver& receiver)
{
	DBASSERT (&receiver != nullptr);
	DBASSERT (!sending);	// it needs further development to enable Detach during event sending (existing receivers should be deleted only after event sending has been finished)

	UInt32 receiverIndex = receivers.FindFirst ([&] (const Receiver& r) { return r.receiver == &receiver; });

	if (receiverIndex != MaxUIndex) {
		receivers.Delete (receiverIndex);
		receiver.eventSenders.DeleteFirst (this);
	}
}


template <class... Args>
bool	EventSenderBaseImp<Args...>::IsAttached (const EventReceiver& receiver) const
{
	return receivers.Contains ([&] (const Receiver& r) { return r.receiver == &receiver; });
}


template <class... Args>
void	EventSenderBaseImp<Args...>::ReceiverDeleted (EventReceiver& receiver)
{
	DBASSERT (!sending);	// it is not allowed to delete receiver during event sending

	UInt32 receiverIndex = receivers.FindFirst ([&] (const Receiver& r) { return r.receiver == &receiver; });
	receivers.Delete (receiverIndex);
}


template <class... Args>
template <class... Args2>
void	EventSenderBaseImp<Args...>::Send (const Args2&... args2)
{
	CallSend ([&] (const CallbackFunction& function) {
		function (args2...);
	});
}


template <class... Args>
void	EventSenderBaseImp<Args...>::CallSend (const InvokerFunction& invoker)
{
	DBASSERT (&invoker != nullptr);

	sending = true;

	if (reverseSendOrder) {
		for (UInt32 i = receivers.GetSize (); i > 0; i--)
			invoker (receivers[i - 1].callbackFunction);
	} else {
		for (UInt32 i = 0; i < receivers.GetSize (); i++)
			invoker (receivers[i].callbackFunction);
	}

	reverseSendOrder = !reverseSendOrder;

	sending = false;
}


} // namespace GS 

#endif
