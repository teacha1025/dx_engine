#pragma once
#include <coroutine>
#include <memory>

#include "def.h"

namespace dx_engine {
	namespace coro_detail
	{
		struct _yield
		{
			constexpr _yield() :
				count(1)
			{}
			constexpr _yield(std::uint32_t _count) :
				count(_count)
			{}
			std::uint32_t count;
		};
		/// <summary>
		/// タスク用インターフェース
		/// </summary>
		struct ITask
		{
			virtual ~ITask() = default;
			virtual bool next() const = 0;
		};
	}
	/// <summary>
	/// タスク
	/// </summary>
	template <class T = void>
	struct coroutine : coro_detail::ITask
	{
		struct promise_type; // coroutine_traitsを特殊化してないのでスネイクケース
		using Handle = std::coroutine_handle<promise_type>;
		struct PromiseValue
		{
			void return_value(const T& value)
			{
				this->value = value;
			}
			const T& getValue() const
			{
				return value;
			}
			T value;
		};
		struct promise_type : PromiseValue
		{
			/*static coroutine get_return_object_on_allocation_failure()
			{
				return coroutine{ nullptr };
			}*/
			auto get_return_object() { return coroutine{ coroutine::Handle::from_promise(*this) }; }
			auto initial_suspend() { return std::suspend_always{}; }
			auto final_suspend() noexcept { return std::suspend_always{}; }
			void unhandled_exception() { std::terminate(); }
			auto yield_value(const coro_detail::_yield& _yield)
			{
				struct Awaiter
				{
					bool await_ready() const noexcept
					{
						return ready;
					}
					void await_suspend(std::coroutine_handle<>) {}
					void await_resume() {}
					bool ready = false;
				};
				if (_yield.count == 0) {
					return Awaiter{ true };
				}
				--(this->yield = _yield).count;
				return Awaiter{ false };
			}
			template<class U>
			auto yield_value(coroutine<U> other)
			{
				auto nextTask = std::make_shared<coroutine<U>>(std::move(other));
				auto ready = !nextTask->next();
				next = nextTask;
				struct Awaiter
				{
					bool ready = false;
					std::shared_ptr<coroutine<U>> pTask;
					bool await_ready() const { return ready; }
					decltype(auto) await_resume()
					{
						return pTask->get();
					}
					void await_suspend(std::coroutine_handle<>)
					{}
				};
				return Awaiter{ ready, nextTask };
			}
			coro_detail::_yield yield{ 0 };
			std::shared_ptr<coro_detail::ITask> next;
		};
		//coroutine() = default;
		coroutine(Handle h) :
			coro(h)
		{}
		coroutine(coroutine const&) = delete;
		coroutine(coroutine&& rhs) noexcept
			: coro(std::move(rhs.coro))
		{
			rhs.coro = nullptr;
		}
		~coroutine()
		{
			if (coro) {
				coro.destroy();
			}
		}
		/// <summary>
		/// 再開
		/// </summary>
		/// <returns></returns>
		bool next() const override
		{
			if (!coro) {
				return false;
			}
			if (coro.done()) {
				return false;
			}
			// Yield
			{
				auto& yield = coro.promise().yield;
				if (yield.count > 0 && yield.count-- > 0) {
					// カウンタが残ってるなら
					return true;
				}
			}
			// 割り込み別タスク
			{
				auto& next = coro.promise().next;
				if (next) {
					if (!next->next()) {
						next = nullptr;
					}
					else {
						return true;
					}
				}
			}
			coro.resume();
			return !coro.done();
		}
		/// <summary>
		/// 完了したか
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] bool isDone()const
		{
			if (!coro) {
				return false;
			}
			return coro.done();
		}
		/// <summary>
		/// 取得
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] decltype(auto) get() const
		{
			return coro.promise().getValue();
		}
	private:
		Handle coro;
	};
	// void特殊化
	template<>
	struct coroutine<void>::PromiseValue
	{
		void return_void() {}
		void getValue() const
		{}
	};
	template<class T, class U>
	[[nodiscard]] coroutine<void> operator & (coroutine<T> a, coroutine<U> b)
	{
		while (true) {
			a.next();
			b.next();
			if (a.isDone() && b.isDone()) {
				co_return;
			}
			co_yield{};
		}
	}
	template<class T, class U>
	[[nodiscard]] coroutine<void> operator | (coroutine<T> a, coroutine<U> b)
	{
		while (true) {
			a.next();
			b.next();
			if (a.isDone() || b.isDone()) {
				co_return;
			}
			co_yield{};
		}
	}
	template<class T, class U>
	[[nodiscard]] coroutine<U> operator + (coroutine<T> a, coroutine<U> b)
	{
		while (a.next()) {
			co_yield{};
		}
		while (b.next()) {
			co_yield{};
		}
		co_return b.get();
	}

	using task = coroutine<void>;

	namespace coroutines {
		[[nodiscard]] task wait(uint frame);
	}
}
