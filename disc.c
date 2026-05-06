#include "disc.h"
#include <stdlib.h>
#include "column.h"

Disc* MakeDisc(int size, int x, int y, Color color, Column *col) {
    Disc *disc = malloc(sizeof(Disc));

    disc->col = col;
    disc->color = color;
    disc->pos = (Vector2){.x = x, .y = y};
    disc->size = size + 1;

    return disc;
}

void MoveDisc(Disc *self, Column *col) {
    if(ColIsEmpty(col)) {
        self->col = col;
        self->pos = col->pos;
    } else if(col->last_disc->size > self->size) {
        self->col = col;
        self->pos.x = col->pos.x;
        self->pos.y = col->last_disc->pos.y - DISC_HEIGHT;
    }
}

void RenderDisc(Disc *self) {
    DrawRectangle(self->pos.x - (BASE_DISC_WIDTH*self->size)/2 + COL_WIDTH/2, self->pos.y, BASE_DISC_WIDTH*self->size, DISC_HEIGHT, self->color);
}