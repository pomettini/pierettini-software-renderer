#include "rasterizer.h"
#include <stdio.h>
#include "math.h"
#include <SDL2/SDL.h>

// TODO
// * Piera must handle errors

int main()
{
    context_t ctx;
    ctx.width = 600;
    ctx.height = 600;

    ctx.framebuffer = NULL;

    if (!ctx.framebuffer)
        return -1;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Pierettini Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 600, 600);

    for (;;)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_Quit)
                return 0;
        }
        
        int pitch;
        SDL_LockTexture(texture, NULL, &ctx.framebuffer, &pitch);

        // Rasterize

        SDL_UnlockTexture(texture);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    return 0;
}
