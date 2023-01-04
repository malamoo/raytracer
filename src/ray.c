#include <stdlib.h>
#include <math.h>
#include "program.h"
#include "gfxmath.h"
#include "raytracer.h"

void setray(vec3 origin, vec3 direction, Ray *out)
{
    copyvec3(origin, out->origin);
    copyvec3(direction, out->dir);
}

void evalray(Ray *ray, float t, vec3 out)
{
    vec3 td;

    setscalevec3(t, ray->dir, td);
    addvec3(ray->origin, td, out);
}
