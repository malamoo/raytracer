#include "gfxmath.h"

void rayortho(float u, float v, Cframe *framep, Ray *rayp)
{
    vec3 tmp;

    vec3copy(framep->e, rayp->o);
    vec3scale(u, framep->u, tmp);
    vec3add(rayp->o, tmp, rayp->o);
    vec3scale(v, framep->v, tmp);
    vec3add(rayp->o, tmp, rayp->o);
    vec3neg(framep->w, tmp);
    vec3copy(tmp, rayp->d);
}

void rayeval(float t, Ray *rayp, vec3 vec)
{
    vec3 tmp;

    vec3scale(t, rayp->d, tmp);
    vec3add(rayp->o, tmp, vec);
}