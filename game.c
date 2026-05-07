#include "game.h"
#include "column.h"
#include "disc.h"
#include "discstack.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

Game *game = NULL;
char counter[20] = "";

Column* GetActiveCol(int x, int y) {
    for(ColTypes i = SOURCE; i < COL_COUNT; i++) {
        Column *col = game->cols[i];

        if(
            x >= col->pos.x - 20 &&
            x <= col->pos.x + 20 &&
            y <= SCREEN_HEIGHT - BOTTOM_OFFSET &&
            y >= col->pos.y
        ) {
            return col;
        }
    }

    return NULL;
}

void HandleClick() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int x = GetMouseX();
        int y = GetMouseY();

        Column *activeCol = GetActiveCol(x, y);
        
        if(activeCol != NULL) {
            if(game->active == NULL) {
                if(!DiscStackEmpty(activeCol->discs)) game->active = DiscStackTop(activeCol->discs);
            } else {
                if(MoveDisc(game->active, activeCol)) {
                    game->move_count++;
                    sprintf(counter, "MOVES: %d", game->move_count);
                }
                game->active = NULL;
            }
        } else {
            game->active = NULL;
        }
    }
}

void InitGame() {
    game = malloc(sizeof(Game));

    game->disc_count = 3;
    game->move_count = 0;
    game->min_moves = pow(2.0, (double)game->disc_count) - 1;
    game->finished = false;
    game->active = NULL;
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

    sprintf(counter, "MOVES: %d", game->move_count);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hanoi");
    SetTargetFPS(TARGET_FPS);
}

void LoopGame() {
    while(!WindowShouldClose()) {
        HandleClick();
        for(int i = 0; i < game->disc_count; i++) {
            game->discs[i]->active = false;
            if(game->discs[i] == game->active) {
                game->discs[i]->active = true;
            }
        }
        RenderGame();
    }
}

void RenderGame() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(0, SCREEN_HEIGHT - BOTTOM_OFFSET, SCREEN_WIDTH, BOTTOM_OFFSET, BROWN);

    DrawText(counter, (SCREEN_WIDTH - MeasureText(counter, 20))/2, 75, 20, BLACK);

    for(ColTypes i = SOURCE; i < COL_COUNT; i++) {
        RenderColumn(game->cols[i]);
    }

    for(int i = 0; i < game->disc_count; i++) {
        RenderDisc(game->discs[i]);
    }

    EndDrawing();
}

void EndGame() {
    for(int i = 0; i < game->disc_count; i++) {
        free(game->discs[i]);
    }
    free(game->discs);

    for(ColTypes i = SOURCE; i < COL_COUNT; i++) {
        free(game->cols[i]->discs->items);
        free(game->cols[i]->discs);
        free(game->cols[i]);
    }
    free(game->cols);

    free(game);

    CloseWindow();
}