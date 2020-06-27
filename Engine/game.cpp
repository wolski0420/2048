#include "game.h"

Game::Game(int size){
    this->gameBoard = new Board(size);
    this->gameStatus = Status::PLAYING;
}

void Game::move(Direction direction){
    // move on board
    this->gameBoard->move(direction);

    // change status if neccessary
    if(this->gameBoard->got2048())
        this->gameStatus = Status::WON;

    else if(!this->gameBoard->canMove())
        this->gameStatus = Status::LOST;
}

void Game::restart(){
    this->gameStatus = Status::PLAYING;
    this->gameBoard->reset();
}
