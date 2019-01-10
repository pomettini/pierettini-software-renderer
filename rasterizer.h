
#include "math.h"

typedef struct context
{
    int width;
    int height;

    unsigned char *framebuffer;
} context_t;

typedef struct vertex
{
    vector3_t position;
    vector3_t normal;
    vector3_t color;

    int raster_x;
    int raster_y;
} vertex_t;

vertex_t vertex_new(vector3_t position);

typedef struct triangle
{
    vertex_t a;
    vertex_t b;
    vertex_t c;
} triangle_t;

triangle_t triangle_new(vertex_t a, vertex_t b, vertex_t c);

void rasterize(context_t *ctx, triangle_t *triangle);
