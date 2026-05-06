#include "column.h"
#include <stdlib.h>

Column* MakeColumn(int x, int y, ColTypes type) {
    Column *col = malloc(sizeof(Column));

    col->discs = NULL;
    col->last_disc = NULL;
    col->pos = (Vector2){.x = x, .y = y};
    col->type = type;

    return col;
}

bool ColIsEmpty(Column *self) {
    return self->last_disc == NULL;
}

void RenderColumn(Column *self) {
    DrawRectangle(self->pos.x, self->pos.y, COL_WIDTH, COL_HEIGHT, RED);
}