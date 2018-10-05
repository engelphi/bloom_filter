#pragma once
#include <string>
#include <type_traits>

namespace hash::fnv {

namespace {
  constexpr std::uint32_t FNV_PRIME_32 = 16777619;
  constexpr std::uint32_t FNV_OFFSET_BASIS_32 = 0x811c9dc5;
  constexpr std::uint64_t FNV_PRIME_64 = 1099511628211;
  constexpr std::uint64_t FNV_OFFSET_BASIS_64 = 0xcbf29ce484222325;

template <typename T>
struct fnv_parameters {
  public:
    static constexpr T get_fnv_offset_basis() {
      if constexpr(std::is_same_v<std::uint32_t, T>) {
        return FNV_OFFSET_BASIS_32;
      } else if constexpr(std::is_same_v<std::uint64_t, T>) {
        return FNV_OFFSET_BASIS_64;
      }
      return 0;
    }

    static constexpr T get_fnv_prime() {
      if constexpr(std::is_same_v<std::uint32_t, T>) {
        return FNV_PRIME_32;
      } else if constexpr(std::is_same_v<std::uint64_t, T>) {
        return FNV_PRIME_64;
      }
      return 0;
    }
};

template <typename T, typename Enable=void> 
class fnv_1a {
};

template <typename T>
class fnv_1a<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
  public:
    T operator()(const std::string& value) {
      T hash = fnv_parameters<T>::get_fnv_offset_basis();

      for (const auto& c : value) {
        hash ^= static_cast<std::uint8_t>(c);
        hash *= fnv_parameters<T>::get_fnv_prime();
      }
      return hash;
    }
};

template <typename T, typename Enable=void> 
class fnv_1 {
};

template <typename T>
class fnv_1<T, typename std::enable_if<std::is_integral<T>::value>::type> {
 public:
    T operator()(const std::string& value) {
      T hash = fnv_parameters<T>::get_fnv_offset_basis();
      for (const auto& c : value) {
        hash *= fnv_parameters<T>::get_fnv_prime();
        hash ^= static_cast<std::uint8_t>(c);
      }
      return hash;
    }
};

template <typename T, typename Enable=void> 
class fnv_0 {
};

template <typename T>
class fnv_0<T, typename std::enable_if<std::is_integral<T>::value>::type> {
 public:
    T operator()(const std::string& value) {
      T hash = 0;
      for (const auto& c : value) {
        hash *= fnv_parameters<T>::get_fnv_prime();
        hash ^= static_cast<std::uint8_t>(c);
      }
      return hash;
    }
};
}

using fnv_0_32 = fnv_0<std::uint32_t>;
using fnv_0_64 = fnv_0<std::uint64_t>;
using fnv_1_32 = fnv_1<std::uint32_t>;
using fnv_1_64 = fnv_1<std::uint64_t>;
using fnv_1a_32 = fnv_1a<std::uint32_t>;
using fnv_1a_64 = fnv_1a<std::uint64_t>;
} // namespace hash::fnv
