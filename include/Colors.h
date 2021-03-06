#ifndef COLORS_H
#define COLORS_H
#include <SDL2/SDL_pixels.h>

namespace SDL
{
    namespace Colors
    {
        const SDL_Color RED = {255,0,0,255};
        const SDL_Color GREEN = {0,255,0,255};
        const SDL_Color BLUE = {0,0,255,255};
        const SDL_Color LIGHT_BLUE = {173,216,230,0};
        const SDL_Color WHITE = {255,255,255,255};
        const SDL_Color BLACK = {0,0,0,255};
        const SDL_Color GRAY = {128,128,128,255};
        const SDL_Color YELLOW = {255,255,0,255};
        const SDL_Color BROWN = {51,25,0,255};
        const SDL_Color PINK = {255,0,255,255};
        extern SDL_Color* m_COLOR_KEY;
        
        extern SDL_Color RAND(short r = -1,short g = -1,short b = -1);
        extern SDL_Color* KEY(short r,short g, short b);
    }
}

#endif
