typedef struct Surface Surface;
typedef struct Sphere Sphere;
typedef struct Hit Hit;

enum { SPHERE };

struct Surface {
    uchar type;
    Rgb color;
    void *geometry;
};

struct Sphere {
    vec3 center;
    float radius;
};

struct Hit {
    Surface *surface;
    float t;
    vec3 n;
};

void hitscene(Ray *rayp, float t0, float t1, Hit *hitp);