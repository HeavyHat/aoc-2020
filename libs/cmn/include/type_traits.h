#ifndef INCLUDED_HH_AOC_TYPE_TRAITS_H
#define INCLUDED_HH_AOC_TYPE_TRAITS_H

#include <iterator>
#include <type_traits>

namespace hh::aoc
{

template <typename T, typename = void> struct is_iterator : std::false_type
{
};

template <typename T>
struct is_iterator<T, std::enable_if_t<!std::is_void_v<typename std::iterator_traits<T>::value_type>>> : std::true_type
{
};

template <typename T, typename CATEGORY_TAG, typename = void> struct is_iterator_category : std::false_type

{
};

template <typename T, typename CATEGORY_TAG>
struct is_iterator_category<T, CATEGORY_TAG,
                            std::enable_if_t<std::is_same_v<typename std::iterator_traits<T>::iterator_category, CATEGORY_TAG>>>
    : std::true_type
{
};

} // namespace hh::aoc

#endif
