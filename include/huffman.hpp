#pragma once

#include <cstdint>
#include <fstream>
#include <list>
#include <memory>

namespace huff {
class leaf {
public:
  leaf(std::byte _val, unsigned long _freq);
  leaf(const leaf &l);
  explicit leaf(leaf &&_leaf)
      : left(std::move(_leaf.left)), right(std::move(_leaf.right)) {
    val = _leaf.val;
    freq = _leaf.freq;
  }

  std::byte val;
  unsigned long freq;

  std::unique_ptr<leaf *> left;
  std::unique_ptr<leaf *> right;
};

class huffman {
public:
  huffman(std::list<leaf> leaf_list);
};

}; // namespace huff

std::ostream &operator<<(std::ostream &os, huff::leaf const &l) {
  return os << std::to_integer<int>(l.val) << ":" << l.freq;
}
