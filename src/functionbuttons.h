#ifndef FUNCTIONBUTTONS_H
#define FUNCTIONBUTTONS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QSizePolicy>
#include "globalinclude.h"

class LeftFunctionButtons : public QWidget
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    explicit LeftFunctionButtons(QWidget *parent = nullptr);

private:
    int numOfParanthesesOpened = 0;
    QLabel* paranthesesIndicator;
    QPushButton* modButton;
    QPushButton* paranthesesOpenButton;
    QPushButton* paranthesesCloseButton;
    QPushButton* rolButton;
    QPushButton* rorButton;
    QPushButton* orButton;
    QPushButton* xorButton;
    QPushButton* lshButton;
    QPushButton* rshButton;
    QPushButton* notButton;
    QPushButton* andButton;

signals:
    void functionButtonPressed(Calc::Functions function);

public slots:
    // The parantheses functionality is confusing but from what i understand
    // we only have to clear this state when user presses "C" or "=".
    // we may need more slots/signals to connect it with various events
    void clearParanthesesCount();

};


class RightFunctionButtons : public QWidget
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    explicit RightFunctionButtons(QWidget *parent = nullptr);

private:
    QPushButton* invertButton;
    QPushButton* divideButton;
    QPushButton* multiplyButton;
    QPushButton* subtractButton;
    QPushButton* addButton;
    QPushButton* deadButton1;
    QPushButton* deadButton2;
    QPushButton* deadButton3;
    QPushButton* equalButton;

signals:
    void functionButtonPressed(Calc::Functions function);
};

#endif // FUNCTIONBUTTONS_H
