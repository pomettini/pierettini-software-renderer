#include <stdio.h>

typedef struct point2
{
    float x;
    float y;
} point2_t;

point2_t screen_space_to_pixel_space(float x, float y, int width, int height)
{
    point2_t point;

    point.x = 0.0;
    point.y = 0.0;

    return point;
}

int main()
{
    return 0;
}
