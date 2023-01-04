typedef float vec3[3];

enum {
    VEC3ZERO,
    VEC3ONE,
    VEC3RIGHT,
    VEC3LEFT,
    VEC3UP,
    VEC3DOWN,
    VEC3BACK,
    VEC3FRONT,
    VEC3BLACK,
    VEC3RED,
    VEC3GREEN,
    VEC3BLUE,
    VEC3YELLOW,
    VEC3CYAN,
    VEC3MAGENTA,
    VEC3WHITE
};

extern const double PI;
extern const double INF;
extern const double EPS;

void copystdvec3(int std, vec3 out);
void copyvec3(vec3 a, vec3 out);
void setvec3(float x, float y, float z, vec3 out);
float normvec3(vec3 a);
void setnormalizedvec3(vec3 a, vec3 out);
void normalizevec3(vec3 out);
void setnegvec3(vec3 a, vec3 out);
void negvec3(vec3 out);
void setscalevec3(float k, vec3 a, vec3 out);
void scalevec3(float k, vec3 out);
void addvec3(vec3 a, vec3 b, vec3 out);
void addaddvec3(vec3 a, vec3 b, vec3 out);
void subvec3(vec3 a, vec3 b, vec3 out);
float dotvec3(vec3 a, vec3 b);
void crossvec3(vec3 a, vec3 b, vec3 out);
void reflectvec3(vec3 d, vec3 n, vec3 out);
float clamp(float x, float min, float max);
float max(float x, float max);
float min(float x, float min);
float rad(float deg);
