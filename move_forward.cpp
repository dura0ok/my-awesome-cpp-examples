#include <iostream>
#include <type_traits>

template<class T> struct remove_reference { using type = T; };
template<class T> struct remove_reference<T&> { using type = T; };
template<class T> struct remove_reference<T&&> { using type = T; };

void foo(int &) { std::cout << "&" << std::endl; }
void foo(int &&) { std::cout << "&&" << std::endl; }

template <typename T>
constexpr T&& forward(typename remove_reference<T>::type& value)
{
    return static_cast<T&&>(value);
}

template <typename T>
constexpr T&& forward(typename remove_reference<T>::type&& value)
{
    static_assert(!std::is_lvalue_reference<T>::value, "T must be an lvalue reference");
    return static_cast<T&&>(value);
}

template <typename T>
constexpr typename remove_reference<T>::type&& move(T&& value)
{
    return static_cast<typename remove_reference<T>::type&&>(value);
}

template <typename T>
void bar(T && value)
{
    foo(forward<T>(value));
}

int main() {
    int x = 10;

    foo(x);
    foo(move(x));

    bar(x);

    return 0;
}
