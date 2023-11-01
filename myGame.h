#include <iostream>
//#include <cstdlib>
//#include <ctime>
#include <vector>
//#include <cctype>
//#include <algorithm>
#include <string>
#include <random>
#include "normal.h"
#include "ladder.h"
#include "snake.h"

class MyGame {
private:
    int cTiles;
    int* tilesPtr;
    int cSnakes;
    int* snakesPtr;
    int cLadders;
    int* laddersPtr;
    int cPenalty;
    int* penaltyPtr;
    int cReward;
    int* rewardPtr;
    int maxTurns;
    int* turnsPtr;
    int cPlayer; 
    int *playerPtr; 
    int i;
    int j;
 

    std::vector<char> board;

    std::vector<int> snakeSquares;
    std::vector<int> ladderSquares;
    std::vector<int> playerPositions;
    int currentPlayer;
    int turn;
    bool winnerStat;
    bool turnStat;
    int num;
    int lastTile; 
    int playerCounter; 

public:
    MyGame();
    int rollDice();
    void createBoard();
    void nextTurn();
    char getPositionType(int);
    void start();
    void resetGame();
    bool getWinnerStat();

};

class GameType {
public:
    virtual void nextTurn(MyGame& game) = 0;
};

class AutoGameType : public GameType {
public:
    int maxturn_auto;
    int maxturn_auto_initial=1;
    
    void nextTurn(MyGame& game) override {
        std::cout << "Confirm the maximum turns to play ";
        std::cin >> maxturn_auto;
        while (maxturn_auto_initial != maxturn_auto && game.getWinnerStat() == false)
        {
            game.nextTurn();
            maxturn_auto_initial++;
        }

         if(game.getWinnerStat() == false){
          game.nextTurn();
        }
        
    }
};

class ManualGameType : public GameType {
public:
    void nextTurn(MyGame& game) override {
        char choice;
        std::cout << "Press C to CONTINUE next turn, or E to END the game: ";
        std::cin >> choice;

        while (choice != 'C' && choice != 'E') {
            std::cout << "Invalid option. Press C to continue next turn or E to end the game: ";
            std::cin >> choice;
        }

        if (choice == 'C') {
            game.nextTurn();
        }
    }
};


MyGame::MyGame() {
    std::cout << "Tiles: " << std::endl;  //User assigns number of Tiles
    std::cin >> cTiles;
    tilesPtr = &cTiles;

    std::cout << "Snakes: " << std::endl;  //User assigns number of snake tiles
    std::cin >> cSnakes;
    snakesPtr = &cSnakes;

    std::cout << "Ladders: " << std::endl;  //User assigns number of ladder tiles
    std::cin >> cLadders;
    laddersPtr = &cLadders;

    std::cout << "Penalty: " << std::endl;  //User assigns value of Penalty
    std::cin >> cPenalty;
    penaltyPtr = &cPenalty;

    std::cout << "Reward: " << std::endl;  //User assigns value of Reward
    std::cin >> cReward;
    rewardPtr = &cReward;

    std::cout << "Number of players: " << std::endl;  //User assigns value of Reward
    std::cin >> cPlayer;
    playerPtr = &cPlayer;
    
    std::cout << "Max turns: " << std::endl;  //User assigns value of Turns
    std::cin >> maxTurns;
    turnsPtr = &maxTurns;
    lastTile = (*tilesPtr - *penaltyPtr) - *rewardPtr;

    // Initialize snake squares
    snakeSquares.resize(*snakesPtr);
    bool same = false;
    num = 0;
    for (int i = 0; i < *snakesPtr; i++) {
        for (int j = 0; j < *snakesPtr; j++) {
            if (snakeSquares[j] == num) {
                same = true;
                break;
            }
        }

        while (same == true) {
            num = *penaltyPtr + (rand() % lastTile);
            same = false;
            for (int j = 0; j < *snakesPtr; j++) {
                if (snakeSquares[j] == num) {
                    same = true;
                    break;
                }
            }
        }

        snakeSquares[i] = num;
    }

    // Initialize ladder squares
    ladderSquares.resize(*laddersPtr);
    same = false;
    num = *penaltyPtr + (rand() % lastTile);
    for (int i = 0; i < *laddersPtr; i++) {
        for (int j = 0; j < *snakesPtr; j++) {
            if (snakeSquares[j] == num) {
                same = true;
                break;
            }
        }
        for (int j = 0; j < *laddersPtr; j++) {
            if (ladderSquares[j] == num) {
                same = true;
                break;
            }
        }

        while (same == true) {
            num = *penaltyPtr + (rand() % lastTile);
            same = false;
            for (int j = 0; j < *snakesPtr; j++) {
                if (snakeSquares[j] == num) {
                    same = true;
                    break;
                }
            }
            for (int j = 0; j < *laddersPtr; j++) {
                if (ladderSquares[j] == num) {
                    same = true;
                    break;
                }
            }
        }

        ladderSquares[i] = num;
    }

    // Initialize player positions
    playerPositions.resize(*playerPtr, 1);
    currentPlayer = 1;
    turn = 1;
    winnerStat = false;
    turnStat = false;
}

