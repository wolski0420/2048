#ifndef FIELD_H
#define FIELD_H

#include <cstdlib>
#include <ctime>

class Field
{
private:
    // variables
    static const int probability = 5; // 1/5 for value=4
    int value;
    bool afterUpdate;

public:
    // methods
    Field();
    int getValue() const {return this->value;}
    void update();
    void resetUpdate(){this->afterUpdate = false;}
    bool isUpdated() const {return this->afterUpdate;}
};

#endif // FIELD_H
