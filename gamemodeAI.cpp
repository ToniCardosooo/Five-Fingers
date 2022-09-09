#include <vector>

#include "gameFuncs.hpp"

// to creat a copy of the state passed as argument
GameState copyState(GameState *state){

    GameState copy = { {state->human.left_hand, state->human.right_hand}, {state->ai.left_hand, state->ai.right_hand}, state->turn};

    return copy;
}


// checks if play is valid
bool playIsValid(GameState *state, string &play){

    // if it's an AI play
    if (state->turn == 1){

        if (play == "LL" && (state->ai.left_hand == 0 || state->human.left_hand == 0)) return false;
        else if (play == "RL" && (state->ai.right_hand == 0 || state->human.left_hand == 0)) return false;
        else if (play == "LR" && (state->ai.left_hand == 0 || state->human.right_hand == 0)) return false;
        else if (play == "RR" && (state->ai.right_hand == 0 || state->human.right_hand == 0)) return false;

    }
    // if it's a Human play
    else{

        if (play == "LL" && (state->human.left_hand == 0 || state->ai.left_hand == 0)) return false;
        else if (play == "RL" && (state->human.right_hand == 0 || state->ai.left_hand == 0)) return false;
        else if (play == "LR" && (state->human.left_hand == 0 || state->ai.right_hand == 0)) return false;
        else if (play == "RR" && (state->human.right_hand == 0 || state->ai.right_hand == 0)) return false;


    }
    
    return true;
}


// executes the AI play, given a string "XY"
// X is the AI hand
// Y is the Human hand
void playAI(GameState *state, string &play){

    if (play == "LL") state->human.left_hand = (state->human.left_hand + state->ai.left_hand) % 5;
    else if (play == "LR") state->human.right_hand = (state->human.right_hand + state->ai.left_hand) % 5;
    else if (play == "RL") state->human.left_hand = (state->human.left_hand + state->ai.right_hand) % 5;
    else if (play == "RR") state->human.right_hand = (state->human.right_hand + state->ai.right_hand) % 5;

    // in a distribute play, we will assume all distrubutions are equal
    else if (play == "D"){

        int sum = state->ai.left_hand + state->ai.right_hand;
        state->ai.left_hand = sum / 2;
        state->ai.right_hand = sum / 2;

        if (sum % 2 != 0) state->ai.left_hand++;

    }

    state->parent_play = play;

}


// is basically a copy of playAI(), but for the human, for minimax purposes
void playHuman(GameState *state, string &play){

    if (play == "LL") state->ai.left_hand = (state->ai.left_hand + state->human.left_hand) % 5;
    else if (play == "LR") state->ai.right_hand = (state->ai.right_hand + state->human.left_hand) % 5;
    else if (play == "RL") state->ai.left_hand = (state->ai.left_hand + state->human.right_hand) % 5;
    else if (play == "RR") state->ai.right_hand = (state->ai.right_hand + state->human.right_hand) % 5;

    // in a distribute play, we will assume all distrubutions are equal
    else if (play == "D"){

        int sum = state->human.left_hand + state->human.right_hand;
        state->human.left_hand = sum / 2;
        state->human.right_hand = sum / 2;

        if (sum % 2 != 0) state->human.left_hand++;

    }

    state->parent_play = play;

}


// creates the children states of the state given as argument
vector<GameState *> createChildren(GameState *state, vector<GameState *> &collector){

    vector<GameState *> children;

    string moves[5] = {"LL", "LR", "RL", "RR", "D"};
    for (int i = 0; i < 5; i++){
        
        // create the child and add it to the vector if it is valid
        if (playIsValid(state, moves[i])){
            
            // reserve memory space for the child state
            GameState *new_state = new GameState;
            *new_state = copyState(state);

            if (state->turn == 0) playHuman(new_state, moves[i]);
            else playAI(new_state, moves[i]);

            if ( !gameEnded(new_state->human, new_state->ai) ) switchPlayerTurn(new_state->turn);

            // save the parent state in the child
            new_state->parent_state = state;

            // save in collector
            collector.push_back(new_state);

            // save in children
            children.push_back(new_state);

        }

    }

    return children;

}


// copies the 2nd MinimaxResult struct given as argument to the 1st one
void copyMinimaxResult(MinimaxResult *first, MinimaxResult *second){

    first->state = second->state;
    first->depth = second->depth;
    first->evaluation = second->evaluation;

}