bool MyGame::getWinnerStat(){
  return winnerStat; 
}

int MyGame::rollDice() {
    return rand() % 6 + 1;
}

void MyGame::createBoard() {
    std::cout << "Game Board: " << std::endl;
    std::cout << "-----------" << std::endl;

    for (int i = 0; i < board.size(); i++) {
        std::cout << "| " << board[i] << " ";

        if ((i + 1) % 10 == 0) {
            std::cout << "|" << std::endl;
            std::cout << "-----------" << std::endl;
        }
    }

    std::cout << std::endl;
}

void MyGame::nextTurn() {
    std::cout << turn << " " << currentPlayer << " " << playerPositions[currentPlayer - 1] << " ";

    int diceRoll = rollDice();
    std::cout << diceRoll << " ";

    int newPosition = playerPositions[currentPlayer - 1] + diceRoll;

    if (newPosition > *tilesPtr) {
        newPosition = *tilesPtr;
    }

    std::cout << getPositionType(newPosition) << " ";

    if (getPositionType(newPosition) == 'S') {
        newPosition -= *penaltyPtr;
    } else if (getPositionType(newPosition) == 'L') {
        newPosition += *rewardPtr;
    }

    playerPositions[currentPlayer - 1] = newPosition;

    std::cout << playerPositions[currentPlayer - 1] << std::endl;

    if (playerPositions[currentPlayer - 1] >= *tilesPtr) {
        winnerStat = true;
        std::cout << "-- GAME OVER --" << std::endl;
        std::cout << "Player " << currentPlayer << " is the winner!!!" << std::endl;
    }

    if (turn >= *turnsPtr) {
        turnStat = true;
        std::cout << "-- GAME OVER --" << std::endl;
        std::cout << "The maximum number of turns has been reached..." << std::endl;
    }

    if (currentPlayer > *playerPtr -1){
    currentPlayer = 0; 
  }

      ++turn;
    ++currentPlayer; 
}

char MyGame::getPositionType(int position) {
    if (std::find(snakeSquares.begin(), snakeSquares.end(), position) != snakeSquares.end()) {
       Snake s; 
      return s.getType();
    } else if (std::find(ladderSquares.begin(), ladderSquares.end(), position) != ladderSquares.end()) {
      Ladder l; 
     return l.getType();
    } else {
      Normal n; 
      return n.getType(); 
    }
}

void MyGame::resetGame() {
    std::vector<int>playerPositions(*playerPtr, 1);
    currentPlayer = 1;
    turn = 1;
    winnerStat = false;
    turnStat = false;
}

void MyGame::start() {
    createBoard();
    std::cout << "Press A for Automatic game type or M for Manual game type: ";
    char gameTypeChoice;
    std::cin >> gameTypeChoice;

    GameType* gameType;

    if (gameTypeChoice == 'A') {
        gameType = new AutoGameType();
    } else if (gameTypeChoice == 'M') {
        gameType = new ManualGameType();
    } else {
        std::cout << "Invalid game type choice. Please choose A for Automatic or M for Manual." << std::endl;
        return;
    }

    std::cout << "Press C to CONTINUE next turn, or E to RESTART or END the game" << std::endl;
    char choice;
    std::cin >> choice;

    while (choice != 'E' && winnerStat == false && turnStat == false) {
        if (choice == 'C') {
            gameType->nextTurn(*this);
        } else {
            std::cout << "Invalid option, please press C to continue next turn or E to end the game" << std::endl;
        }

        if (winnerStat == false && turnStat == false) {
            std::cin >> choice;
        }
    }

    if (winnerStat == false && turnStat == false) {
        std::cout << "-- GAME OVER --" << std::endl;
        std::cout << "Thanks for playing!!!" << std::endl;

        char restartChoice;
        std::cout << "Do you want to restart the game? (Y/N): ";
        std::cin >> restartChoice;

        if (tolower(restartChoice) == 'y') {
            resetGame();
            MyGame game;
            game.start();
        }
    }
}