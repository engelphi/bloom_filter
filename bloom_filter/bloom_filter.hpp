#pragma once
#include <bitset>
#include <vector>
#include <functional>
#include <algorithm>

namespace data {
template <typename T, std::size_t FILTER_SIZE> class bloom_filter {
public:
  bloom_filter() = default;

  void insert(const T &element);

  bool find(const T &element) const;

  void add_hash(std::function<std::size_t(const T &)> hash_function);

  void clear();

private:
  std::vector<std::function<std::size_t(const T &)>> m_hash_functions{};

  std::bitset<FILTER_SIZE> m_filter_set{};
};

template <typename T, std::size_t FILTER_SIZE>
void bloom_filter<T, FILTER_SIZE>::add_hash(
    std::function<std::size_t(const T &)> hash_function) {
  m_hash_functions.emplace_back(hash_function);
  clear();
}

template <typename T, std::size_t FILTER_SIZE>
void bloom_filter<T, FILTER_SIZE>::clear() {
  for (int i = 0; i < FILTER_SIZE; i++) {
    m_filter_set.reset(i);
  }
}

template <typename T, std::size_t FILTER_SIZE>
void bloom_filter<T, FILTER_SIZE>::insert(const T &element) {
  for (const auto &hash : m_hash_functions) {
    m_filter_set.set(hash(element) % FILTER_SIZE);
  }
}

template <typename T, std::size_t FILTER_SIZE>
bool bloom_filter<T, FILTER_SIZE>::find(const T &element) const {
  return std::all_of(std::begin(m_hash_functions), std::end(m_hash_functions),
                     [&, this](const auto &hash) {
                       return m_filter_set[hash(element) % FILTER_SIZE];
                     });
}

} // namespace data
