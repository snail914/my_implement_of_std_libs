#pragma once
#include <utility>
#include <memory>

namespace my {
namespace impl {
template <typename R, typename... Args>
class CallableBase {
  public:
    virtual R invoke(Args...) = 0;

    virtual ~CallableBase() = default;

    CallableBase() = default;

    CallableBase(const CallableBase&) = delete;
    CallableBase(CallableBase&&) = delete;

    CallableBase& operator=(const CallableBase&) = delete;
    CallableBase& operator=(CallableBase&&) = delete;
};

template <typename F, typename R, typename... Args>
class Callable : public CallableBase<R, Args...> {
  public:
    explicit Callable(F&& func)
    : d_func(std::forward<F>(func))
    {}

    R invoke(Args... args) override {
        return d_func(std::forward<Args>(args)...);
    }

    ~Callable() = default;

    Callable(const Callable&) = delete;
    Callable(Callable&&) = delete;

    Callable& operator=(const Callable&) = delete;
    Callable& operator=(Callable&&) = delete;
  private:
    F d_func;
};
} // close namespace impl


template <typename>
class function; // non implementation

template <typename R, typename... Args>
class function<R(Args...)> {
  public:
    function() = default;

    template <typename F>
    explicit function(F&& f)
    : d_callable_p {std::make_unique<impl::Callable<F, R, Args...>>(
                                                        std::forward<F>(f))}
    {}

    template <typename F>
    function& operator=(F&& f) {
        d_callable_p = std::make_unique<impl::Callable<F, R, Args...>>(
                                                        std::forward<F>(f));
        return *this;
    }

    R operator()(Args... args) {
        return d_callable_p->invoke(std::forward<Args>(args)...);
    }

    ~function() = default;
    function(function&&) = delete;
    function(const function&) = delete;

    function& operator=(const function&) = delete;
    function& operator=(function&&) = delete;
  private:
    std::unique_ptr<impl::CallableBase<R, Args...>> d_callable_p;
};

}
