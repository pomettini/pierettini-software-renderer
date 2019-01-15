#include "rasterizer.h"
#include <stdio.h>
#include <stdlib.h>
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
    // for the square
    triangle_t triangle1 = triangle(
        -0.5, -0.5, 0,
        -0.5, 0.5, 0,
        0.5, 0.5, 0);

    triangle_t triangle2 = triangle(
        -0.5, -0.5, 0,
        0.5, -0.5, 0,
        0.5, 0.5, 0);

    // for the edges of the screen
    triangle_t triangle3 = triangle(
        -1, -1, 0,
        -1, -0.75, 0,
        -0.75, -1, 0);

    triangle_t triangle4 = triangle(
        1, 1, 0,
        1, 0.75, 0,
        0.75, 1, 0);

    triangle_t triangle5 = triangle(
        -1, 1, 0,
        -1, 0.75, 0,
        -0.75, 1, 0);

    triangle_t triangle6 = triangle(
        1, -1, 0,
        1, -0.75, 0,
        0.75, -1, 0);

    triangle_list_init(&ctx);
    append_triangle(&ctx, triangle1);
    append_triangle(&ctx, triangle2);
    append_triangle(&ctx, triangle3);
    append_triangle(&ctx, triangle4);
    append_triangle(&ctx, triangle5);
    append_triangle(&ctx, triangle6);

    SDL_Init(SDL_INIT_VIDEO);

    // Create the window
    SDL_Window *window = SDL_CreateWindow("Pierettini Software Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, 0);
    if (!window)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError);
    }
    // Create the renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_Log("Unable to create renderer: %s", SDL_GetError);
    }
    // Create the texture
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 600, 600);
    if (!texture)
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
        // rasterize(&ctx, &ctx.triangles[0]);
        // rasterize(&ctx, &ctx.triangles[1]);
        rasterize(&ctx, &ctx.triangles[2]);
        rasterize(&ctx, &ctx.triangles[3]);
        rasterize(&ctx, &ctx.triangles[4]);
        rasterize(&ctx,&ctx.triangles[5]);

        SDL_UnlockTexture(texture);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    return 0;
}
