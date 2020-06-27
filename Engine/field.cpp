#include "field.h"

Field::Field(){
    srand(time(NULL));
    this->value = rand()%probability==0 ? 4 : 2;
    this->afterUpdate = false;
}

void Field::update(){
    this->value *= 2;
    this->afterUpdate = true;
}
