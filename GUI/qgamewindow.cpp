#include "qgamewindow.h"

QGameWindow::QGameWindow(QWidget *parent)
{
    // setting components
    this->parent = parent;
    this->windowLabel = new QLabel();
    this->buttonHorizontalLayout = new QHBoxLayout();

    // setting main layout
    this->mainVerticalLayout = new QVBoxLayout();
    this->mainVerticalLayout->addWidget(this->windowLabel);
    this->mainVerticalLayout->addLayout(this->buttonHorizontalLayout);

    setLayout(this->mainVerticalLayout);

    // when it's not set, window likes to hide behind main window
    this->setFocusPolicy(Qt::StrongFocus);
    this->setWindowState(Qt::WindowState::WindowActive);
}

void QGameWindow::showWindow(){
    this->show();
    this->parent->setEnabled(false);
}

void QGameWindow::closeWindow(){
    this->close();
    this->parent->setEnabled(true);
}

void QGameWindow::closeEvent(QCloseEvent *event){
    this->closeWindow();
    event->accept();
}
