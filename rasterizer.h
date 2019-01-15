
#include "math.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b)

typedef struct vertex
{
    vector3_t position;
    vector3_t normal;
    vector3_t color;

    int raster_x;
    int raster_y;
} vertex_t;

typedef struct triangle
{
    vertex_t a;
    vertex_t b;
    vertex_t c;
} triangle_t;

typedef struct context
{
    int width;
    int height;
    triangle_t *triangles;
    int triangles_index;
    int triangles_length;

    unsigned char *framebuffer;
} context_t;

vertex_t vertex_new(vector3_t position);

triangle_t triangle_new(vertex_t a, vertex_t b, vertex_t c);
void put_pixel(int x, int y, context_t *ctx, int r, int g, int b);
void rasterize(context_t *ctx, triangle_t *triangle);
void sort_triangle(context_t *ctx, point2_t *point, triangle_t *triangle);
void swap_point(point2_t *point1, point2_t *point2);
void append_triangle(context_t *ctx, triangle_t triangle);
void triangle_list_init(context_t *ctx);
void triangle_list_resize(context_t *ctx);
