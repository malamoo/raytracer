#include <stdlib.h>
#include "program.h"
#include "gfxmath.h"
#include "raytracer.h"

static Light *makelight_pt(void);
static Light *makelight_amb(void);
static void illum_pt(Light *light, Ray *ray, Hit *hit, vec3 out);
static void illum_amb(Light *light, Ray *ray, Hit *hit, vec3 out);

static Light *(*makelightfn[])(void) = {
    makelight_pt, /* PTLIGHT */
    makelight_amb /* AMBLIGHT */
};

Light *makelight(int type)
{
    if (type >= NELEMS(makelightfn))
        eprintf("bad light type %d", type);
    return (*makelightfn[type])();
}

static Light *makelight_pt(void)
{
    Light *lp;

    lp = emalloc(sizeof(Pointlight));
    lp->illuminate = illum_pt;
    return lp;
}

static Light *makelight_amb(void)
{
    Light *lp;

    lp = emalloc(sizeof(Ambientlight));
    lp->illuminate = illum_amb;
    return lp;
}

static void illum_pt(Light *light, Ray *ray, Hit *hit, vec3 out)
{
    Pointlight *lp;
    vec3 x, l;
    Ray sray;
    Hit srhit;
    float r, gfactor;

    lp = (Pointlight *) light;

    evalray(ray, hit->t, x);
    subvec3(lp->p, x, l);
    r = normvec3(l);
    scalevec3(1 / r, l); /* unit vector */

    /* determine if shading p is in shadow */
    setray(x, l, &sray);
    hitscene(&sray, EPS, r, &srhit);
    if (srhit.t < INF) { /* hit object; light is blocked */
        copystdvec3(VEC3ZERO, out);
    } else {
        gfactor = max(dotvec3(hit->n, l), 0) / (r * r);
        setscalevec3(gfactor, lp->intensity, out);
    }
}

static void illum_amb(Light *light, Ray *ray, Hit *hit, vec3 out)
{
    Ambientlight *al;

    al = (Ambientlight *) light;

    setscalevec3(1, al->intensity, out);
}
