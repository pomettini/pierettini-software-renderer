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

typedef struct vector3
{
    float x; 
    float y;
    float z;
} vector3_t;

point2_t screen_space_to_pixel(float x, float y, int width, int height);
vector3_t vector3_new(float x, float y, float z);
vector3_t vector3_zero();
float lerp(float start, float end, float gradient);
float inversed_slope(float x0, float y0, float x1, float y1);