// heuristic / evaluation function
// returns a struct MinimaxResult with the evaluated state, its depth and evaluation
MinimaxResult heuristicFunc(GameState *state, int const &_depth){

    MinimaxResult result;

    result.state = *state;
    result.depth = _depth;

    GameState &_state = result.state;

    // evaluations starts here
    double eval = 0;

    // if the game ended and victorius, eval increases by a large amount
    if (gameEnded(_state.human, _state.ai)) eval += 10;

    // if the opponent has a closed hand, eval increases; if current play has a hand closed, eval descreases
    // if the next turn it's the opponent's turn, for every possible attack if there's a hand of the player that can be closed, eval decreases
    // if it's the player's turn and same scenario occurs against the opponent, eval increases for each possibility

    // AI case
    if (_state.turn == 1){

        if (_state.human.left_hand * _state.human.right_hand == 0) eval += 1;

        string moves[4] = {"LL", "LR", "RL", "RR"};
        for (int i = 0; i < 4; i++){
        
            if (playIsValid(&_state, moves[i])){

                GameState *new_state = new GameState;
                *new_state = copyState(&_state);
                playAI(new_state, moves[i]);

                if (new_state->human.left_hand * new_state->human.right_hand == 0) eval += 0.5;

                delete new_state;

            }

        }

    }
    // Human case
    else if (_state.turn == 0){

        if (_state.ai.left_hand * _state.ai.right_hand == 0) eval += 1;

        string moves[4] = {"LL", "LR", "RL", "RR"};
        for (int i = 0; i < 4; i++){
        
            if (playIsValid(&_state, moves[i])){

                GameState *new_state = new GameState;
                *new_state = copyState(&_state);
                playHuman(new_state, moves[i]);

                if (new_state->ai.left_hand * new_state->ai.right_hand == 0) eval += 0.5;

                delete new_state;

            }

        }

    }

    result.evaluation = eval;

    return result;
}




MinimaxResult minimaxAB(GameState *state, int depth, int const &max_depth, bool isMaximizingPlayer, double alpha, double beta, vector<GameState *> &collector){

    // create children of current state
    vector<GameState *> children = createChildren(state, collector);

    // if state is final or is at the max depth
    if (children.size() == 0 || depth == max_depth){

        return heuristicFunc(state, depth);

    }

    // if it's AI playing
    if (isMaximizingPlayer){

        MinimaxResult bestPlay; bestPlay.evaluation = -1000;
        for (int i = 0; i < children.size(); i++){

            MinimaxResult play = minimaxAB(children[i], depth+1, max_depth, false, alpha, beta, collector);
            
            if (play.evaluation > bestPlay.evaluation) copyMinimaxResult(&bestPlay, &play);
            alpha = max(alpha, bestPlay.evaluation);

            if (beta <= alpha) break;

        } 

        return bestPlay;

    }

    // if it's Human playing
    else{

        MinimaxResult bestPlay; bestPlay.evaluation = 1000;
        for (int i = 0; i < children.size(); i++){

            MinimaxResult play = minimaxAB(children[i], depth+1, max_depth, true, alpha, beta, collector);
            
            if (play.evaluation < bestPlay.evaluation) copyMinimaxResult(&bestPlay, &play);
            beta = min(beta, bestPlay.evaluation);

            if (beta <= alpha) break;

        } 

        return bestPlay;

    }

}


// back propagates from the leaf state obtained in Minimax to the state which would result from the AI move
GameState backPropagateIntoPlay(MinimaxResult *result){

    GameState ai_play = result->state;

    // back propagate into the state made by the calculated play
    for (int i = 0; i < result->depth - 1; i++){

        ai_play = *(ai_play.parent_state);

    }

    return ai_play;
}


// to check if two states are equal
bool equalStates(GameState *s1, GameState *s2){

    bool ai = (s1->ai.left_hand == s2->ai.left_hand) && (s1->ai.right_hand == s2->ai.right_hand);
    bool human = (s1->human.left_hand == s2->human.left_hand) && (s1->human.right_hand == s2->human.right_hand);
    bool turn = s1->turn == s2->turn;

    if (ai && human && turn) return true;
    else return false;

}


// to delete from memory all the children states that didnt make into the AI move
void emptyCollector(vector<GameState *> &collector, GameState *ai_play){

    bool ai_state_saved = false;

    // iterate from the end
    // if a state is equal to the state made by the AI, dont delete it, pop it out
    for (int i = collector.size() - 1; i >= 0; i--){

        if (equalStates(collector[i], ai_play) && !ai_state_saved) {
            
            collector.pop_back();
            ai_state_saved = true;

        }
        else{
            
            delete collector[i];
            collector.pop_back();

        }

    }

}


// function that will return the move to play by the AI, calculated in the minimaxAB function
void executeMinimaxAB(GameState *state, vector<GameState* > &state_collector){

    int max_depth = 12;

    MinimaxResult result = minimaxAB(state, 0, max_depth, true, -1000, 1000, state_collector);

    GameState ai_play = backPropagateIntoPlay(&result);

    emptyCollector(state_collector, &ai_play);

    // alter the current state with the ai_play information
    state->human = ai_play.human;
    state->ai = ai_play.ai;
    state->parent_state = ai_play.parent_state;
    state->parent_play = ai_play.parent_play;

    if (state->parent_play == "LL") cout << "\nAI used Left hand against Human's Left Hand!\n";
    else if (state->parent_play == "LR") cout << "\nAI used Left hand against Human's Right Hand!\n";
    else if (state->parent_play == "RL") cout << "\nAI used Right hand against Human's Left Hand!\n";
    else if (state->parent_play == "RR") cout << "\nAI used Right hand against Human's Right Hand!\n";
    else if (state->parent_play == "D") cout << "\nAI distributed its fingers!\n";

}
