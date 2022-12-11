#include <math.h>
#include "gfxmath.h"

float vec3len(vec3 a)
{
    return sqrtf(a[0] * a[0] +
                 a[1] * a[1] +
                 a[2] * a[2]);
}

void vec3norm(vec3 a, vec3 vec)
{
    vec3scale(1 / vec3len(a), a, vec);
}

void vec3neg(vec3 a, vec3 vec)
{
    vec[0] = -a[0];
    vec[1] = -a[1];
    vec[2] = -a[2];
}

void vec3scale(float k, vec3 a, vec3 vec)
{
    vec[0] = k * a[0];
    vec[1] = k * a[1];
    vec[2] = k * a[2];
}

void vec3add(vec3 a, vec3 b, vec3 vec)
{
    vec[0] = a[0] + b[0];
    vec[1] = a[1] + b[1];
    vec[2] = a[2] + b[2];
}

void vec3sub(vec3 a, vec3 b, vec3 vec)
{
    vec[0] = a[0] - b[0];
    vec[1] = a[1] - b[1];
    vec[2] = a[2] - b[2];
}

void vec3up(vec3 vec)
{
    vec[0] = 0;
    vec[1] = 1;
    vec[2] = 0;
}

float vec3dot(vec3 a, vec3 b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

void vec3cross(vec3 a, vec3 b, vec3 vec)
{
    vec[0] = a[1] * b[2] - a[2] * b[1];
    vec[1] = a[2] * b[0] - a[0] * b[2];
    vec[2] = a[0] * b[1] - a[1] * b[0];
}

void vec3copy(vec3 a, vec3 vec)
{
    vec[0] = a[0];
    vec[1] = a[1];
    vec[2] = a[2];
}
