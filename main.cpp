#include <frame.hpp>
#include <spdlog/cfg/env.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

int main() {
  spdlog::set_level(spdlog::level::debug);
  spdlog::debug("HELLO WORLD");
  spdlog::info("HELLO WORLD");
  spdlog::warn("HELLO WORLD");
  Frame f(PixelFormat::YUV420, 1920, 1080);
}