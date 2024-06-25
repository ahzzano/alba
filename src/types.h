#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <memory>

typedef std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
typedef std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer;
