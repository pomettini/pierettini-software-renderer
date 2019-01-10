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

    point2_t pixel = screen_space_to_pixel(triangle->a.position.x, triangle->a.position.y, ctx->width, ctx->height);

    put_pixel(pixel.x, pixel.y, ctx);

    pixel = screen_space_to_pixel(triangle->b.position.x, triangle->b.position.y, ctx->width, ctx->height);

    put_pixel(pixel.x, pixel.y, ctx);

    pixel = screen_space_to_pixel(triangle->c.position.x, triangle->c.position.y, ctx->width, ctx->height);

    put_pixel(pixel.x, pixel.y, ctx);

    sort_triangle(ctx, triangle);
}

void sort_triangle(context_t *ctx, triangle_t *triangle)
{
    point2_t point[3];

    point[0] = screen_space_to_pixel(triangle->a.position.x, triangle->a.position.y, ctx->width, ctx->height);
    point[1] = screen_space_to_pixel(triangle->b.position.x, triangle->b.position.y, ctx->width, ctx->height);
    point[2] = screen_space_to_pixel(triangle->c.position.x, triangle->c.position.y, ctx->width, ctx->height);

    // SDL_Log("0: %d", point[0].y);
    // SDL_Log("1: %d", point[1].y);
    // SDL_Log("2: %d", point[2].y);

    if (point[0].y > point[1].y)
        swap_point(&point[0], &point[1]);

    if (point[1].y > point[2].y)
        swap_point(&point[1], &point[2]);

    if (point[0].y > point[1].y)
        swap_point(&point[0], &point[1]);

    // SDL_Log("00: %d", point[0].y);
    // SDL_Log("11: %d", point[1].y);
    // SDL_Log("22: %d", point[2].y);

    float a_b = inversed_slope(point[0].x, point[0].y, point[1].x, point[1].y);
    float a_c = inversed_slope(point[0].x, point[0].y, point[2].x, point[2].y);

    if (a_b < a_c)
        SDL_Log("Left");
    else
        SDL_Log("Right");
}

void swap_point(point2_t *point1, point2_t *point2)
{
    point2_t temp = *point2;
    *point2 = *point1;
    *point1 = temp;
}
