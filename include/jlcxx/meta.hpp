#ifndef JLCXX_META_HPP
#define JLCXX_META_HPP

#include <type_traits>
#include <utility>

namespace jlcxx
{
namespace mpl
{
template <bool B>
using bool_constant = std::integral_constant<bool, B>;

struct identity
{
  template <class T>
  T&& operator()(T&& x) const
  {
    return std::forward<T>(x);
  }
};

template <class TF, class FF>
decltype(auto) static_if(std::true_type, const TF& tf, const FF&)
{
    return tf(identity());
}

template <class TF, class FF>
decltype(auto) static_if(std::false_type, const TF&, const FF& ff)
{
    return ff(identity());
}

template <bool cond, class TF, class FF>
decltype(auto) static_if(const TF& tf, const FF& ff)
{
    return static_if(std::integral_constant<bool, cond>(), tf, ff);
}

}
}

#endif
