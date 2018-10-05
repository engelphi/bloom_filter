#include <catch.hpp>

#include <bloom_filter.hpp>
#include <hash.hpp>

TEST_CASE("Bloom filter test maybe in", "[basic]") {
  data::bloom_filter<std::string, 256> filter;
  filter.add_hash(hash::fnv::fnv_0_64());
  filter.add_hash(hash::fnv::fnv_1_64());
  filter.add_hash(hash::fnv::fnv_1a_64());
  filter.add_hash(hash::pearson::pearson_64());

  std::string test_string{"Test"};

  filter.insert(test_string);

  REQUIRE(filter.find(test_string));
}

TEST_CASE("bloom filter test definitely not in", "[basic]") {
  data::bloom_filter<std::string, 256> filter;
  filter.add_hash(hash::fnv::fnv_0_64());
  filter.add_hash(hash::fnv::fnv_1_64());
  filter.add_hash(hash::fnv::fnv_1a_64());
  filter.add_hash(hash::pearson::pearson_64());

  std::string test_string_a{"Test1"};
  std::string test_string_b{"Test2"};
  filter.insert(test_string_a);

  REQUIRE(filter.find(test_string_a));
  REQUIRE(!filter.find(test_string_b));
}
