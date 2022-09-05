# Five-Fingers
  
GAME RULES
- This is a 2 player game.
- Both players have one finger in each hand sticking out. The number of fingers drawn is represented on the command prompt during the game.
- In a player's turn, the player can perform 1 out of 2 possible actions:
  - With one hand, attack one of the opponent's hands, adding up your amount of fingers of your attacking to theirs on their stricken hand (the attacking player remains with the same amount of fingers in the attacking hand afterwards).
  - The player can distribute the total amout of fingers by both hands. For example, if a player has 4 fingers in one hand and 0 on the other, he can distribute them in 3-1 or 1-3, 2-2, or 0-4.
* When the sticken player gets 5 fingers in a hand, they must close their hands (represented by having 0 fingers).
- Players cannot attack closed hands (hands with 0 fingers).
- A player wins when the opponent has both hands closed (both hands have 0 fingers).
  
HOW TO RUN THE PROGRAM
- Install any C++ compiler in case you haven't got one already.
- Download all files into the same directory.
- Open command prompt / terminal and compile (g++ example) the files with the command 'g++ .\main.cpp .\gameFuncs.cpp -o FiveFingers'
- Type the command '.\FiveFingers', and the game will start on the command prompt / terminal.
  
Enjoy!  
(a game mode 'Human vs AI' might be developed later with Minimax A/B algorithm)  
(a graphical version of this project might be done in Python in the future)
