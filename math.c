#include "math.h"

// Convert from screen space to pixels
point2_t screen_space_to_pixel(float x, float y, int width, int height)
{
    point2_t point;

    point.x = ((x + 1) / 2) * width;
    point.y = ((y + 1) / 2) * height;

    // Clamp values to -1.0 +1.0
    point.x = (point.x > width) ? -1 : ((point.x < 0) ? -1 : point.x);
    point.y = (point.y > height) ? -1 : ((point.y < 0) ? -1 : point.y);

    return point;
}

vector3_t vector3_new(float x, float y, float z)
{
    vector3_t vector3 = {.x = x, .y = y, .z = z};
    return vector3;
}

vector3_t vector3_zero()
{
    vector3_t vector3 = {0, 0, 0};
    return vector3;
}

// TEST
vector3_t vector3_add(vector3_t a, vector3_t b)
{
    vector3_t add;
    add.x = a.x + b.x;
    add.y = a.y + b.y;
    add.z = a.z + b.z;
    return add;
}

// TEST
vector3_t vector3_sub(vector3_t a, vector3_t b)
{
    vector3_t sub;
    sub.x = a.x - b.x;
    sub.y = a.y - b.y;
    sub.z = a.z - b.z;
    return sub;
}

float lerp(float start, float end, float gradient)
{
    return start + (end - start) * gradient;
}

float inversed_slope(float x0, float y0, float x1, float y1)
{
    return (x1 - x0) / (y1 - y0);
}
