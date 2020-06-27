#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "board.h"
#include "status.h"

class Game
{
private:
    // variables
    Board *gameBoard;
    Status gameStatus;

public:
    // methods
    Game(int size);
    ~Game(){delete this->gameBoard;}
    void move(Direction direction);
    void restart();
    Board *getGameBoard() const {return this->gameBoard;}
    Status getStatus() const {return this->gameStatus;}
    int getScore(){return this->gameBoard->getScore();}
    int getBestScore(){return this->gameBoard->getBestScore();}
};

#endif // GAME_H
