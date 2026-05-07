#include "disc.h"
#include <stdlib.h>
#include "column.h"

Color discColors[MAX_DISCS] = {RED, GREEN, BLUE, YELLOW, PURPLE, ORANGE, MAGENTA};

Disc* MakeDisc(int size, int x, int y, Color color, Column *col) {
    Disc *disc = malloc(sizeof(Disc));

    disc->col = col;
    disc->color = color;
    disc->pos = (Vector2){.x = x, .y = y};
    disc->size = size + 1;

    return disc;
}

void MoveDisc(Disc *self, Column *col) {
    // TODO
}

void RenderDisc(Disc *self) {
    DrawRectangle(self->pos.x - (BASE_DISC_WIDTH*self->size)/2 + COL_WIDTH/2, self->pos.y, BASE_DISC_WIDTH*self->size, DISC_HEIGHT, self->color);
}