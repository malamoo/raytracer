#include <stdlib.h>
#include <math.h>
#include "program.h"
#include "gfxmath.h"
#include "raytracer.h"

static Surface *makesurf_sphere(void);
static Surface *makesurf_plane(void);
static void hit_sphere(Surface *surf, Ray *ray, float t0, float t1, Hit *out);
static void hit_plane(Surface *surf, Ray *ray, float t0, float t1, Hit *out);

static Surface *(*makesurffn[])(void) = {
    makesurf_sphere, /* SPHERE */
    makesurf_plane   /* PLANE */
};

Surface *makesurf(int type)
{
    if (type >= NELEMS(makesurffn))
        eprintf("bad surface type %d", type);
    return (*makesurffn[type])();
}

static Surface *makesurf_sphere(void)
{
    Surface *sp;

    sp = emalloc(sizeof(Sphere));
    sp->hit = hit_sphere;
    return sp;
}

static Surface *makesurf_plane(void)
{
    Surface *sp;

    sp = emalloc(sizeof(Plane));
    sp->hit = hit_plane;
    return sp;
}

static void hit_sphere(Surface *surf, Ray *ray, float t0, float t1, Hit *out)
{
    Sphere *sphere;
    vec3 p, n, oc;
    float a, b, c;
    float d;
    float root;
    float sqrtd;

    sphere = (Sphere *) surf;

    /* calculate coefficients of quadratic */
    a = dotvec3(ray->dir, ray->dir);
    subvec3(ray->origin, sphere->center, oc);
    b = 2 * dotvec3(ray->dir, oc);
    c = dotvec3(oc, oc) - sphere->radius * sphere->radius;

    /* check if real solutions exist */
    d = b * b - 4 * a * c;
    if (d < 0) { /* no hit */
        out->t = INF;
        return;
    }

    /* find the nearest root in range */
    sqrtd = sqrt(d);
    root = (-b - sqrtd) / (2 * a);
    if (root < t0 || root > t1) {
        root = (-b + sqrtd) / (2 * a);
        if (root < t0 || root > t1) {
            out->t = INF;
            return;
        }
    }

    evalray(ray, root, p);
    subvec3(p, sphere->center, n);
    scalevec3(1 / sphere->radius, n); /* normalize */

    out->surface = surf;
    out->t = root;
    copyvec3(n, out->n);
}

static void hit_plane(Surface *surf, Ray *ray, float t0, float t1, Hit *out)
{
    Plane *plane;
    vec3 op;
    float t, dn;

    plane = (Plane *) surf;

    /* check if ray parallel to plane */
    dn = dotvec3(ray->dir, plane->n);
    if (dn == 0) { /* no hit */
        out->t = INF;
        return;
    }

    /* find root in range */
    subvec3(ray->origin, plane->p, op);
    t = -dotvec3(op, plane->n) / dn;
    if (t < t0 || t > t1) {
        out->t = INF;
        return;
    }

    out->surface = surf;
    out->t = t;
    copyvec3(plane->n, out->n);
}
