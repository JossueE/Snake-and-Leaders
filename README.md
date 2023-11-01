# Snake and Leaders
The Snake and Ladder game is a team project that aims to demonstrate learning object-oriented programming. The game has a board where players move through the board by rolling a die and advancing the number of squares indicated on the die. The goal is to reach the final square before the other players, avoiding snake squares that cause players to move backward and aiming for ladder squares that advance them quickly.

## Requirements

- You need a C++ development environment to compile and run the game.
- Make sure you have the standard C++ libraries installed.

## Running the Game

Follow these steps to run the game:

1. Open the provided source code in your C++ development environment.

2. Compile the code to create the executable.

3. Run the resulting program.

## Game Rules

The game implemented in the code follows the basic rules of the Snake and Ladder game. Here is a general overview of the rules:

- The game is played on a board with numbered squares.
- Players roll a die to move through the board.
- Some squares are "snakes" that make the player move backward, while others are "ladders" that quickly advance the player.
- The goal is to reach the final square before the other players.

## Gameplay Instructions

The game will start by requesting parameters from the user: board size, number of snakes, number of ladders, number of players, penalty and reward points, and the maximum number of turns. After filling in these fields, the user has the option to play in two ways: automatic or manual. In each input that requires user text, I will indicate the necessary letters to proceed with the instruction, so there is no need to explain them in this document.

If the automatic mode is chosen, the user will be asked to confirm the maximum number of turns to play. After confirmation, the program will proceed to run a simulation of the entire game until one of the players wins or the maximum number of turns is reached.

If the manual game mode is chosen, the user will have to enter a character for each turn to proceed with the game. They have the option to continue the game, restart it, or end it at any time. Similarly, if a player wins or the maximum number of turns is reached, they will have the option to end the game or restart it with the same parameters given at the beginning.

Both ways use a Snake, Ladder and Normal class, which are tile classes that inherit their attributes from a Tile class, without overriding any of the methods. There is also the inheritance from the parent class Game Type, which includes a virtual function for the AutoGameType and ManualGameType to implement.

THANKS FOR PLAYING!!!
