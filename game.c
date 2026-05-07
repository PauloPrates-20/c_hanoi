#include "game.h"
#include "column.h"
#include "disc.h"
#include "discstack.h"
#include <stdlib.h>
#include <math.h>

Game *game = NULL;

void InitGame() {
    game = malloc(sizeof(Game));

    game->disc_count = 3;
    game->min_moves = pow(2.0, (double)game->disc_count) - 1;
    game->finished = false;
    game->cols = malloc(sizeof(Column*)*COL_COUNT);
    game->discs = malloc(sizeof(Disc*)*game->disc_count);

    for(ColTypes i = SOURCE; i < COL_COUNT; i++) {
        int x = SIDE_GAPS + (COL_WIDTH + COL_GAP)*i;
        int y = SCREEN_HEIGHT - BOTTOM_OFFSET - COL_HEIGHT;
        game->cols[i] = MakeColumn(x, y, i);
        game->cols[i]->discs = CreateDiscStack(game->disc_count);
    }

    for(int i = 0; i < game->disc_count; i++) {
        int x = game->cols[SOURCE]->pos.x;
        int y = game->cols[SOURCE]->pos.y + COL_HEIGHT - (DISC_HEIGHT*(game->disc_count - i));

        game->discs[i] = MakeDisc(i, x, y, discColors[i], game->cols[SOURCE]);
    }

    for(int i = game->disc_count - 1; i >= 0; i--) {
        StackDisc(game->discs[i], game->cols[SOURCE]->discs);
    }

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hanoi");
    SetTargetFPS(TARGET_FPS);
}

void LoopGame() {
    while(!WindowShouldClose()) {
        RenderGame();
    }
}

void RenderGame() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(0, SCREEN_HEIGHT - BOTTOM_OFFSET, SCREEN_WIDTH, BOTTOM_OFFSET, BROWN);

    for(ColTypes i = SOURCE; i < COL_COUNT; i++) {
        RenderColumn(game->cols[i]);
    }

    for(int i = 0; i < game->disc_count; i++) {
        RenderDisc(game->discs[i]);
    }

    EndDrawing();
}

void EndGame() {
    CloseWindow();

    for(int i = 0; i < game->disc_count; i++) {
        free(game->discs[i]);
    }
    free(game->discs);

    for(ColTypes i = SOURCE; i < COL_COUNT; i++) {
        free(game->cols[i]);
    }
    free(game->cols);

    free(game);
}