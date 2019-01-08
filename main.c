#include <stdio.h>
#include "math.h"

int main()
{
    point2_t result = screen_space_to_pixel(0.5, 0.5, 400, 400);

    printf("%d %d\n", result.x, result.y);

    result = screen_space_to_pixel(-0.5, -0.5, 400, 400);

    printf("%d %d\n", result.x, result.y);

    return 0;
}
