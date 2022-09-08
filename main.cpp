#include <time.h>

#include "gameFuncs.hpp"

int main(){

    // select game mode
    int gamemode = chooseGameMode();

    // create initial game state
    GameState state;

    // if game mode is 'Human vs Human'
    if (gamemode == 1){

        // randomly choose which player starts the game
        srand(time(NULL));
        state.turn = rand()%2;

    }
    // if game mode is 'Human vs AI'
    else state.turn = 0;
    
    // run the game
    bool running = true;

    // game mode is 'Human vs Human'
    if (gamemode == 1){

        while (running){
        
            displayGame(&state, gamemode);
            playTurn(&state);

            if (gameEnded(state.human, state.ai)) running = false;
            else switchPlayerTurn(state.turn);

        }
        std::cout << "\nPlayer " << state.turn + 1 << " won the game!\n";
    }

    // if game mode is 'Human vs AI'
    else{
        
        while (running){

            displayGame(&state, gamemode);

            // if it is the Human turn
            if (state.turn == 0) playTurn(&state);

            // if it is the AI turn
            else executeMinimaxAB(&state);

            if (gameEnded(state.human, state.ai)) running = false;
            else switchPlayerTurn(state.turn);

        }

        if (state.turn == 0) cout << "\nHuman won the game!\n";
        else cout << "\nAI won the game!\n";
            
    }

    return 0;
}