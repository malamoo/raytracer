#include <stdlib.h>
#include "program.h"

List *makelistitem(void *data)
{
    List *newp;

    newp = (List *) emalloc(sizeof(List));
    newp->data = data;
    newp->next = NULL;
    return newp;
}

List *addfrontlist(List *listp, List *newp)
{
    newp->next = listp;
    return newp;
}

List *addendlist(List *listp, List *newp)
{
    List *p;

    if (listp == NULL)
        return newp;
    for (p = listp; p->next != NULL; p = p->next)
        ;
    p->next = newp;
    return listp;
}

List *dellistitem(List *listp, int (*cmp)(List *, void *), void *data)
{
    List *p, *prev;

    prev = NULL;
    for (p = listp; p != NULL; p = p->next) {
        if (cmp(listp, data) == 0) {
            if (prev == NULL)
                listp = p->next;
            else
                prev->next = p->next;
            free(p);
            return listp;
        }
        prev = p;
    }
    eprintf("item not in list");
    return NULL;
}

List *lookuplist(List *listp, int (*cmp)(List *, void *), void *data)
{
    for (; listp != NULL; listp = listp->next)
        if (cmp(listp, data) == 0)
            return listp;
    return NULL;
}

void applylist(List *listp, void (*fn)(List *, void *), void *arg)
{
    for (; listp != NULL; listp = listp->next)
        (*fn)(listp, arg);
}

void freealllist(List *listp)
{
    List *next;

    for (; listp != NULL; listp = next) {
        next = listp->next;
        free(listp);
    }
}
