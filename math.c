#include "math.h"

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
    vector3_t hello;
    return hello;
}

