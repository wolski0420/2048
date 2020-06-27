#ifndef QGAMEWINDOW_H
#define QGAMEWINDOW_H

#include <QCloseEvent>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>

class QGameWindow: public QWidget
{
    Q_OBJECT
private:
    // variables
    QVBoxLayout *mainVerticalLayout;
    QHBoxLayout *buttonHorizontalLayout;
    QLabel *windowLabel;
    QWidget *parent;

public:
    // methods
    QGameWindow(QWidget *parent);
    void setLabelText(QString text){this->windowLabel->setText(text);}
    void addButton(QPushButton *button){this->buttonHorizontalLayout->addWidget(button);}
    void showWindow();
    void closeWindow();
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // QGAMEWINDOW_H
