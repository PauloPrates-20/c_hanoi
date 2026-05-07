#ifndef DISC_H
#define DISC_H

#include "raylib.h"

#define DISC_HEIGHT 20
#define BASE_DISC_WIDTH 30
#define MAX_DISCS 7

typedef struct Column Column;

typedef struct Disc {
    Color color;
    Vector2 pos;
    int size;
    Column *col;
    bool active;
} Disc;

void RenderDisc(Disc *self);
bool MoveDisc(Disc *self, Column *col);
Disc* MakeDisc(int size, int x, int y, Color color, Column *col);

extern Color discColors[MAX_DISCS];

#endif // DISC_H
