#include <huffman.hpp>
#include <iostream>
namespace huff {

leaf::leaf(std::byte _val, unsigned long _freq) : val(_val), freq(_freq) {}

huffman::huffman(std::list<leaf> leaf_list) {
  while (leaf_list.size() != 0) {
    auto x = &leaf_list.front();
    leaf_list.pop_front();
    leaf mine = std::move(*x);
    if (leaf_list.size() == 0) {
      std::cout << "huffman done" << std::endl;
      break;
    }
  }
}

}; // namespace huff