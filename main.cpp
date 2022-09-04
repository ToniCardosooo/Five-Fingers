#include <time.h>

#include "gameFuncs.hpp"

int main(){

    // create players
    PLAYER p0, p1;

    // randomly choose which player starts the game
    srand(time(NULL));
    int p_turn = rand()%2;

    // run the game
    bool running = true;
    while (running){

        playTurn(&p0, &p1, &p_turn);

        if (gameEnded(p0, p1)) running = false;
        else switchPlayerTurn(p_turn);

    }

    std::cout << "\nPlayer " << p_turn + 1 << " won the game!\n";

    return 0;
}