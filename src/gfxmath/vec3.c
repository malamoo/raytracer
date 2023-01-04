#include <stdlib.h>
#include <math.h>
#include "program.h"
#include "gfxmath.h"

static vec3 stdvec3[] = {
    { 0, 0, 0 },  /* VEC3ZERO */
    { 1, 1, 1 },  /* VEC3ONE */
    { 1, 0, 0 },  /* VEC3RIGHT */
    { -1, 0, 0 }, /* VEC3LEFT */
    { 0, 1, 0 },  /* VEC3UP */
    { 0, -1, 0 }, /* VEC3DOWN */
    { 0, 0, 1 },  /* VEC3BACK */
    { 0, 0, -1 }, /* VEC3FRONT */
    { 0, 0, 0 },  /* VEC3BLACK */
    { 1, 0, 0 },  /* VEC3RED */
    { 0, 1, 0 },  /* VEC3GREEN */
    { 0, 0, 1 },  /* VEC3BLUE */
    { 1, 1, 0 },  /* VEC3YELLOW */
    { 0, 1, 1 },  /* VEC3CYAN */
    { 1, 0, 1 },  /* VEC3MAGENTA */
    { 1, 1, 1 }   /* VEC3WHITE */
};

void setvec3(float x, float y, float z, vec3 out)
{
    out[0] = x;
    out[1] = y;
    out[2] = z;
}

void copystdvec3(int std, vec3 out)
{
    if (std >= NELEMS(stdvec3))
        eprintf("bad standard vec3 %d", std);
    copyvec3(stdvec3[std], out);
}

void copyvec3(vec3 a, vec3 out)
{
    out[0] = a[0];
    out[1] = a[1];
    out[2] = a[2];
}

float normvec3(vec3 a)
{
    return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

void setnormalizedvec3(vec3 a, vec3 out)
{
    setscalevec3(1 / normvec3(a), a, out);
}

void normalizevec3(vec3 out)
{
    scalevec3(1 / normvec3(out), out);
}

void setnegvec3(vec3 a, vec3 out)
{
    setscalevec3(-1, a, out);
}

void negvec3(vec3 out)
{
    scalevec3(-1, out);
}

void setscalevec3(float k, vec3 a, vec3 out)
{
    out[0] = k * a[0];
    out[1] = k * a[1];
    out[2] = k * a[2];
}

void scalevec3(float k, vec3 out)
{
    out[0] = k * out[0];
    out[1] = k * out[1];
    out[2] = k * out[2];
}

void addvec3(vec3 a, vec3 b, vec3 out)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

void addaddvec3(vec3 a, vec3 b, vec3 out)
{
    out[0] += a[0] + b[0];
    out[1] += a[1] + b[1];
    out[2] += a[2] + b[2];
}

void subvec3(vec3 a, vec3 b, vec3 out)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

float dotvec3(vec3 a, vec3 b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

void crossvec3(vec3 a, vec3 b, vec3 out)
{
    out[0] = a[1] * b[2] - a[2] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
}

void reflectvec3(vec3 d, vec3 n, vec3 out)
{
    setscalevec3(-2 * dotvec3(d, n), n, out);
    addvec3(d, out, out);
}
