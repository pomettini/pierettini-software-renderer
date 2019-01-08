#include "math.h"

point2_t screen_space_to_pixel(float x, float y, int width, int height)
{
    point2_t point;

    point.x = ((x + 1) / 2) * width;
    point.y = ((y + 1) / 2) * height;

    // Clamp values to -1.0 +1.0
    point.x = (point.x > width) ? width : ((point.x < 0) ? 0 : point.x);
    point.y = (point.y > height) ? height : ((point.y < 0) ? 0 : point.y);

    return point;
}
