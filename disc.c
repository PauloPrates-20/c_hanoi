#include "disc.h"
#include <stdlib.h>
#include "column.h"
#include "discstack.h"

Color discColors[MAX_DISCS] = {RED, GREEN, BLUE, YELLOW, PURPLE, ORANGE, MAGENTA};

Disc* MakeDisc(int size, int x, int y, Color color, Column *col) {
    Disc *disc = malloc(sizeof(Disc));

    disc->col = col;
    disc->color = color;
    disc->pos = (Vector2){.x = x, .y = y};
    disc->size = size + 1;
    disc->active = false;

    return disc;
}

bool MoveDisc(Disc *self, Column *col) {
    if(self->col != col) {
        if(DiscStackEmpty(col->discs)) {
            UnstackDisc(self->col->discs);
            StackDisc(self, col->discs);
            self->col = col;
            self->pos.x = col->pos.x;
            self->pos.y = SCREEN_HEIGHT - BOTTOM_OFFSET - DISC_HEIGHT;

            return true;
        } else if(DiscStackTop(col->discs)->size > self->size) {
            UnstackDisc(self->col->discs);
            self->pos.y = DiscStackTop(col->discs)->pos.y - DISC_HEIGHT;
            StackDisc(self, col->discs);
            self->col = col;
            self->pos.x = col->pos.x;

            return true;
        }
    }

    return false;
}

void RenderDisc(Disc *self) {
    int y = self->active? self->pos.y - 20 : self->pos.y;
    DrawRectangle(self->pos.x - (BASE_DISC_WIDTH*self->size)/2 + COL_WIDTH/2, y, BASE_DISC_WIDTH*self->size, DISC_HEIGHT, self->color);
}