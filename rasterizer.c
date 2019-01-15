#include "rasterizer.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// crazy defines
#define A triangle->a.pixel_point
#define B triangle->b.pixel_point
#define C triangle->c.pixel_point

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

// Giving a context, it colors a single pixel on the screen
void put_pixel(int x, int y, context_t *ctx, int r, int g, int b)
{
    if (x < 0 || y < 0 || x >= ctx->width || y >= ctx->height)
        return;

    int offset = ((y * ctx->width) + x) * 4;
    ctx->framebuffer[offset++] = r;
    ctx->framebuffer[offset++] = g;
    ctx->framebuffer[offset++] = b;
    ctx->framebuffer[offset] = 255;
}

// adding a triangle in a list of memory
void append_triangle(context_t *ctx, triangle_t triangle)
{
    if (ctx->triangles_index >= ctx->triangles_length)
        triangle_list_resize(ctx);

    ctx->triangles[ctx->triangles_index] = triangle;
    ctx->triangles_index++;
}

// create a block of memory of 100 triangles
void triangle_list_init(context_t *ctx)
{
    ctx->triangles_index = 0;
    ctx->triangles_length = 2;
    ctx->triangles = malloc(sizeof(triangle_t) * ctx->triangles_length);
    memset(ctx->triangles, 0, sizeof(triangle_t) * ctx->triangles_length);
}

void triangle_list_resize(context_t *ctx)
{
    ctx->triangles_length *= 2;
    ctx->triangles = realloc(ctx->triangles, sizeof(triangle_t) * ctx->triangles_length);
}

// Giving the triangle coords, draw on the screen
void rasterize(context_t *ctx, triangle_t *triangle)
{
    point_to_view(ctx, &triangle->a);
    point_to_view(ctx, &triangle->b);
    point_to_view(ctx, &triangle->c);

    view_to_raster(ctx, &triangle->a);
    view_to_raster(ctx, &triangle->b);
    view_to_raster(ctx, &triangle->c);

    sort_triangle(ctx, triangle);

    int total_height = C.y - A.y;
    // First triangle
    for (int y = A.y; y <= B.y; y++)
    {
        int segment_height = B.y - A.y + 1;
        float alpha = (float)(y - A.y) / total_height;
        float beta = (float)(y - A.y) / segment_height;

        point2_t point_a;
        point_a.x = A.x + (C.x - A.x) * alpha;
        point_a.y = A.y + (C.y - A.y) * alpha;

        point2_t point_b;
        point_b.x = A.x + (B.x - A.x) * beta;
        point_b.y = A.y + (B.y - A.y) * beta;

        // If the triangle is facing left, I swap the vertices
        // So it will render from left to right
        if (point_a.x > point_b.x)
            swap_point(&point_a, &point_b);

        for (int j = point_a.x; j <= point_b.x; j++)
        {
            put_pixel(j, y, ctx, 0, 255, 0);
        }
    }

    // TODO: Refactor to a single for loop
    // Second triangle
    for (int y = B.y; y <= C.y; y++)
    {
        int segment_height = C.y - B.y + 1;
        float alpha = (float)(y - A.y) / total_height;
        float beta = (float)(y - B.y) / segment_height;

        point2_t point_a;
        point_a.x = A.x + (C.x - A.x) * alpha;
        point_a.y = A.y + (C.y - A.y) * alpha;

        point2_t point_b;
        point_b.x = B.x + (C.x - B.x) * beta;
        point_b.y = B.y + (C.y - B.y) * beta;

        if (point_a.x > point_b.x)
            swap_point(&point_a, &point_b);

        for (int j = point_a.x; j <= point_b.x; j++)
        {
            put_pixel(j, y, ctx, 0, 0, 255);
        }
    }
}

// This function will sort the vertices of a triangle on their Y
void sort_triangle(context_t *ctx, triangle_t *triangle)
{
    if (A.y > B.y)
        swap_point(&A, &B);

    if (B.y > C.y)
        swap_point(&B, &C);

    if (A.y > B.y)
        swap_point(&A, &B);
}

void swap_point(point2_t *point1, point2_t *point2)
{
    point2_t temp = *point2;
    *point2 = *point1;
    *point1 = temp;
}

static void view_to_raster(context_t *ctx, vertex_t *vertex)
{
    float fov = (60.0 / 2) * (M_PI / 180.0);
    float camera_distance = tan(fov);

    float projected_x = vertex->view_position.x / (camera_distance * vertex->view_position.z);
    float projected_y = vertex->view_position.y / (camera_distance * vertex->view_position.z);

    vertex->pixel_point.x = (projected_x + 1) * (ctx->width * 0.5);
    vertex->pixel_point.y = ctx->height - ((projected_y + 1) * (ctx->height * 0.5));
}

static void point_to_view(context_t *ctx, vertex_t *vertex)
{
    vertex->view_position = vector3_sub(vertex->position, ctx->camera_position);
}
