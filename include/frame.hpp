#pragma once

#include <buffer.hpp>
#include <cstdint>
#include <spdlog/fmt/ostr.h> // Essential for operator<< support

#include <magic_enum.hpp>
#include <memory>

enum class PixelFormat { RGB24, YUV420 };
std::ostream &operator<<(std::ostream &os, const PixelFormat &px) {
  return os << magic_enum::enum_name(px);
}
class Frame {
public:
  Frame(PixelFormat _format, uint64_t _width, uint64_t _height);
  const PixelFormat format;
  const uint64_t width;
  const uint64_t height;

private:
  std::unique_ptr<Buffer> buffer;
};