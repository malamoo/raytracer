#include "gfxmath.h"

const double PI = 3.141592653589793;
const double INF = 1 / 0.0;
const double EPS = 1e-2;

float clamp(float x, float min, float max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

float max(float x, float max)
{
    if (x < max)
        return max;
    return x;
}

float min(float x, float min)
{
    if (x > min)
        return min;
    return x;
}

float rad(float deg)
{
    return (deg * PI) / 180;
}
