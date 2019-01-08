typedef struct point2
{
    int x;
    int y;
} point2_t;

typedef struct vector2
{
    float x;
    float y;
} vector2_t;

point2_t screen_space_to_pixel(float x, float y, int width, int height);
