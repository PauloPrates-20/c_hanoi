#ifndef DISC_H
#define DISC_H

#include "raylib.h"

#define DISC_HEIGHT 20
#define BASE_DISC_WIDTH 30

typedef struct Column Column;

typedef struct Disc {
    Color color;
    Vector2 pos;
    int size;
    Column *col;
} Disc;

void RenderDisc(Disc *self);
void MoveDisc(Disc *self, Column *col);
Disc* MakeDisc(int size, int x, int y, Color color, Column *col);

#endif // DISC_H
