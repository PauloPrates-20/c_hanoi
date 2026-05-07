#ifndef COLUMN_H
#define COLUMN_H

#include "raylib.h"
#include "config.h"

#define COL_WIDTH 10
#define COL_HEIGHT 200
#define SIDE_GAPS 100

typedef enum ColType {
    SOURCE,
    AUX,
    DEST,
} ColTypes;

struct DiscStack;

#define COL_COUNT 3
#define COL_GAP (SCREEN_WIDTH - (COL_WIDTH*COL_COUNT) - (SIDE_GAPS*2))/(COL_COUNT - 1)

typedef struct Disc Disc;

typedef struct Column {
    Vector2 pos;
    struct DiscStack *discs;
    ColTypes type;
} Column;

Column* MakeColumn(int x, int y, ColTypes type);
void RenderColumn(Column *self);
bool ColIsEmpty(Column *self);

#endif // COLUMN_H
