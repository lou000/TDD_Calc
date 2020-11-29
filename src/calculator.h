#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QDebug>
#include "globalinclude.h"


class Calculator : public QObject
{
    Q_OBJECT
    MAKE_TESTABLE
public:
    Calculator(QObject *parent = nullptr);

private:
    qint64 currentNumber;
    qint64 previousNumber;
    //qint64 memory;
    bool numInMemory = false;

    Calc::Functions savedFunction = Calc::_none;
    Calc::BitPrecision currentPrecision = Calc::_64bit;

    qint64 _32(qint64 number);
    qint64 _16(qint64 number);
    qint64 _8(qint64 number);
    qint64 add(qint64 memory, qint64 number);
    qint64 subtract(qint64 memory, qint64 number);
    qint64 divide(qint64 memory, qint64 number);
    qint64 multiply(qint64 memory, qint64 number);
    qint64 executeFunction();
signals:
    void displayNumber(qint64 num);

public slots:
    void handleBitFlipped(int bitPosition);
    void handleCalculatorFunction(Calc::Functions func);
    void handleNumberButton(Calc::NumberPad numberButton);
    void handlePrecisionSystemChange(Calc::BitPrecision prec);
    void handleMemoryFunctions(Calc::MemoryFunctions func);

};


#endif // CALCULATOR_H
