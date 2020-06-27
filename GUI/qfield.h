#ifndef QFIELD_H
#define QFIELD_H

#include <QLabel>
#include <cmath>
#include "../Engine/field.h"
#include "qfieldstyles.h"

class QField : public QLabel
{
    Q_OBJECT
private:
    // variables
    Field *field;

public:
    // methods
    QField(Field *field): field(field){};
    void draw();
};

#endif // QFIELD_H
