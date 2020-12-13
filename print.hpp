#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <tuple>
#include <typeinfo>
#include <unordered_map>
#include <vector>
using namespace std;
//overload for tuple
//https://stackoverflow.com/questions/6245735/pretty-print-stdtuple
template <typename TupType, size_t... I>
void tuple_print(const TupType &_tup, std::index_sequence<I...>, string delim)
{
    cout << "[";
    (..., (cout << (I == 0 ? "" : delim) << std::get<I>(_tup)));
    cout << "]";
}

template <typename... T>
void print(const std::tuple<T...> &_tup, string delim = ",")
{
    tuple_print(_tup, std::make_index_sequence<sizeof...(T)>(), delim);
}
template <typename>
struct is_tuple : std::false_type {
};

template <typename... T>
struct is_tuple<std::tuple<T...>> : std::true_type {
};
//overload for pairs
template <typename T1, typename T2>
void print(const pair<T1, T2> p, string delim = ",")
{
    cout << '{' << p.first << ": " << p.second << '}' << delim;
}
#if __cplusplus >= 201709L
template <typename T>
concept printable = requires(T a)
{
    cout << a;
};
template <typename T>
concept arr = is_array_v<T>;
template <typename T>
concept ptr = is_pointer_v<T>;
template <typename T>
concept boolean = is_same_v<T, bool>;
template <typename T>
concept directPrintable = printable<T> and not ptr<T> and not boolean<T>;
template <typename T>
concept normalObj = not directPrintable<T> and not boolean<T> and not arr<T> and not ranges::input_range<T> and not ptr<T> and not is_tuple<T>();
template <directPrintable T>
void print(const T prt, string delim = "")
{
    cout << prt << delim;
};
template <boolean B>
void print(const B b, string delim = "")
{
    cout << (b ? "true" : "false") << delim;
}
template <ranges::input_range rng>
void print(const rng ir)
{

    cout << '[';
    ranges::for_each(ir, [](auto ele) {
        print(ele, ",");
    });
    cout << "\b]\n";
}
template <typename T, size_t sz>
void print(T (&arr)[sz])
{
    cout << '[';
    for_each(arr, arr + sz, [](auto ele) {
        print(ele, ",");
    });
    cout << "\b]\n";
}
template <normalObj obj>
void print(obj o)
{
    cout << typeid(o).name();
}
#else

#endif