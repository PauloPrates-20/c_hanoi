#include "discstack.h"
#include <stdlib.h>

DiscStack CreateDiscStack(int max) {
    DiscStack ds = malloc(sizeof(struct DiscStack));
    ds->max = max;
    ds->last = -1;
    ds->items = malloc(sizeof(Disc*)*max);

    return ds;
}

bool DiscStackEmpty(DiscStack ds) {
    return ds->last == -1;
}

bool DiscStackFull(DiscStack ds) {
    return ds->last == ds->max - 1;
}

void StackDisc(Disc *d, DiscStack ds) {
    if(DiscStackFull(ds)) abort();
    ds->last++;
    ds->items[ds->last] = d;
}

Disc* UnstackDisc(DiscStack ds) {
    if(DiscStackEmpty(ds)) abort();
    Disc *d = ds->items[ds->last];
    ds->last--;

    return d;
}

Disc* DiscStackTop(DiscStack ds) {
    if(DiscStackEmpty(ds)) abort();
    return ds->items[ds->last];
}