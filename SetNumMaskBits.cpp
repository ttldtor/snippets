#include <limits>
#include <type_traits>

template <typename T>
constexpr T setNumMaskBits(std::size_t len) {
    using U = typename std::make_unsigned<T>::type;
    
    return len >= sizeof(T) * 8 ? std::numeric_limits<T>::max(): static_cast<T>((U(1) << len) - U(1));
}
