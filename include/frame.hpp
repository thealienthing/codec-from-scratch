#pragma once

#include <buffer.hpp>
#include <cstdint>
#include <spdlog/fmt/ostr.h> // Essential for operator<< support
#include <spdlog/spdlog.h>

#include <magic_enum/magic_enum.hpp>
#include <memory>

enum class PixelFormat { RGB24, YUV420 };
std::ostream &operator<<(std::ostream &os, const PixelFormat &px) {
  return os << magic_enum::enum_name(px);
}

int GetNumChannels(PixelFormat f) {
  switch (f) {
  case PixelFormat::RGB24:
  case PixelFormat::YUV420:
    return 3;
  default:
    return 0;
  }
}

class Frame {
public:
  Frame(PixelFormat _format, uint64_t _width, uint64_t _height);
  const PixelFormat format;
  const uint64_t width;
  const uint64_t height;
  const int num_channels;
  const uint64_t size_bytes;
  std::unique_ptr<uint8_t[]> buffer;
};

bool RGBToYUV420(Frame &rgb, Frame &yuv);

class FrameFileReader {
public:
  FrameFileReader() = delete;
  FrameFileReader(std::string file_path);
  bool ReadIntoFrame(Frame &f);
  uint64_t Size();

private:
  uint64_t file_size;
  std::ifstream file;
  std::streampos pos;
};