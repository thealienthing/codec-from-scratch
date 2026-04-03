#include "include/frame.hpp"
#include <frame.hpp>
#include <spdlog/cfg/env.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

// int main(int argc, char **argv) {
//   if (argc < 2) {
//     spdlog::error("must pass path to video file (eg. video.rgb24)");
//     return -1;
//   }
//   std::string file_path(argv[1]);
//   spdlog::set_level(spdlog::level::debug);

//   Frame f(PixelFormat::RGB24, 384, 216);
//   Frame f_yuv(PixelFormat::YUV420, 384, 216);
//   FrameFileReader vid_file(file_path);
//   while (true) {
//     if (!vid_file.ReadIntoFrame(f)) {
//       break;
//     }
//     RGBToYUV420(f, f_yuv);
//   }
// }

/*
 * This example code creates an SDL window and renderer, and then clears the
 * window to a different color every frame, so you'll effectively get a window
 * that's smoothly fading between colors.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_SetAppMetadata("Example Renderer Clear", "1.0",
                     "com.example.renderer-clear");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 640, 480,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  SDL_SetRenderLogicalPresentation(renderer, 640, 480,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }
  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
  const double now = ((double)SDL_GetTicks()) /
                     1000.0; /* convert from milliseconds to seconds. */
  /* choose the color for the frame we will draw. The sine wave trick makes it
   * fade between colors smoothly. */
  const float red = (float)(0.5 + 0.5 * SDL_sin(now));
  const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
  const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
  SDL_SetRenderDrawColorFloat(
      renderer, red, green, blue,
      SDL_ALPHA_OPAQUE_FLOAT); /* new color, full alpha. */

  /* clear the window to the draw color. */
  SDL_RenderClear(renderer);

  /* put the newly-cleared rendering on the screen. */
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  /* SDL will clean up the window/renderer for us. */
}
