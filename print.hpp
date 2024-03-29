#pragma once
#include <algorithm>
#include <bitset>
#include <iostream>
#include <numeric>
#include <ranges>
#include <tuple>
#include <typeinfo>
#include <utility>
using namespace std;
// overload for tuple
// https://stackoverflow.com/questions/6245735/pretty-print-stdtuple
template <typename TupType, size_t... I>
void tuple_print(const TupType &_tup, std::index_sequence<I...>, string delim);
template <typename... T>
void print(const std::tuple<T...> &_tup, string delim = ",");
template <typename T1, typename T2>
void print(const pair<T1, T2> &p, string delim = ",");
template <typename TupType, size_t... I>
void tuple_print(const TupType &_tup, std::index_sequence<I...>, string delim)
{
    cout << "[";
    (..., (cout << (I == 0 ? "" : delim) << std::get<I>(_tup)));
    cout << "]";
}
template <typename... T>
void print(const std::tuple<T...> &_tup, string delim)
{
    tuple_print(_tup, std::make_index_sequence<sizeof...(T)>(), delim);
}
template <typename>
struct is_tuple : std::false_type {
};

template <typename... T>
struct is_tuple<std::tuple<T...>> : std::true_type {
};
template <typename>
struct is_bitset : std::false_type {
};
template <size_t sz>
struct is_bitset<std::bitset<sz>> : std::true_type {
};
// overload for pairs
template <typename T1, typename T2>
void print(const pair<T1, T2> &p, string delim)
{
    cout << '{' << p.first << ": " << p.second << '}' << delim;
}

#if __cplusplus >= 201709L
template <typename T>
concept printable = requires(const T &a) {
                        cout << a;
                    };
template <typename T>
concept arr = is_array_v<T>;
template <typename T>
concept ptr = is_pointer_v<T>;
template <typename T>
concept boolean = is_same_v<T, bool>;
template <typename T>
concept directPrintable = printable<T> && !
boolean<T> && !is_bitset<T>() && !is_array_v<T>;
template <typename T>
concept normalObj = !(directPrintable<T> || boolean<T> || arr<T> || ranges::input_range<T> || ptr<T> || is_tuple<T>() || is_bitset<T>());
template <size_t sz>
void print(const bitset<sz> &bs, string delim = ",");
template <directPrintable T>
void print(const T &prt, string delim = "");
template <boolean B>
void print(const B &b, string delim = "");
template <ranges::input_range rng>
void print(const rng &ir);
template <normalObj obj>
void print(const obj &o);
// overload for bitset
template <boolean B>
void print(const B &b, string delim)
{
    cout << std::boolalpha << b << delim;
}
template <size_t sz>
void print(const bitset<sz> &bs, string delim)
{
    cout << "[";
    for (size_t i = 0; i < sz; ++i) {
        print(bs[i], ","s);
    }
    cout << "\b]\n";
}
template <directPrintable T>
void print(const T &prt, string delim)
{
    cout << prt << delim;
};
template <ranges::input_range rng>
void print(const rng &ir)
{

    cout << '[';
    ranges::for_each(ir, [](const auto &ele) {
        print(ele, ","s);
    });
    cout << "\b]\n";
}
template <normalObj obj>
void print(const obj &o)
{
    cout << typeid(o).name();
}
#else

#endif
