#ifndef SK_FUNCTION_H__
#define SK_FUNCTION_H__

#include <memory>
#include <type_traits>

namespace sk {

template<typename >
class Function;

template<class Out, class ... In>
class Function<Out(In...)> {
public:
	Function() = default;
	Function(std::nullptr_t ) {}

	template<class CallableType>
	Function(CallableType&& callable)
		: m_call(std::make_unique <
		         CallableTypeWrapper < std::remove_reference_t<CallableType> >> (
		             std::forward < CallableType && > (callable))
		        )
	{}

	Out operator()(In...in) const {
		if (m_call) {
			return m_call->call(in...);
		}
		return Out();
	}

	explicit operator bool() const { return !!m_call;}

	template<typename OtherCallableType>
	Function& operator=(OtherCallableType&& callable)
	{
		m_call = std::make_unique <
		         CallableTypeWrapper< std::remove_reference_t<OtherCallableType> >> (
		             std::forward < OtherCallableType && > (callable) );
		return *this;
	}

	Function& operator=(std::nullptr_t)
	{
		m_call = nullptr;
		return *this;
	}

private:
	class CallableBase {
	public:
		virtual ~CallableBase() {}

		virtual Out call(In...) = 0;
	};

	template<class CallableType>
	class CallableTypeWrapper : public CallableBase {
	public:
		explicit CallableTypeWrapper(CallableType&& callable)
			: m_callable(std::forward < CallableType && > (callable))
		{}

		CallableTypeWrapper(const CallableTypeWrapper&) = delete;
		CallableTypeWrapper& operator=(const CallableTypeWrapper&) = delete;

		virtual Out call(In ... in)  {
			return m_callable(in...);
		}
	private:
		CallableType m_callable;
	};

	std::unique_ptr<CallableBase> m_call;

};


// template<typename> class Function;

// template <typename Out, typename... In>
// class Function<Out(In...)> {
// public:
// 	Function() = default;
// 	Function(std::nullptr_t) { }

// 	template < typename CallableType, class =
// 	           typename std::enable_if < std::is_rvalue_reference < CallableType && >::value >::type >
// 	Function(CallableType && callable)
// 		: m_callableWrapper(std::make_unique<CallableWrapper<CallableType>>(std::move(callable)))
// 	{
// 	}

// 	Out operator()(In... in) const
// 	{
// 		if (m_callableWrapper)
// 			return m_callableWrapper->call(std::forward<In>(in)...);
// 		return Out();
// 	}

// 	explicit operator bool() const { return !!m_callableWrapper; }

// 	template < typename CallableType, class = typename std::enable_if < std::is_rvalue_reference < CallableType && >::value >::type >
// 	Function & operator=(CallableType && callable)
// 	{
// 		m_callableWrapper = std::make_unique<CallableWrapper<CallableType>>(std::move(callable));
// 		return *this;
// 	}

// 	Function& operator=(std::nullptr_t)
// 	{
// 		m_callableWrapper = nullptr;
// 		return *this;
// 	}

// private:
// 	class CallableWrapperBase {
// 		/*WTF_MAKE_FAST_ALLOCATED*/;
// 	public:
// 		virtual ~CallableWrapperBase() { }

// 		virtual Out call(In...) = 0;
// 	};

// 	template<typename CallableType>
// 	class CallableWrapper : public CallableWrapperBase {
// 	public:
// 		explicit CallableWrapper(CallableType&& callable)
// 			: m_callable(std::move(callable))
// 		{
// 		}

// 		CallableWrapper(const CallableWrapper&) = delete;
// 		CallableWrapper& operator=(const CallableWrapper&) = delete;

// 		Out call(In... in) final { return m_callable(std::forward<In>(in)...); }

// 	private:
// 		CallableType m_callable;
// 	};

// 	std::unique_ptr<CallableWrapperBase> m_callableWrapper;
// };


} // end sk

#endif


