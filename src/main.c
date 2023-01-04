#include <stdlib.h>
#include <math.h>
#include "program.h"
#include "gfxmath.h"
#include "image.h"
#include "raytracer.h"

typedef struct Basis Basis;
typedef struct Coordframe Coordframe;

enum {
    FOV = 90,   /* vertical field of view */
    MAXREFL = 1 /* maximum number of reflections when shading rays */
};

struct Basis {
    vec3 u;
    vec3 v;
    vec3 w;
};

struct Coordframe {
    vec3 p;
    Basis basis;
};

static void setcamframe(vec3 eye, vec3 viewdir, Coordframe *out);
static void setorthobasis(vec3 a, vec3 b, Basis *out);
static void transformpt(Coordframe *frame, vec3 a, vec3 out);
static void transformdir(Coordframe *frame, vec3 a, vec3 out);
static void shaderay(Ray *ray, float t0, float t1, int nrefl, vec3 out);
static void setpixel(vec3 color, Rgb *rgb);
static Scene *makescene(void);

static Scene *scene; /* rendered scene */
static image img;    /* raster image to render to */

int main(void)
{
    vec3 eye, viewdir;
    Coordframe camframe;
    Ray ray;
    vec3 color;
    int i, j;
    float u, v, dist;
    float r, l, t, b;

    setvec3(0, 200, 300, eye);
    setvec3(0, sin(rad(-10)), -cos(rad(-15)), viewdir);
    setcamframe(eye, viewdir, &camframe);

    /* calculate image dimensions */
    r = IMGWIDTH / 2.0f;
    l = -r;
    t = IMGHEIGHT / 2.0f;
    b = -t;
    dist = IMGHEIGHT / 2.0f / tan(rad(FOV / 2.0f));

    for (i = 0; i < IMGHEIGHT; i++) {
        for (j = 0; j < IMGWIDTH; j++) {
            /* calculate pixel grid coords within image */
            u = l + (r - l) * (j + 0.5f) / IMGWIDTH;
            v = b + (t - b) * (i + 0.5f) / IMGHEIGHT;
            /* get ray in global coordinates */
            copystdvec3(VEC3ZERO, ray.origin);
            setvec3(u, v, -dist, ray.dir);
            transformpt(&camframe, ray.origin, ray.origin);
            transformdir(&camframe, ray.dir, ray.dir);
            shaderay(&ray, 0, INF, 0, color);
            setpixel(color, &img[i][j]);
        }
    }

    writebmpimage("scene.bmp", img);

    return 0;
}

void hitscene(Ray *ray, float t0, float t1, Hit *out)
{
    Hit hit, minhit;
    List *listp;
    Surface *surfp;

    if (scene == NULL)
        scene = makescene();

    minhit.t = INF;
    for (listp = scene->surflist; listp != NULL; listp = listp->next) {
        surfp = listp->data;
        surfp->hit(surfp, ray, t0, t1, &hit);
        if (hit.t < INF) { /* closest hit so far */
            t1 = hit.t;
            minhit = hit;
        }
    }
    *out = minhit;
}

static void shaderay(Ray *ray, float t0, float t1, int nrefl, vec3 out)
{
    Hit hit;
    List *listp;
    Light *lightp;
    vec3 color, total;
    vec3 p, r;
    Ray reflray;

    if (nrefl > MAXREFL)
        return;

    if (nrefl == 0) /* set background color */
        copystdvec3(VEC3BLACK, out);

    hitscene(ray, t0, t1, &hit);
    if (hit.t == INF)
        return;

    /* add illumination from all lights in scene */
    copystdvec3(VEC3BLACK, total);
    for (listp = scene->lightlist; listp != NULL; listp = listp->next) {
        lightp = listp->data;
        lightp->illuminate(lightp, ray, &hit, color);
        addvec3(color, total, total);
    }

    /* add illumination from reflections */
    reflectvec3(ray->dir, hit.n, r);
    evalray(ray, hit.t, p);
    setray(p, r, &reflray);
    shaderay(&reflray, EPS, INF, ++nrefl, total);
    addvec3(total, out, out);
}

static void setorthobasis(vec3 a, vec3 b, Basis *out)
{
    setnormalizedvec3(a, out->w);
    crossvec3(b, out->w, out->u);
    normalizevec3(out->u);
    crossvec3(out->w, out->u, out->v);
}

static void setcamframe(vec3 eye, vec3 viewdir, Coordframe *out)
{
    vec3 up, negvd;

    copystdvec3(VEC3UP, up);
    setnegvec3(viewdir, negvd);
    setorthobasis(negvd, up, &out->basis);
    copyvec3(eye, out->p);
}

static void transformpt(Coordframe *frame, vec3 a, vec3 out)
{
    transformdir(frame, a, out);
    addvec3(frame->p, out, out);
}

static void transformdir(Coordframe *frame, vec3 a, vec3 out)
{
    vec3 u, v;
    Basis *bp;

    bp = &frame->basis;
    setscalevec3(a[0], bp->u, u);
    setscalevec3(a[1], bp->v, v);
    setscalevec3(a[2], bp->w, out);
    addaddvec3(u, v, out);
}

static void setpixel(vec3 color, Rgb *rgb)
{
    /* quantize RGB levels */
    rgb->r = clamp(color[0], 0, 1) * 255;
    rgb->g = clamp(color[1], 0, 1) * 255;
    rgb->b = clamp(color[2], 0, 1) * 255;
}

static Scene *makescene(void)
{
    Scene *scp;
    Sphere *sp;
    Plane *pp;
    Pointlight *ptlp;
    Ambientlight *amblp;

    scp = emalloc(sizeof(Scene));
    scp->surflist = NULL;
    scp->lightlist = NULL;

    sp = (Sphere *) makesurf(SPHERE);
    setvec3(-250, 175, -350, sp->center);
    sp->radius = 175;
    scp->surflist = addfrontlist(scp->surflist, makelistitem(sp));

    sp = (Sphere *) makesurf(SPHERE);
    setvec3(50, 100, -100, sp->center);
    sp->radius = 100;
    scp->surflist = addfrontlist(scp->surflist, makelistitem(sp));

    pp = (Plane *) makesurf(PLANE);
    copystdvec3(VEC3ZERO, pp->p);
    copystdvec3(VEC3UP, pp->n);
    scp->surflist = addfrontlist(scp->surflist, makelistitem(pp));

    ptlp = (Pointlight *) makelight(PTLIGHT);
    copystdvec3(VEC3RED, ptlp->intensity);
    scalevec3(5000, ptlp->intensity);
    setvec3(300, 250, -50, ptlp->p);
    scp->lightlist = addfrontlist(scp->lightlist, makelistitem(ptlp));

    ptlp = (Pointlight *) makelight(PTLIGHT);
    copystdvec3(VEC3CYAN, ptlp->intensity);
    scalevec3(5000, ptlp->intensity);
    setvec3(-200, 225, 0, ptlp->p);
    scp->lightlist = addfrontlist(scp->lightlist, makelistitem(ptlp));

    ptlp = (Pointlight *) makelight(PTLIGHT);
    copystdvec3(VEC3RED, ptlp->intensity);
    scalevec3(15000, ptlp->intensity);
    setvec3(100, 500, -280, ptlp->p);
    scp->lightlist = addfrontlist(scp->lightlist, makelistitem(ptlp));

    amblp = (Ambientlight *) makelight(AMBLIGHT);
    copystdvec3(VEC3WHITE, amblp->intensity);
    scalevec3(0.0275f, amblp->intensity);
    scp->lightlist = addfrontlist(scp->lightlist, makelistitem(amblp));

    return scp;
}
