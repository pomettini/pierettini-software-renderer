#include "math.h"

point2_t screen_space_to_pixel(float x, float y, int width, int height)
{
    point2_t point;

    point.x = ((x + 1) / 2) * width;
    point.y = ((y + 1) / 2) * height;

    return point;
}
