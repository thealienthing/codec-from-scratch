#include "frame.hpp"
#include <spdlog/spdlog.h>

Frame::Frame(PixelFormat _format, uint64_t _width, uint64_t _height)
    : format(_format), width(_width), height(_height),
      num_channels(GetNumChannels(_format)),
      size_bytes(num_channels * width * height) {
  spdlog::debug("Frame Created: {}", magic_enum::enum_name(format));
  buffer = std::make_unique<uint8_t[]>(static_cast<size_t>(size_bytes));
}

FrameFileReader::FrameFileReader(std::string file_path) {
  file = std::ifstream(file_path, std::ios::binary | std::ios::ate);
  if (!file) {
    spdlog::error("failed to open file reader");
  }
  std::streampos temp_size = file.tellg();
  std::streamoff offset = static_cast<std::streamoff>(temp_size);
  file_size = static_cast<uint64_t>(offset);

  file.seekg(0, std::ios::beg);
  pos = file.tellg();

  spdlog::info("File opened. Size: {}", file_size);
}

uint64_t FrameFileReader::Size() { return file_size; }

bool RGBToYUV420(Frame &rgb, Frame &yuv) {
  // YUV conversion steps
  return false;
}

bool FrameFileReader::ReadIntoFrame(Frame &f) {
  if (Size() % f.size_bytes != 0) {
    spdlog::error("File size not compatible with frame size");
    return false;
  }
  if (file.peek() == std::char_traits<char>::eof()) {
    spdlog::info("EOF");
    return false;
  }

  file.read(reinterpret_cast<char *>(f.buffer.get()), f.size_bytes);
  pos = file.tellg();
  spdlog::trace(static_cast<std::streamoff>(pos));
  return true;
}