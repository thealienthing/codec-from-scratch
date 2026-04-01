#include "frame.hpp"
#include <spdlog/spdlog.h>

Frame::Frame(PixelFormat _format, uint64_t _width, uint64_t _height)
    : format(_format), width(_width), height(_height) {
  spdlog::debug("Frame Created: {}", magic_enum::enum_name(format));
}