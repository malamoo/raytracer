#define NELEMS(array) (sizeof(array) / sizeof((array)[0]))

typedef unsigned char uchar;
typedef unsigned int uint;

void eprintf(char *fmt, ...);
void *emalloc(size_t n);