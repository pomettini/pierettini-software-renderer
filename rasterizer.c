#include "rasterizer.h"
#include <string.h>

vertex_t vertex_new(vector3_t position)
{
    vertex_t vertex;
    memset(&vertex, 0, sizeof(vertex_t));
    vertex.position = position;
    return vertex;
}

triangle_t triangle_new(vertex_t a, vertex_t b, vertex_t c)
{
    triangle_t triangle = {.a = a, .b = b, .c = c};
    return triangle;
}

void put_pixel(int x, int y, context_t *ctx)
{
    if (x < 0 || y < 0 || x >= ctx->width || y >= ctx->height)
        return;

    int offset = ((y * ctx->width) + x) * 4;
    ctx->framebuffer[offset++] = 255;
    ctx->framebuffer[offset++] = 255;
    ctx->framebuffer[offset++] = 255;
    ctx->framebuffer[offset] = 255;
}

void rasterize(context_t *ctx, triangle_t *triangle)
{
    // SDL_Log("a: %f %f %f", triangle->a.position.x, triangle->a.position.y, triangle->a.position.z);
    // SDL_Log("b: %f %f %f", triangle->b.position.x, triangle->b.position.y, triangle->b.position.z);
    // SDL_Log("c: %f %f %f", triangle->c.position.x, triangle->c.position.y, triangle->c.position.z);

    point2_t pixel = screen_space_to_pixel(triangle->a.position.x, triangle->a.position.z, ctx->width, ctx->height);

    put_pixel(pixel.x, pixel.y, ctx);

    pixel = screen_space_to_pixel(triangle->b.position.x, triangle->b.position.y, ctx->width, ctx->height);

    put_pixel(pixel.x, pixel.y, ctx);

    pixel = screen_space_to_pixel(triangle->c.position.x, triangle->c.position.y, ctx->width, ctx->height);

    put_pixel(pixel.x, pixel.y, ctx);
}
