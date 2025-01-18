#include <type_traits>
#include <iostream>

template <typename, typename = void>
struct is_default_constructible : std::false_type {};

template <typename T>
struct is_default_constructible<T, std::void_t<decltype(T())>> : std::true_type {};

template <typename T>
constexpr bool is_default_constructible_v = is_default_constructible<T>::value;

struct NoDefaultConstructor {
    explicit NoDefaultConstructor(int) {}
};

struct DefaultConstructor {};

int main() {
    std::cout << std::boolalpha;
    std::cout << "int is default constructible: " << is_default_constructible_v<int> << '\n';
    std::cout << "NoDefaultConstructor is default constructible: "
              << is_default_constructible_v<NoDefaultConstructor> << '\n';
    std::cout << "DefaultConstructor is default constructible: "
              << is_default_constructible_v<DefaultConstructor> << '\n';
    return 0;
}
