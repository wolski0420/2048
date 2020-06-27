#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Engine/game.h>
#include "GUI/qboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // variables
    Ui::MainWindow *ui;
    QWidget *instructionWindow;
    QBoard *gameBoard;
    Game *game;

    // methods
    void setInfoObjects();
    void setGameBoard();
    void setInstruction();

public:
    // methods
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void showInstruction();
public slots:
    void setScore(int newScore, int newBestScore);
};
#endif // MAINWINDOW_H
