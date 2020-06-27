#include "board.h"

Board::Board(int size){
    this->size = size;
    this->bestScore = 0;

    // setting size
    this->map.resize(size);
    for(int i=0; i<size; i++)
        this->map[i].resize(size);

    reset();
}

std::pair<int,int> Board::randFindFreeField() const{
    std::pair<int,int> pair;

    srand(time(NULL));
    do{
        pair.first = rand()%this->size;
        pair.second = rand()%this->size;
    }while(this->map[pair.first][pair.second] != NULL);

    return pair;
}

void Board::initMap(){
    placeRandomly();
    placeRandomly();
}

void Board::clearMap(){
    for(int i=0; i<this->size; i++){
        for(int j=0; j<this->size; j++){
            if(this->map[i][j] != NULL){
                delete this->map[i][j];
                this->map[i][j] = NULL;
            }
        }
    }

    this->score = 0;
    this->actualFieldsNumber = 0;
}

void Board::placeRandomly(){
    std::pair<int,int> pair = randFindFreeField();
    this->map[pair.first][pair.second] = new Field();
    this->actualFieldsNumber++;
}

void Board::reset(){
    clearMap();
    initMap();
}

bool Board::moveTop(int y, int x){
    if(this->map[y][x] != NULL){
        int nextY = y-1;
        if(nextY < 0) return false;

        // looking for new place
        while(nextY >= 0 && this->map[nextY][x] == NULL)
            nextY--;

        // end reached
        if(nextY < 0){
            this->map[0][x] = this->map[y][x];
            this->map[y][x] = NULL;
            return true;
        }
        // collision
        else{
            // the same value
            if(this->map[nextY][x]->getValue() == this->map[y][x]->getValue()
                    && !this->map[nextY][x]->isUpdated()){
                this->map[nextY][x]->update();
                this->deleteField(y,x);
                updateScore(this->map[nextY][x]->getValue());
                return true;
            }
            // different value
            else{
                this->map[nextY+1][x] = this->map[y][x];
                if(y != nextY+1) this->map[y][x] = NULL;
                return nextY+1 != y;
            }
        }
    }

    return false;
}

bool Board::moveRight(int y, int x){
    if(this->map[y][x] != NULL){
        int nextX = x+1;
        if(nextX >= this->size) return false;

        // looking for new place
        while(nextX < this->size && this->map[y][nextX] == NULL)
            nextX++;

        // end reached
        if(nextX >= this->size){
            this->map[y][this->size-1] = this->map[y][x];
            this->map[y][x] = NULL;
            return true;
        }
        // collision
        else{
            // the same value
            if(this->map[y][nextX]->getValue() == this->map[y][x]->getValue()
                    && !this->map[y][nextX]->isUpdated()){
                this->map[y][nextX]->update();
                this->deleteField(y,x);
                updateScore(this->map[y][nextX]->getValue());
                return true;
            }
            // different value
            else{
                this->map[y][nextX-1] = this->map[y][x];
                if(x != nextX-1) this->map[y][x] = NULL;
                return x != nextX-1;
            }
        }
    }

    return false;
}

bool Board::moveDown(int y, int x){
    if(this->map[y][x] != NULL){
        int nextY = y+1;
        if(nextY >= this->size) return false;

        // looking for new place
        while(nextY < this->size && this->map[nextY][x] == NULL)
            nextY++;

        // end reached
        if(nextY >= this->size){
            this->map[this->size-1][x] = this->map[y][x];
            this->map[y][x] = NULL;
            return true;
        }
        // collision
        else{
            // the same value
            if(this->map[nextY][x]->getValue() == this->map[y][x]->getValue()
                    && !this->map[nextY][x]->isUpdated()){
                this->map[nextY][x]->update();
                this->deleteField(y,x);
                updateScore(this->map[nextY][x]->getValue());
                return true;
            }
            // different value
            else{
                this->map[nextY-1][x] = this->map[y][x];
                if(y != nextY-1) this->map[y][x] = NULL;
                return y != nextY-1;
            }
        }
    }

    return false;
}

bool Board::moveLeft(int y, int x){
    if(this->map[y][x] != NULL){
        int nextX = x-1;
        if(nextX < 0) return false;

        // looking for new place
        while(nextX >= 0 && this->map[y][nextX] == NULL)
            nextX--;

        // end reached
        if(nextX < 0){
            this->map[y][0] = this->map[y][x];
            this->map[y][x] = NULL;
            return true;
        }
        // collision
        else{
            // the same value
            if(this->map[y][nextX]->getValue() == this->map[y][x]->getValue()
                    && !this->map[y][nextX]->isUpdated()){
                this->map[y][nextX]->update();
                this->deleteField(y,x);
                updateScore(this->map[y][nextX]->getValue());
                return true;
            }
            // different value
            else{
                this->map[y][nextX+1] = this->map[y][x];
                if(x != nextX+1) this->map[y][x] = NULL;
                return x != nextX+1;
            }
        }
    }

    return false;
}

void Board::move(Direction direction){
    // moving
    bool moved = false;
    if(direction == Direction::TOP){
        for(int y=0; y<this->size; y++)
            for(int x=0; x<this->size; x++)
                if(moveTop(y,x)) moved = true;
    }
    else if(direction == Direction::RIGHT){
        for(int y=0; y<this->size; y++)
            for(int x=this->size-1; x>=0; x--)
                if(moveRight(y,x)) moved = true;
    }
    else if(direction == Direction::DOWN){
        for(int y=this->size-1; y>=0; y--)
            for(int x=0; x<this->size; x++)
                if(moveDown(y,x)) moved = true;
    }
    else if(direction == Direction::LEFT){
        for(int y=0; y<this->size; y++)
            for(int x=0; x<this->size; x++)
                if(moveLeft(y,x)) moved = true;
    }

    // reseting update
    for(int y=0; y<this->size; y++)
        for(int x=0; x<this->size; x++)
            if(this->map[y][x] != NULL)
                this->map[y][x]->resetUpdate();

    // placing new one
    if(moved && this->actualFieldsNumber != this->size*this->size)
        placeRandomly();
}

void Board::deleteField(int y, int x){
    this->map[y][x] = NULL;
    this->actualFieldsNumber--;
}

bool Board::canMove() const{
    // checkng number of occupied fields
    if(this->actualFieldsNumber < this->size*this->size)
        return true;

    // checking equality to neighbourhood
    for(int y=0; y<this->size; y++){
        for(int x=0; x<this->size; x++){
            if(y-1>=0 && this->map[y-1][x] != NULL && this->map[y][x] != NULL
                    && this->map[y][x]->getValue() == this->map[y-1][x]->getValue())
                return true;
            if(x-1>=0 && this->map[y][x-1] != NULL && this->map[y][x] != NULL
                    && this->map[y][x]->getValue() == this->map[y][x-1]->getValue())
                return true;
            if(y+1<this->size && this->map[y+1][x] != NULL && this->map[y][x] != NULL
                    && this->map[y][x]->getValue() == this->map[y+1][x]->getValue())
                return true;
            if(x+1<this->size && this->map[y][x+1] != NULL && this->map[y][x] != NULL
                    && this->map[y][x]->getValue() == this->map[y][x+1]->getValue())
                return true;
        }
    }

    return false;
}

bool Board::got2048() const{
    for(int y=0; y<this->size; y++)
        for(int x=0; x<this->size; x++)
            if(this->map[y][x] != NULL && this->map[y][x]->getValue() == 2048)
               return true;

    return false;
}

void Board::updateScore(int toAddValue){
    this->score += toAddValue;

    if(this->bestScore < this->score)
        this->bestScore = this->score;
}
