#ifndef DISCSTACK_H
#define DISCSTACK_H

#include "disc.h"

typedef struct DiscStack {
    int max;
    int last;
    Disc **items;
} *DiscStack;

DiscStack CreateDiscStack(int max);
bool DiscStackEmpty(DiscStack ds);
bool DiscStackFull(DiscStack ds);
void StackDisc(Disc *d, DiscStack ds);
Disc* UnstackDisc(DiscStack ds);
Disc* DiscStackTop(DiscStack ds);

#endif // DISCSTACK_H