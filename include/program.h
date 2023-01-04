#define NELEMS(array) (sizeof(array) / sizeof((array)[0]))

typedef unsigned char uchar;
typedef unsigned int uint;
typedef struct List List;

struct List {
    void *data;
    List *next;
};

List *makelistitem(void *data);
List *addfrontlist(List *listp, List *newp);
List *addendlist(List *listp, List *newp);
List *dellistitem(List *listp, int (*cmp)(List *, void *), void *data);
List *lookuplist(List *listp, int (*cmp)(List *, void *), void *data);
void applylist(List *listp, void (*fn)(List *, void *), void *arg);
void freealllist(List *listp);
void eprintf(char *fmt, ...);
void *emalloc(size_t n);
