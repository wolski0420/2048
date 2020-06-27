#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include "field.h"
#include "direction.h"

class Board
{
private:
    // variables
    int size;
    int score;
    int bestScore;
    int actualFieldsNumber;
    std::vector<std::vector<Field*>> map;

    // methods
    std::pair<int,int> randFindFreeField() const;
    void initMap();
    void clearMap();
    void placeRandomly();
    bool moveTop(int y, int x);
    bool moveRight(int y, int x);
    bool moveDown(int y, int x);
    bool moveLeft(int y, int x);
    void deleteField(int y, int x);
    void updateScore(int toAddValue);

public:
    Board(int size);
    ~Board(){clearMap();}
    int getSize() const {return this->size;}
    int getScore() const {return this->score;}
    int getBestScore() const {return this->bestScore;}
    void reset();
    Field *getField(int y, int x) const {return this->map[y][x];}
    void move(Direction direction);
    bool canMove() const;
    bool got2048() const;
};

#endif // BOARD_H
