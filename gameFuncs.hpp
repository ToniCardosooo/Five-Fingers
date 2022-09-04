#include <iostream>

// player struct
typedef struct{
    int right_hand = 1, left_hand = 1;
} PLAYER;


// functions declaration for main.cpp
void switchPlayerTurn(int &p_turn);
void playTurn(PLAYER *p0, PLAYER *p1, int *p_turn);
bool gameEnded(PLAYER &p0, PLAYER &p1);