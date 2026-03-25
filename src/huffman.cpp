#include <cstddef>
#include <huffman.hpp>
#include <iostream>
namespace huff {

int leaf::leaves_instantiated = 0;
leaf::leaf() {
  leaves_instantiated++;
  left = nullptr;
  right = nullptr;
}
leaf::leaf(std::byte _val, unsigned long _freq)
    : val(_val), freq(_freq), left(nullptr), right(nullptr) {
  leaves_instantiated++;
}
leaf::leaf(leaf &&_leaf) noexcept
    : left(std::move(_leaf.left)), right(std::move(_leaf.right)) {
  leaves_instantiated++;
  val = _leaf.val;
  freq = _leaf.freq;
}
leaf::~leaf() {
  // std::cout << "Delete " << static_cast<char>(val) << ": " << freq <<
  // std::endl;
  // std::cout << "Leaves instantiated: " << leaves_instantiated << std::endl;
  leaves_instantiated--;
  left.reset();
  right.reset();
}
huffman::huffman(std::list<leaf> *leaf_list) {
  while (leaf_list->size() != 0) {

    auto first =
        std::make_unique<leaf>(std::move(std::move(leaf_list->front())));
    std::cout << "first leaf: " << std::to_integer<int>(first->val) << "-"
              << first->freq << std::endl;
    leaf_list->pop_front();

    auto second = std::make_unique<leaf>(std::move(leaf_list->front()));
    std::cout << "second leaf: " << std::to_integer<int>(second->val) << "-"
              << second->freq << std::endl;
    leaf_list->pop_front();
    leaf new_leaf(std::byte(0), first->freq + second->freq);

    if (first->freq > second->freq) {
      std::cout << "1" << std::endl;
      new_leaf.left = std::move(first);
      new_leaf.right = std::move(second);
    } else {
      std::cout << "2" << std::endl;
      new_leaf.right = std::move(first);
      new_leaf.left = std::move(second);
    }

    if (leaf_list->size() != 0) {
      for (auto iter = leaf_list->begin(); iter != leaf_list->end(); iter++) {
        if (new_leaf.freq <= iter->freq) {
          leaf_list->insert(iter, std::move(new_leaf));
          break;
        } else if ((std::next(iter)) == leaf_list->end()) {
          leaf_list->push_back(std::move(new_leaf));
          break;
        }
      }
    } else {
      head = std::make_unique<leaf>(std::move(new_leaf));
      break;
    }
  }
}

huffman::~huffman() {
  std::cout << "Delete huffman" << std::endl;
  head.reset();
}

void leaf::print(int spacing) {
  std::cout << std::to_integer<int>(val) << ": " << freq << std::endl;
  if (left != nullptr) {
    std::cout << std::string(spacing, ' ') << "left: ";
    left->print(spacing + 2);
  }
  if (right != nullptr) {
    std::cout << std::string(spacing, ' ') << "right: ";
    right->print(spacing + 2);
  }
}
void huffman::print() { head->print(); }
}; // namespace huff