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
    qint64 currentNumber = 0;
    qint64 previousNumber = 0;
    qint64 memoryNumber = 0;

    bool waitingForNextNumb = true;
    bool clearOnNextNumb = false;

    Calc::Functions savedFunction = Calc::_none;
    Calc::BitPrecision currentPrecision = Calc::_64bit;
    Calc::NumeralSystem currentNumSystem = Calc::Dec;

    QPair<float, Calc::Functions> savedExpression = QPair<float, Calc::Functions>(0, Calc::_none);

    void displayNumber();
    void executeFunction();

signals:
    void signalDisplayNumber(qint64 num);

public slots:
    void handleBitFlipped(int bitPosition);
    void handleCalculatorFunction(Calc::Functions func);
    void handleNumberButton(Calc::NumberPad numberButton);
    void handlePrecisionSystemChange(Calc::BitPrecision prec);
    void handleMemoryFunctions(Calc::MemoryFunctions func);
    void handleNumeralSystemChanged(Calc::NumeralSystem sys);

};


#endif // CALCULATOR_H
