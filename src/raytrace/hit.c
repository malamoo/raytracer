#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "helper.h"
#include "gfxmath.h"
#include "image.h"
#include "raytrace.h"

static void hitsphere(Ray *rayp, float t0, float t1, Surface *sfp, Hit *hitp);

static Sphere sphere[] = {
    { .center = { 250, 250, -100 }, .radius = 50 },
    { .center = { -250, -250, -100 }, .radius = 50 }
};

static Surface scene[] = {
    { .type = SPHERE, .geometry = &sphere[0], .color = { 0, 0, 255 } },
    { .type = SPHERE, .geometry = &sphere[1], .color = { 255, 0, 0 } }
};

static void (*hitfn[])(Ray *rayp, float t0, float t1, Surface *sfp,
                       Hit *hitp) = {
    hitsphere // SPHERE
};

void hitscene(Ray *rayp, float t0, float t1, Hit *hitp)
{
    int i;
    Hit hit, closest;

    closest.t = INFINITY;

    for (i = 0; i < NELEMS(scene); i++) {
        if (scene[i].type >= NELEMS(hitfn))
            eprintf("bad surface type %d", scene[i].type);
        (*hitfn[scene[i].type])(rayp, t0, t1, &scene[i], &hit);
        if (hit.t < INFINITY) {
            t1 = hit.t;
            closest = hit;
        }
    }

    *hitp = closest;
}

static void hitsphere(Ray *rayp, float t0, float t1, Surface *sfp,
                      Hit *hitp)
{
    Sphere *sp;
    vec3 p, n, tmp;
    float a, b, c;
    float disc;
    float s1, s2, t;

    sp = (Sphere *) sfp->geometry;

    // calculate coefficients of quadratic
    a = vec3dot(rayp->d, rayp->d);
    vec3sub(rayp->o, sp->center, tmp);
    b = 2 * vec3dot(rayp->d, tmp);
    c = vec3dot(tmp, tmp) - sp->radius * sp->radius;

    // check if real solutions exist
    disc = b * b - 4 * a * c;
    if (disc < 0) { // no hit
        hitp->t = INFINITY;
        return;
    }

    s1 = (-b - sqrtf(disc)) / 2 * a;
    s2 = (-b + sqrtf(disc)) / 2 * a;
    if (s1 >= t0 && s1 <= t1) { // smaller solution
        t = s1;
    } else if (s2 >= t0 && s2 <= t1) { // larger solution
        t = s2;
    } else { // no hit
        hitp->t = INFINITY;
        return;
    }

    rayeval(t, rayp, p);
    vec3sub(p, sp->center, n);
    vec3scale(1 / sp->radius, n, n); // unit normal

    hitp->surface = sfp;
    hitp->t = t;
    vec3copy(n, hitp->n);
}
