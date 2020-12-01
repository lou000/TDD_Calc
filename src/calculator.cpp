#include "calculator.h"

Calculator::Calculator(QObject* parent)
    : QObject(parent)
{

}

void Calculator::displayNumber()
{
    switch (currentPrecision) {
    case Calc::BitPrecision::_64bit:
        currentNumber = static_cast<qint64>(currentNumber);
        break;
    case Calc::BitPrecision::_32bit:
        currentNumber = static_cast<qint32>(currentNumber);
        break;
    case Calc::BitPrecision::_16bit:
        currentNumber = static_cast<qint16>(currentNumber);
        break;
    case Calc::BitPrecision::_8bit:
        currentNumber = static_cast<qint8>(currentNumber);
        break;
    }
    emit signalDisplayNumber(currentNumber);
}

void Calculator::handleBitFlipped(int bitPosition)
{
    BIT_FLIP(currentNumber, bitPosition);
    displayNumber();
}

void Calculator::handleCalculatorFunction(Calc::Functions func)
{
    //One arg functions affect only the currentNumber and work immiedietely
    switch (func) {
    case Calc::_rol:
        currentNumber <<= 1;
        break;
    case Calc::_ror:
        currentNumber >>= 1;
        break;
    case Calc::_not:
        currentNumber = ~currentNumber;
        break;
    case Calc::_invert:
        currentNumber = -currentNumber;
        break;
    case Calc::_equal:
        executeFunction();
        waitingForNextNumb = true;
        break;
    default:
        if(!waitingForNextNumb)
            executeFunction();
        savedFunction = func;
        waitingForNextNumb = true;
        break;
    }
    clearOnNextNumb = true;
    displayNumber();
}

void Calculator::executeFunction()
{
    auto temp = previousNumber;
    previousNumber = currentNumber;
    switch (savedFunction) {
    case Calc::_mod:
        currentNumber = temp % currentNumber;
        break;
    case Calc::_or:
        currentNumber = temp | currentNumber;
        break;
    case Calc::_xor:
        currentNumber = temp ^ currentNumber;
        break;
    case Calc::_and:
        currentNumber = temp & currentNumber;
        break;
    case Calc::_lsh:
        currentNumber = temp << currentNumber;
        break;
    case Calc::_rsh:
        currentNumber = temp >> currentNumber;
        break;
    case Calc::_divide:
        if(currentNumber != 0)
            currentNumber = temp / currentNumber;
        break;
    case Calc::_multiply:
        currentNumber = temp * currentNumber;
        break;
    case Calc::_subtract:
        currentNumber = temp - currentNumber;
        break;
    case Calc::_add:
        currentNumber = temp + currentNumber;
        break;
    case Calc::_none:
        break;
    default:
        qDebug()<<"Not Implemented";
        break;
    }
}

void Calculator::handleNumberButton(Calc::NumberPad numberButton)
{
    switch (numberButton) {

    case Calc::_clear:
        previousNumber = 0;
        savedFunction = Calc::_none;
        savedExpression = QPair<float, Calc::Functions>(0, Calc::_none);
        currentNumber = 0;
        break;
    case Calc::_clearEnter:
        currentNumber = 0;
        break;
    case Calc::_backSpace:
        if(!clearOnNextNumb)
            switch (currentNumSystem) {
            case Calc::Hex:
                currentNumber /= 16;
                break;
            case Calc::Dec:
                currentNumber /= 10;
                break;
            case Calc::Oct:
                currentNumber /= 8;
                break;
            case Calc::Bin:
                currentNumber /= 2;
                break;
            }
        break;
    default:
        if(clearOnNextNumb)
        {
            previousNumber = currentNumber;
            currentNumber = 0;
        }
        clearOnNextNumb = false;
        waitingForNextNumb = false;

        switch (currentNumSystem) {
        case Calc::Hex:
            Q_ASSERT(static_cast<int>(numberButton)<16);
            currentNumber *= 16;
            currentNumber += static_cast<int>(numberButton);
            break;
        case Calc::Dec:
            Q_ASSERT(static_cast<int>(numberButton)<10);
            currentNumber *= 10;
            currentNumber += static_cast<int>(numberButton);
            break;
        case Calc::Oct:
            Q_ASSERT(static_cast<int>(numberButton)<8);
            currentNumber *= 8;
            currentNumber += static_cast<int>(numberButton);
            break;
        case Calc::Bin:
            Q_ASSERT(static_cast<int>(numberButton)<2);
            currentNumber *= 2;
            currentNumber += static_cast<int>(numberButton);
            break;
        }
        break;
    }
    displayNumber();
}

void Calculator::handlePrecisionSystemChange(Calc::BitPrecision prec)
{
    currentPrecision = prec;
    displayNumber();
}

void Calculator::handleMemoryFunctions(Calc::MemoryFunctions func)
{

}

void Calculator::handleNumeralSystemChanged(Calc::NumeralSystem sys)
{
    currentNumSystem = sys;
}



