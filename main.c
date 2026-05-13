#include "game.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int discs = 3;

    if(argc == 2) {
        int discArg = atoi(argv[1]);
        discs = discArg < MIN_DISCS? MIN_DISCS : discArg > MAX_DISCS? MAX_DISCS : discArg; 
    }
    
    InitGame(discs);
    LoopGame();
    EndGame();
}