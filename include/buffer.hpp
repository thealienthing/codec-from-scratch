#pragma once

#include <cstddef>
#include <string>
#include <vector>

class Buffer {
public:
  Buffer() {}
  explicit Buffer(const std::string &str_in);
  explicit Buffer(std::vector<std::byte> &&_data) : buffer(std::move(_data)) {}

  std::size_t size() const { return buffer.size(); }
  std::byte *data() { return buffer.data(); }
  const std::byte &operator[](int index) { return buffer[index]; }
  void push_back(std::byte b) { buffer.push_back(b); }
  std::string debug_str();

  bool operator==(const Buffer &rhs) const {
    if (size() != rhs.size())
      return false;
    for (size_t i = 0; i < size(); i++) {
      if (this->buffer[i] != rhs.buffer[i])
        return false;
    }
    return true;
  }

private:
  std::vector<std::byte> buffer;
};

Buffer read_file_to_buffer(const std::string &file_path);