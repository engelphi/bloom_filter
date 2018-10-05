#include "bloom_filter/bloom_filter.hpp"
#include "hash/hash.hpp"
#include <string>
#include <iostream>

int main(int argc, char** argv) {
  data::bloom_filter<std::string, 256> filter;
  filter.add_hash(hash::fnv::fnv_0_64());
  filter.add_hash(hash::fnv::fnv_1_64());
  filter.add_hash(hash::fnv::fnv_1a_64());
  filter.add_hash(hash::pearson::pearson_64());

  std::string testA{"Hello"};
  std::string testB{"HALLLOOO"};

  filter.insert(testA);

  if (filter.find(testA)) {
    std::cout << "string " << testA << " is probably in" << std::endl;
  }

  if (filter.find(testB)) {
    std::cout << "string " << testB << " is probably in" << std::endl;
  } else {
    std::cout << "string " << testB << " is definitly not in" << std::endl;
  }

  return filter.find(testA) ? 0 : -1;
}
