#include "gfxmath.h"

void cframecamera(vec3 eye, vec3 viewdir, Cframe *framep)
{
    vec3 d, up;
    vec3 u, v, w;

    vec3norm(viewdir, d);
    vec3up(up);

    vec3neg(d, w);
    vec3cross(up, w, u);
    vec3cross(w, u, v);

    vec3copy(eye, framep->e);
    vec3copy(u, framep->u);
    vec3copy(v, framep->v);
    vec3copy(w, framep->w);
}