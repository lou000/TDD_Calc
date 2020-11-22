#pragma once
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "globalinclude.h"

class DecNumberButtons : public QWidget
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    explicit DecNumberButtons(QWidget *parent = nullptr);

private:
    QPushButton* button0;
    QPushButton* button1;
    QPushButton* button2;
    QPushButton* button3;
    QPushButton* button4;
    QPushButton* button5;
    QPushButton* button6;
    QPushButton* button7;
    QPushButton* button8;
    QPushButton* button9;
    QPushButton* buttonBackSpace;
    QPushButton* buttonClear;
    QPushButton* buttonCE;
    QPushButton* buttonDeadComa;

signals:
    void numericalButtonPressed(Calc::NumberPad button);

public slots:
    void setButtonsEnabled(Calc::NumeralSystem system);
};


class HexNumberButtons : public QWidget
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    explicit HexNumberButtons(QWidget *parent = nullptr);

private:
    QPushButton* buttonA;
    QPushButton* buttonB;
    QPushButton* buttonC;
    QPushButton* buttonD;
    QPushButton* buttonE;
    QPushButton* buttonF;

signals:
    void numericalButtonPressed(Calc::NumberPad button);

public:
    void setButtonsEnabled(bool enabled);

};



