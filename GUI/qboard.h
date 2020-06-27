#ifndef QBOARD_H
#define QBOARD_H

#include <QStyleOption>
#include <QPainter>
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QKeyEvent>
#include "qfield.h"
#include "qgamewindow.h"
#include "../Engine/game.h"
#include "../Engine/status.h"

class QBoard: public QWidget
{
    Q_OBJECT
private:
    // variables
    QWidget *parent;
    QVector<QVector<QField*>> qmap;
    QGridLayout *gridLayout;
    QGameWindow *winningWindow;
    QGameWindow *losingWindow;
    Game *game;
    int size;
    bool showedWonWindow;

    // methods
    QPushButton *getResetButton();
    QPushButton *getContinueButton();
    QPushButton *getExitGameButton();
    void setWinningWindow();
    void setLosingWindow();
    void draw();
    void refresh();
    void closeWindows();

public:
    QBoard(QWidget *parent, Game *game);
    ~QBoard();

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void scoreChanged(int newScore, int newBestScore);

private slots:
    void continueGame();    // for continue button
    void exitGame();    // for exit button

public slots:
    void resetBoard();  // for reset button
};

#endif // QBOARD_H
