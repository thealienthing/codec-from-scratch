#include <cstddef>
#include <huffman.hpp>
#include <iostream>
namespace huff {

leaf::leaf(std::byte _val, unsigned long _freq) : val(_val), freq(_freq) {}

huffman::huffman(std::list<leaf> *leaf_list) {
  while (leaf_list->size() != 0) {
    std::unique_ptr<leaf> first, second;
    first = std::make_unique<leaf>(std::move(leaf_list->front()));
    std::cout << "first leaf: " << std::to_integer<int>(first->val) << "-"
              << first->freq << std::endl;
    leaf_list->pop_front();

    if (leaf_list->size() > 1) {
      auto second = std::make_unique<leaf>(std::move(leaf_list->front()));
      std::cout << "second leaf: " << std::to_integer<int>(second->val) << "-"
                << second->freq << std::endl;
      leaf_list->pop_front();
      leaf new_leaf(std::byte(0), first->freq + second->freq);
      if (first->freq > second->freq) {
        new_leaf.left = std::move(first);
        new_leaf.right = std::move(second);
      } else {
        new_leaf.left = std::move(second);
        new_leaf.right = std::move(first);
      }

      for (auto iter = leaf_list->begin(); iter != leaf_list->end(); iter++) {
        if (new_leaf.freq <= iter->freq) {
          leaf_list->insert(iter, leaf(std::move(new_leaf)));
          break;
        } else if ((std::next(iter)) == leaf_list->end()) {
          leaf_list->push_back(leaf(std::move(new_leaf)));
          break;
        }
      }

    } else {
      head = std::move(first);
      std::cout << "DUNN" << std::endl;
    }

    if (leaf_list->size() == 0) {
      std::cout << "huffman done" << std::endl;
      break;
    }
  }
}
void leaf::print(int spacing) {
  std::cout << std::to_integer<int>(val) << ": " << freq << std::endl;
  if (right) {
    std::cout << std::string(spacing, ' ') << "right: ";
    right->print(spacing + 2);
  }
  if (left) {
    std::cout << std::string(spacing, ' ') << "left: ";
    left->print(spacing + 2);
  }
}
void huffman::print() { head->print(); }
}; // namespace huff