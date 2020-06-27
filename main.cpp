#include "mainwindow.h"

#include <QApplication>
#include <string>
#include "Engine/game.h"
#include "Engine/board.h"
#include "Engine/field.h"
#include "Engine/direction.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
