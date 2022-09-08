#include <iostream>
#include <vector>

using namespace std;

// player struct
typedef struct{

    int left_hand = 1, right_hand = 1;

} PLAYER;


// struct that will hold information of the current state of the game in 'Human vs AI' gamemode
struct game_state;

typedef struct game_state{

    PLAYER human, ai;
    int turn;
    game_state *parent_state;
    string parent_play;

} GameState;


// struct to store the result of the minimax algorithm
typedef struct{

    GameState state;
    int depth;
    double evaluation;

} MinimaxResult;


// functions declaration for main.cpp
void switchPlayerTurn(int &p_turn);
int chooseGameMode();
void displayGame(GameState *state, int const &gamemode);
void playTurn(GameState *state);
bool gameEnded(PLAYER &p0, PLAYER &p1);

// AI functions
void executeMinimaxAB(GameState *state, vector<GameState* > &state_collector);