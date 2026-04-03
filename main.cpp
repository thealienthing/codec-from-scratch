#include "include/frame.hpp"
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

  // 1. Create a streaming texture (using RGBA8888 format)
  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24,
                        SDL_TEXTUREACCESS_STREAMING, width, height);

  int fps = 30;
  int ms_per_frame = 1000 / fps;
  bool running = true;

  Frame f(PixelFormat::RGB24, width, height);
  FrameFileReader vid_file(file_path);
  while (running) {
    SDL_Delay(ms_per_frame);
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_EVENT_QUIT) {
      running = false;
    }
    // Try reading file into frame
    if (vid_file.ReadIntoFrame(f)) {
      // 3.a. Process the frame to final display pixel format

      // 3.b. Update the texture with the array
      SDL_UpdateTexture(texture, NULL, f.buffer.get(), width * 3);
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