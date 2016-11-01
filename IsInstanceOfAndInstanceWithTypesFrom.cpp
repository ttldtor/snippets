#include <type_traits>
#include <iostream>

template <typename... Ts>
struct TypesHolder {};

template <typename T>
struct GetInstancingTypes {};

template <template <typename...> typename C, typename... Ts>
struct GetInstancingTypes<C<Ts...>> {
    using result = TypesHolder<Ts...>;
};

template <typename T, template <typename...> typename C, typename... Ts>
constexpr bool IsInstanceOfHelper(TypesHolder<Ts...> = TypesHolder<Ts...>()) {
    return std::is_same<T, C<Ts...>>::value;
}

template<typename T, template <typename...> typename C>
constexpr bool IsInstanceOf = IsInstanceOfHelper<T, C>(typename GetInstancingTypes<T>::result());

template <template <typename...> typename C, typename T, typename... Ts>
constexpr auto InstanceWithTypesFromHelper(TypesHolder<Ts...> = TypesHolder<Ts...>()) {
    return C<Ts...>();
}

template <template <typename...> typename C, typename T>
using InstanceWithTypesFrom = decltype(InstanceWithTypesFromHelper<C, T>(typename GetInstancingTypes<T>::result()));

template <typename... Ts>
struct A {};

template <typename... Ts>
struct B {};

template<typename... Ts>
void printTypes() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

int main() {
    printTypes<A<int, double, void>>();
    printTypes<typename GetInstancingTypes<A<int, double, void>>::result>();
    std::cout << std::boolalpha << "A<int, double, void> is instance of A -- " << IsInstanceOf<A<int, double, void>, A> << "\n";
    printTypes<InstanceWithTypesFrom<B, A<int, double, void>>>();
}
