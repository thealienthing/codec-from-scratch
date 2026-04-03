#include "include/frame.hpp"
#include <chrono>
#include <frame.hpp>
#include <spdlog/cfg/env.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

// int main(int argc, char **argv) {
// }

#include <SDL3/SDL.h>
#include <vector>

int main(int argc, char *argv[]) {
  const int width = 384;
  const int height = 216;

  if (argc < 2) {
    spdlog::error("must pass path to video file (eg. video.rgb24)");
    return -1;
  }
  std::string file_path(argv[1]);
  spdlog::set_level(spdlog::level::debug);

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_CreateWindowAndRenderer("SDL3 Array to Window", width, height, 0, &window,
                              &renderer);

  int fps = 30;
  int ms_per_frame = 1000 / fps;
  bool running = true;

  Frame f(PixelFormat::RGB24, width, height);
  Frame yuv(PixelFormat::YUV420, width / 2, height / 2);
  FrameFileReader vid_file(file_path);

  // 1. Create a streaming texture (using RGBA8888 format)
  // SDL_PIXELFORMAT_IYUV
  // SDL_Texture *texture =
  //     SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24,
  //                       SDL_TEXTUREACCESS_STREAMING, width, height);

  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV,
                        SDL_TEXTUREACCESS_STREAMING, width, height);
  while (running) {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_EVENT_QUIT) {
      running = false;
    } else if (event.type == SDL_EVENT_KEY_DOWN) {
      running = false;
    }
    // Try reading file into frame
    auto start = std::chrono::steady_clock::now();
    if (vid_file.ReadIntoFrame(f)) {
      // 3.a. Process the frame to final display pixel format
      // Operation to measure

      if (RGBToYUV420(f, yuv)) {
        spdlog::info("Converted YUV");
      }

      // Calculate the difference
      auto end = std::chrono::steady_clock::now();
      auto diff =
          std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

      // Wait the remaining amount of time before rendering frame to ensure
      // stable fps
      SDL_Delay(ms_per_frame - diff.count());

      // SDL_UpdateTexture(texture, NULL, f.buffer.get(), f.size_bytes);
      SDL_UpdateTexture(texture, NULL, yuv.buffer.get(), yuv.size_bytes);
      // 3.b. Update the texture with the array
    } else {
      running = false;
    }

    // 4. Render and Present
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL,
                      NULL); // NULL renders to full window
    SDL_RenderPresent(renderer);
  }

  SDL_RenderClear(renderer);
  SDL_RenderTexture(renderer, texture, NULL,
                    NULL); // NULL renders to full window
  SDL_RenderPresent(renderer);

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}