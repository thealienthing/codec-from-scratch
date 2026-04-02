#include "include/frame.hpp"
#include <frame.hpp>
#include <spdlog/cfg/env.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    spdlog::error("must pass path to video file (eg. video.rgb24)");
    return -1;
  }
  std::string file_path(argv[1]);
  spdlog::set_level(spdlog::level::debug);

  Frame f(PixelFormat::RGB24, 384, 216);
  Frame f_yuv(PixelFormat::YUV420, 384, 216);
  FrameFileReader vid_file(file_path);
  while (true) {
    if(!vid_file.ReadIntoFrame(f)) {
      break;
    }
    RGBToYUV420(f, f_yuv);
  }
}