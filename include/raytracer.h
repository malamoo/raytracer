typedef struct Ray Ray;
typedef struct Hit Hit;
typedef struct Light Light;
typedef struct Pointlight Pointlight;
typedef struct Ambientlight Ambientlight;
typedef struct Surface Surface;
typedef struct Sphere Sphere;
typedef struct Plane Plane;
typedef struct Scene Scene;

enum { SPHERE,
       PLANE };

enum { PTLIGHT,
       AMBLIGHT };

struct Ray {
    vec3 origin;
    vec3 dir;
};

struct Light {
    void (*illuminate)(Light *, Ray *, Hit *, vec3);
};

struct Pointlight {
    Light light;
    vec3 intensity;
    vec3 p;
};

struct Ambientlight {
    Light light;
    vec3 intensity;
};

struct Surface {
    void (*hit)(Surface *, Ray *, float, float, Hit *);
};

struct Sphere {
    Surface surface;
    vec3 center;
    float radius;
};

struct Plane {
    Surface surface;
    vec3 p;
    vec3 n;
};

struct Hit {
    float t;
    vec3 n;
    Surface *surface;
};

struct Scene {
    List *surflist;
    List *lightlist;
};

void setray(vec3 origin, vec3 direction, Ray *out);
void evalray(Ray *ray, float t, vec3 out);
Light *makelight(int type);
Surface *makesurf(int type);
void hitscene(Ray *ray, float t0, float t1, Hit *out);

