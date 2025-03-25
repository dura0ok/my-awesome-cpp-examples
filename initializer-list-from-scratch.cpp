#include <iostream>
#include <cstddef>

template <typename T>
class InitializerList {
private:
    const T* _data;
    size_t _size;

public:
    using value_type = T;
    using size_type = size_t;
    using iterator = const T*;
    using const_iterator = const T*;

    constexpr InitializerList() noexcept : _data(nullptr), _size(0) {}

    constexpr InitializerList(const T* data, size_t size) noexcept
        : _data(data), _size(size) {}

    constexpr size_t size() const noexcept { return _size; }
    constexpr const T* begin() const noexcept { return _data; }
    constexpr const T* end() const noexcept { return _data + _size; }
};

template <typename T, size_t N>
constexpr InitializerList<T> make_initializer_list(const T (&arr)[N]) noexcept {
    return InitializerList<T>(arr, N);
}


void printList(InitializerList<int> list) {
    for (int x : list) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main() {
    auto myList = make_initializer_list({1, 2, 3, 4, 5});
    printList(myList);
}

