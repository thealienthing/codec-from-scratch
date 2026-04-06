#include "frame.hpp"
#include <spdlog/spdlog.h>

Frame::Frame(PixelFormat _format, uint64_t _width, uint64_t _height)
    : format(_format), width(_width), height(_height),
      num_channels(GetNumChannels(_format)),
      size_bytes(GetSizeBytes(_width, _height, _format)) {
  spdlog::debug("Frame Created: {}", magic_enum::enum_name(format));
  buffer = std::make_unique<uint8_t[]>(size_bytes);
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
  // if ((rgb.width != yuv.width) || (rgb.height != yuv.height)) {
  //   spdlog::error("input frame resolution {}x{} does not match output frame
  //   "
  //                 "resolution {}x{}",
  //                 rgb.width, rgb.height, yuv.width, yuv.height);
  //   return false;
  // }

  auto row_len = rgb.num_channels * rgb.width;

  uint8_t *u_ptr = &yuv.buffer[rgb.width * rgb.height];
  uint8_t *v_ptr = u_ptr + ((yuv.width / 2) * (yuv.height / 2));
  int pixel = 0;
  for (auto y = 0; y < rgb.height; y += 2) { // skip a row each iter
    auto row_start = row_len * y;
    for (auto x = 0; x < row_len; x += rgb.num_channels * 2) {

      auto row1 = row_start + x;
      auto row2 = row1 + row_len;

      uint8_t r = rgb.buffer[row1];
      uint8_t g = rgb.buffer[row1 + 1];
      uint8_t b = rgb.buffer[row1 + 2];
      // C b = 0.564( B − Y )
      // Cr =0.713(R−Y)
      double y = (kR * r) + (kG * g) + (kB * b);
      auto cb = 0.564 * (b - y);
      auto cr = 0.713 * (r - y);
      uint32_t u = cb;
      uint32_t v = cr;
      yuv.buffer[row1 / 3] = y;

      r = rgb.buffer[row1 + 3];
      g = rgb.buffer[row1 + 4];
      b = rgb.buffer[row1 + 5];
      y = (kR * r) + (kG * g) + (kB * b);

      cb = 0.564 * (b - y);
      cr = 0.713 * (r - y);
      u += cb;
      v += cr;
      yuv.buffer[row1 / 3 + 1] = y;

      r = rgb.buffer[row2];
      g = rgb.buffer[row2 + 1];
      b = rgb.buffer[row2 + 2];
      y = (kR * r) + (kG * g) + (kB * b);
      cb = 0.564 * (b - y);
      cr = 0.713 * (r - y);
      u += cb;
      v += cr;
      yuv.buffer[row2 / 3] = y;

      r = rgb.buffer[row2 + 3];
      g = rgb.buffer[row2 + 4];
      b = rgb.buffer[row2 + 5];
      y = (kR * r) + (kG * g) + (kB * b);
      cb = 0.564 * (b - y);
      cr = 0.713 * (r - y);
      u += cb;
      v += cr;
      yuv.buffer[row2 / 3 + 1] = y;
      u /= 4;
      v /= 4;
      u_ptr[pixel / 2] = static_cast<uint8_t>(255);
      auto bbbbb = yuv.width * yuv.height / 4;
      u_ptr[bbbbb + pixel] = static_cast<uint8_t>(255);
      pixel++;
    }
  }

  return true;
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