#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdint>
#include <memory>

typedef std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
typedef std::shared_ptr<SDL_Renderer> _renderer;
typedef std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> _surface;
typedef std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _texture;

typedef uint64_t u64;
