#include "qfield.h"

void QField::draw(){
    if(field == NULL){
        setText("");
        setStyleSheet(EmptyFieldStyleSheet);
    }
    else{
        setText(QString::number(field->getValue()));

        int index = log(this->field->getValue())/log(2);
        setStyleSheet(FieldStyleSheet[index]);
    }
}
