#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <unordered_map>
#include <range/v3/all.hpp>

template <typename T>
requires ranges::sized_range<T>
auto pair_with_iota(const T& objs) {
	const auto ints = ranges::views::iota(0, static_cast<int>(objs.size()));
	return ranges::views::zip(objs, ints);
} 

// TODO: Restrict T to be range of pairs
template <typename T>
requires ranges::range<T>
auto pair_swap(const T& pairs){
	return pairs | ranges::views::transform(
		[](const auto& p){ return std::make_pair(p.second, p.first); }
	);
}

// template <typename R, typename V>
// concept range_of = ranges::range<R> && std::same_as<ranges::range_value_t<R>, V>; 
//
// template <typename R, typename V>
// requires range_of<R, V>
// auto pair_swap(const R& pairs){
// 	return pairs | ranges::views::transform(
// 		[](const auto& p){ return std::make_pair(p.second, p.first); }
// 	);
// }
