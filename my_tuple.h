#include <tuple>
#include <utility>

namespace my {
namespace impl {

template <unsigned Idx, typename T, typename... Types>
class TupleImpl : public TupleImpl<Idx + 1, Types...> {
  public:
    constexpr TupleImpl(T&& val, Types&&... args)
    : TupleImpl<Idx+1, Types...>(std::forward<Types>(args)...)
    , d_item {std::forward<T>(val) }
    {}

    // This is important, otherwise, function overloads won't work
    using TupleImpl<Idx + 1, Types...>::get;

    constexpr const T& get(std::integral_constant<unsigned, Idx>) const {
        return d_item;
    }

  private:
    T d_item;
};

template <unsigned Idx, typename T>
class TupleImpl<Idx, T> {
  public:
    static constexpr unsigned size() noexcept {
        return Idx + 1;
    }

    constexpr TupleImpl(T&& val)
    : d_item {std::forward<T>(val) }
    {}

    constexpr const T& get(std::integral_constant<unsigned, Idx>) const {
        return d_item;
    }

  private:
    T d_item;
};
}

template <typename... Types>
class tuple : public impl::TupleImpl<0, Types...> {
  public:
    constexpr tuple(Types&&... args)
    : impl::TupleImpl<0, Types...>(std::forward<Types>(args)...)
    {
    }
};

template <unsigned Idx, typename... Types>
constexpr const auto& get(const tuple<Types...>& tup) {
    return tup.get(std::integral_constant<unsigned, Idx>());
}
}
