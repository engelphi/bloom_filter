#include <array>
#include <vector>
#include <functional>

namespace data {
template <typename T, std::size_t FILTER_SIZE, typename COUNTER_SIZE_TYPE>
class counting_bloom_filter {
  public:
    counting_bloom_filter() = default;

    void insert(const T& element);

    bool find(const T& element) const;

    void erase(const T& element);

    void clear();

    void add_hash(std::function<std::size_t(const T&)> hash_function);
  private:
    std::vector<std::function<std::size_t(const T&)>> m_hash_functions{};

    std::array<COUNTER_SIZE_TYPE, FILTER_SIZE> m_filter_set{};
};

template <typename T, std::size_t FILTER_SIZE, typename COUNTER_SIZE_TYPE>
void counting_bloom_filter<T, FILTER_SIZE, COUNTER_SIZE_TYPE>::insert(const T& element) {
  for (const auto& hash : m_hash_functions) {
    m_filter_set.at(hash(element) % FILTER_SIZE)++;
  }
}

template <typename T, std::size_t FILTER_SIZE, typename COUNTER_SIZE_TYPE>
bool counting_bloom_filter<T, FILTER_SIZE, COUNTER_SIZE_TYPE>::find(const T& element) {
  return std::all_of(std::begin(m_hash_functions), std::end(m_hash_functions),
                     [&, this](const auto& hash) {
                        return m_filter_set.at(hash(element) % FILTER_SIZE) != 0;
                     });
}

template <typename T, std::size_t FILTER_SIZE, typename COUNTER_SIZE_TYPE>
void counting_bloom_filter<T, FILTER_SIZE, COUNTER_SIZE_TYPE>::clear(
    std::function<std::size_t(const T &)> hash_function) {
  for (auto &counter : m_filter_set) {
    counter = 0;
  }
}

template <typename T, std::size_t FILTER_SIZE, typename COUNTER_SIZE_TYPE>
void counting_bloom_filter<T, FILTER_SIZE, COUNTER_SIZE_TYPE>::add_hash(
    std::function<std::size_t(const T &)> hash_function) {
  m_hash_functions.emplace_back(hash_function);
  clear();
}

template <typename T, std::size_t FILTER_SIZE, typename COUNTER_SIZE_TYPE>
void counting_bloom_filter<T, FILTER_SIZE, COUNTER_SIZE_TYPE>::erase(const T& element) {
  if (find(element)) {
    for (const auto& hash : m_hash_functions) {
      m_filter_set.at(hash(element) % FILTER_SIZE)--;
    }
  }
}
} // namespace data
