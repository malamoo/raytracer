typedef float vec3[3];
typedef struct Cframe Cframe;
typedef struct Ray Ray;

struct Cframe {
    vec3 e;
    vec3 u;
    vec3 v;
    vec3 w;
};

struct Ray {
    vec3 o;
    vec3 d;
};

float vec3len(vec3 a);
void vec3norm(vec3 a, vec3 vec);
void vec3neg(vec3 a, vec3 vec);
void vec3scale(float k, vec3 a, vec3 vec);
void vec3add(vec3 a, vec3 b, vec3 vec);
void vec3sub(vec3 a, vec3 b, vec3 vec);
void vec3up(vec3 vec);
float vec3dot(vec3 a, vec3 b);
void vec3cross(vec3 a, vec3 b, vec3 vec);
void vec3copy(vec3 a, vec3 vec);
void cframecamera(vec3 eye, vec3 viewdir, Cframe *framep);
void rayortho(float u, float v, Cframe *framep, Ray *rayp);
void rayeval(float t, Ray *rayp, vec3 vec);