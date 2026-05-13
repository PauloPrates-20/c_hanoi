#ifndef GAME_H
#define GAME_H

#include "config.h"
#include "raylib.h"

typedef struct Disc Disc;
typedef struct Column Column;

typedef struct Game {
    int move_count;
    int min_moves;
    Disc **discs;
    Disc *active;
    Column **cols;
    int disc_count;
    bool finished;
} Game;

void InitGame(int discs);
void EndGame();
void RenderGame();
void LoopGame();

#endif // GAME_H