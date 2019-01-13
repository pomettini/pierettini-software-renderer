#include "rasterizer.h"
#include <stdio.h>
#include <SDL2/SDL.h>

// Create the triangle struct
#define triangle(x0, y0, z0, x1, y1, z1, x2, y2, z2) \
    triangle_new(                                    \
        vertex_new(vector3_new(x0, y0, z0)),         \
        vertex_new(vector3_new(x1, y1, z1)),         \
        vertex_new(vector3_new(x2, y2, z2)))


int main(int argc, char **argv)
{
    context_t ctx;
    ctx.width = 600;
    ctx.height = 600;

    ctx.framebuffer = NULL;

    // Create the triangles
    triangle_t triangle1 = triangle(
        -0.5, -0.75, 0,
        -0.75, -0.33, 0,
        -0.25, -0.25, 0);

    triangle_t triangle2 = triangle(
        0.25, -0.75, 0,
        0.75, -0.33, 0,
        0.25, -0.25, 0);

    triangle_t triangle3 = triangle(
        -0.25, 0.75, 0,
        -0.25, 0.25, 0,
        -0.75, 0.33, 0);

    triangle_t triangle4 = triangle(
        0.75, 0.5, 0,
        0.33, 0.75, 0,
        0.25, 0.25, 0);

    SDL_Init(SDL_INIT_VIDEO);

    // Create the window
    SDL_Window *window = SDL_CreateWindow("Pierettini Sotware Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, 0);
    if(!window)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError);
    }
    // Create the renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        SDL_Log("Unable to create renderer: %s", SDL_GetError);
    }
    // Create the texture
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 600, 600);
    if(!texture)
    {
        SDL_Log("Unable to create texture: &s", SDL_GetError);
    }

    //Loop
    for (;;)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return 0;
        }

        int pitch;
        SDL_LockTexture(texture, NULL, (void **)&ctx.framebuffer, &pitch);

        // Draw the triangles
        rasterize(&ctx, &triangle1);
        rasterize(&ctx, &triangle2);
        rasterize(&ctx, &triangle3);
        rasterize(&ctx, &triangle4);

        SDL_UnlockTexture(texture);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    return 0;
}
