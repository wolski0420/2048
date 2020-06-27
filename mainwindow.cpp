#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setStyleSheet("QWidget {background-color: #bbada0;}");

    this->setWindowTitle("2048");
    this->sizePolicy().setHeightForWidth(true);

    setGameBoard();
    setInfoObjects();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameBoard;
}

void MainWindow::setInfoObjects(){
    setInstruction();

    connect(ui->instructionButton,&QPushButton::pressed,
            this,&MainWindow::showInstruction);
    connect(this->gameBoard,&QBoard::scoreChanged,
            this,&MainWindow::setScore);
    connect(ui->resetButton,&QPushButton::pressed,
            this->gameBoard,&QBoard::resetBoard);

    QFont *biggerFont = new QFont();
    biggerFont->setPointSize(17);
    biggerFont->setBold(true);
    QFont *smallerFont = new QFont();
    smallerFont->setPointSize(13);

    ui->actualScoreLabel->setFont(*biggerFont);
    ui->actualScoreHeader->setFont(*smallerFont);
    ui->bestScoreHeader->setFont(*smallerFont);
    ui->bestScoreLabel_2->setFont(*biggerFont);

    ui->infoWidget->setStyleSheet("QWidget {background-color: rgba(238, 228, 218, 0.35); margin-left: 20; margin-right: 20;}");
    ui->actualScoreLabel->setText(QString::number(0));
    ui->bestScoreLabel_2->setText(QString::number(0));
}

void MainWindow::setGameBoard(){
    this->gameBoard = new QBoard(this,new Game(4));
    this->gameBoard->setFocusPolicy(Qt::StrongFocus);
    this->gameBoard->setMinimumSize(600,600);

    ui->layoutForGameAdd->addWidget(this->gameBoard);
}

void MainWindow::setInstruction(){
    this->instructionWindow = new QWidget(nullptr);
    this->instructionWindow->setStyleSheet("QWidget {background-color: #bbada0;}");
    this->instructionWindow->setMinimumWidth(450);
    this->instructionWindow->setMinimumHeight(300);
    this->instructionWindow->setMaximumWidth(900);
    this->instructionWindow->setMaximumHeight(500);

    QVBoxLayout *layout = new QVBoxLayout();
    this->instructionWindow->setLayout(layout);

    QFont *biggerFont = new QFont();
    biggerFont->setPointSize(17);
    biggerFont->setBold(true);
    biggerFont->setUnderline(true);
    QFont *smallerFont = new QFont();
    smallerFont->setPointSize(13);

    QLabel *title = new QLabel("Instrukcja");
    title->setAlignment(Qt::AlignCenter);
    title->setFont(*biggerFont);
    title->setFixedHeight(80);
    layout->addWidget(title);

    QLabel *description = new QLabel();
    description->setText(
                "Use your arrow keys to move the fields.\n "
                "\u2190 - move to the left,\n"
                "\u2191 - move to the top,\n"
                "\u2192 - move to the right,\n"
                "\u2193 - move to the bottom,\n\n"
                "When you meet two fields with the same number, "
                "they merge into one with doubled value.\n"
                "Try to get 2048 field or you lose this game! Have fun!"
                );
    description->setWordWrap(true);
    description->setFont(*smallerFont);
    layout->addWidget(description);
}

void MainWindow::showInstruction(){
    this->instructionWindow->show();
}

void MainWindow::setScore(int newScore, int newBestScore){
    ui->actualScoreLabel->setText(QString::number(newScore));
    ui->bestScoreLabel_2->setText(QString::number(newBestScore));
}
