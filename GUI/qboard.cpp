#include "qboard.h"

QBoard::QBoard(QWidget *parent, Game *game): QWidget(parent)
{
    this->parent = parent;
    this->game = game;
    this->size = this->game->getGameBoard()->getSize();
    this->gridLayout = NULL;

    // setting size of fields' map
    qmap.resize(this->size);
    for(int i=0; i<this->size; i++){
        qmap[i].resize(this->size);
    };

    // setting every neccessary object and reseting
    setLosingWindow();
    setWinningWindow();
    resetBoard();
}

QBoard::~QBoard(){
    delete game;

    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            delete qmap[i][j];
}

QPushButton *QBoard::getResetButton(){
    QPushButton *resetButton = new QPushButton();
    resetButton->setText("Reset");
    connect(resetButton,&QPushButton::pressed,
            this,&QBoard::resetBoard);
    return resetButton;
}

QPushButton *QBoard::getContinueButton(){
    QPushButton *continueButton = new QPushButton();
    continueButton->setText("Continue");
    connect(continueButton,&QPushButton::pressed,
            this,&QBoard::continueGame);
    return continueButton;
}

QPushButton *QBoard::getExitGameButton(){
    QPushButton *exitGameButton = new QPushButton();
    exitGameButton->setText("Finish");
    connect(exitGameButton,&QPushButton::pressed,
            this,&QBoard::exitGame);
    return exitGameButton;
}

void QBoard::setWinningWindow(){
    this->winningWindow = new QGameWindow(parent);
    this->winningWindow->setLabelText(QString("You won the game! You reached 2048!"));
    this->winningWindow->setWindowTitle("2048 WINNER!");
    this->winningWindow->addButton(getResetButton());
    this->winningWindow->addButton(getContinueButton());
    this->winningWindow->addButton(getExitGameButton());
}

void QBoard::setLosingWindow(){
    this->losingWindow = new QGameWindow(parent);
    this->losingWindow->setLabelText(QString("You lost the game! You cannot move anymore!"));
    this->losingWindow->setWindowTitle("2048 LOSER!");
    this->losingWindow->addButton(getResetButton());
    this->losingWindow->addButton(getExitGameButton());
}

void QBoard::draw(){
    // creating new, empty layout for fields
    if(this->gridLayout != NULL) delete this->gridLayout;
    this->gridLayout = new QGridLayout();
    this->gridLayout->setSpacing(15);
    setLayout(this->gridLayout);

    // drawing fields
    for(int i=0; i<this->size; i++){
        for(int j=0; j<this->size; j++){
            if(qmap[i][j] != NULL) delete qmap[i][j];
            qmap[i][j] = new QField(game->getGameBoard()->getField(i,j));
            gridLayout->addWidget(qmap[i][j],i,j);
            qmap[i][j]->draw();
        }
    }
}

void QBoard::refresh(){
    // drawing changes
    draw();

    // informing about changes
    emit scoreChanged(this->game->getScore(),this->game->getBestScore());

    // checking game status and taking actions
    Status status = this->game->getStatus();
    if(!this->showedWonWindow && status == Status::WON){
        this->winningWindow->showWindow();
        this->showedWonWindow = true;
    }
    else if(status == Status::LOST){
        this->losingWindow->showWindow();
    }
}

void QBoard::closeWindows(){
    this->winningWindow->closeWindow();
    this->losingWindow->closeWindow();
}

void QBoard::continueGame(){
    closeWindows();
}

void QBoard::exitGame(){
    closeWindows();
    this->parent->close();
}

void QBoard::resetBoard(){
    this->game->restart();
    this->showedWonWindow = false;

    refresh();
    closeWindows();
}

void QBoard::keyPressEvent(QKeyEvent *event)
{
    // move ...
    if(event->key() == Qt::Key_Up)
        game->move(Direction::TOP);
    else if(event->key() == Qt::Key_Left)
        game->move(Direction::LEFT);
    else if(event->key() == Qt::Key_Down)
        game->move(Direction::DOWN);
    else if(event->key() == Qt::Key_Right)
        game->move(Direction::RIGHT);

    // ... and check if changes are neccessary
    refresh();
}
