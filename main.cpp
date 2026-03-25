#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <buffer.hpp>
#include <codec.hpp>
#include <doctest/doctest.h>
#include <huffman.hpp>
#include <iostream>
#include <list>

const std::string test_file = "video.rgb24";
const int test_file_size = 53996544;

TEST_CASE("Testing huffman encoding") {
  const std::string hufftest =
      "AAAAAABBDSF:"
      "LKAJLKSDJFLKJSDLFKJAOAJOAAAAAOFIJAOFJFJAJAOFJAFOAOJFFFBBBCzzzzzzzzzzzzzzzzzzzzzzzzzzCCCDDDEEF";

  std::map<std::byte, unsigned long> freq_map;

  for (auto i = 0; i < hufftest.size(); i++) {
    std::byte b = static_cast<std::byte>(hufftest[i]);
    auto it = freq_map.find(b);
    if (it != freq_map.end()) {
      it->second++;
    } else {
      freq_map[b] = 1;
    }
  }

  // std::cout << "map size: " << freq_map.size() << std::endl;

  std::list<huff::leaf> leaf_list;
  for (auto i : freq_map) {
    std::cout << static_cast<char>(i.first) << ": " << i.second << std::endl;

    if (leaf_list.empty()) {
      leaf_list.push_front(huff::leaf(i.first, i.second));
    } else {
      for (auto iter = leaf_list.begin(); iter != leaf_list.end(); iter++) {
        if (i.second <= iter->freq) {
          leaf_list.insert(iter, huff::leaf(i.first, i.second));
          break;
        } else if ((std::next(iter)) == leaf_list.end()) {
          leaf_list.push_back(huff::leaf(i.first, i.second));
          break;
        }
      }
    }
  }

  huff::huffman my_huff(&leaf_list);
  my_huff.print();
}

TEST_CASE("Testing Run Length Encoding") {
  Buffer COMPRESSES_TO_HALF = Buffer(std::string("AAAABBBBCCCCDDDDEEEEFFFF"));
  int size = COMPRESSES_TO_HALF.size();
  Buffer compressed = rle(COMPRESSES_TO_HALF);
  CHECK(static_cast<float>(compressed.size()) == (size / 2.0));
  Buffer decoded = rld(compressed);
  // std::cout << "Orig: " << COMPRESSES_TO_HALF.debug_str() << std::endl;
  // std::cout << "Decd: " << decoded.debug_str() << std::endl;
  CHECK(decoded == COMPRESSES_TO_HALF);
}

TEST_CASE("Testing read file to buffer") {
  Buffer sample_buf = read_file_to_buffer(test_file);
}
