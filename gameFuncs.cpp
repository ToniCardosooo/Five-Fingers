#include "gameFuncs.hpp"


// functions definition
void switchPlayerTurn(int &p_turn){

    p_turn = (p_turn + 1) % 2;

}


// ask which game mode to be played
int chooseGameMode(){

    int gamemode;
    cout << "Which game mode do you want to play?\n\t(1) Human vs Human\n\t(2) Human vs AI (minimax a/b algorithm)\n";
    cin >> gamemode;

    return gamemode;
}


// ask if player wants to "attack" (1) or distribute the fingers (2)
int chooseAction(){
    
    int action;

    cout << "ACTIONS:\n\t(1) Attack\n\t(2) Distribute the fingers\n";
    cin >> action;

    return action;
}


// distributes the fingers according to the user input
void distributeFingers(PLAYER *player){
    
    int limit = player->left_hand + player->right_hand;

    int new_right, new_left;
    cout << "Write the new number of fingers for each hand respectivelly (left then right), separated by a white space!\n";

    // iterate until the input is valid
    bool valid_input = false;
    while (!valid_input){

        cin >> new_left >> new_right;

        // there can't be negative inputs
        if (new_left < 0 || new_right < 0){
            cout << "You can't have negative fingers! Type again.\n";
            continue;
        }

        // sum of new inputs must be equal to the limit
        if (new_left + new_right != limit){
            cout << "You don't have the same total number of fingers! Type again.\n";
            continue;
        }

        // new values must not equal the old ones
        if (player->left_hand == new_left && player->right_hand == new_right){
            cout << "The finger's new distribution is the same as the previous! Type again.\n";
            continue;
        }

        // if all faulty conditions were skipped, then it's a valid input
        valid_input = true;
    }

    player->left_hand = new_left;
    player->right_hand = new_right;

}


// get the player's hand
char chooseHand(PLAYER *player, bool choosing_frist_hand = false){
    
    if (choosing_frist_hand) cout << "Which hand do you want to attack with? (type 'L' for Left Hand, or 'R' for Right Hand)\n";
    else cout << "Which of the opponent's hand do you want to attack? (type 'L' for Left Hand, or 'R' for Right Hand)\n";

    char hand = ' ';
    while (hand != 'R' && hand != 'L'){

        cin >> hand;
        
        // check if it's a valid input
        if (hand != 'R' && hand != 'L') cout << "Invalid choice! Choose again!\n";

        // check if the hand has at least a finger
        if ( (hand == 'R' && player->right_hand == 0) || (hand == 'L' && player->left_hand == 0) ){

            if (choosing_frist_hand) cout << "That hand is empty! Choose again!\n";
            else cout << "You can't play against an empty hand! Choose again!\n";
            
            hand = ' ';
        }
        
    }

    return hand;
}


// adds player hand's fingers to the oponent's hand
void addFingers(int &player_hand, int &opponent_hand){
    
    opponent_hand = (opponent_hand + player_hand) % 5;

}


// displays the number of fingers and turn
void displayGame(GameState *state, int const &gamemode){

    // if gamemode is 'Human vs Human'
    if (gamemode == 1){

        cout << "\nPlayer " << state->turn + 1 << " turn!" << "\n";
        cout << "-----------------------------" << "\n";
        cout << "Player 1 fingers: " << state->human.left_hand << " (L)\t" << state->human.right_hand << " (R)\n";
        cout << "Player 2 fingers: " << state->ai.left_hand << " (L)\t" << state->ai.right_hand << " (R)\n";

    }
    // if gamemode is 'Human vs AI' and it's the Human turn
    else {
        // Human turn
        if (state->turn == 0){

            cout << "\nHuman's turn!" << "\n";
            cout << "-----------------------------" << "\n";
            cout << "Human's fingers: " << state->human.left_hand << " (L)\t" << state->human.right_hand << " (R)\n";
            cout << "AI's fingers:    " << state->ai.left_hand << " (L)\t" << state->ai.right_hand << " (R)\n";

        }
        // AI turn
        else{
            
            cout << "\nAI's turn!" << "\n";
            cout << "-----------------------------" << "\n";
            cout << "Human's fingers: " << state->human.left_hand << " (L)\t" << state->human.right_hand << " (R)\n";
            cout << "AI's fingers:    " << state->ai.left_hand << " (L)\t" << state->ai.right_hand << " (R)\n";

        }

    }

}


void playTurn(GameState *state){

    PLAYER *player = &(state->human), *opponent = &(state->ai);
    if (state->turn == 1) player = &(state->ai), opponent = &(state->human);

    // show possible actions: "attack" and "distribute fingers", and ask for input
    int action = chooseAction();

    // if player chooses to attack
    if (action == 1){

        // get player's hand
        char p_hand = chooseHand(player, true);

        // get opponent's hand
        char opp_hand = chooseHand(opponent);

        // execute the play
        if (p_hand == 'L' && opp_hand == 'L') addFingers(player->left_hand, opponent->left_hand);
        else if (p_hand == 'L' && opp_hand == 'R') addFingers(player->left_hand, opponent->right_hand);
        else if (p_hand == 'R' && opp_hand == 'L') addFingers(player->right_hand, opponent->left_hand);
        else if (p_hand == 'R' && opp_hand == 'R') addFingers(player->right_hand, opponent->right_hand);

    }

    else distributeFingers(player);
    

}


// checks if the game has ended
bool gameEnded(PLAYER &p0, PLAYER &p1){

    if ( (p0.left_hand + p0.right_hand == 0) || (p1.left_hand + p1.right_hand == 0) ) return true;
    else return false;

}
