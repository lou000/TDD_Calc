#include "calculator.h"

Calculator::Calculator(QObject* parent)
    : QObject(parent)
{

}

void Calculator::handleBitFlipped(int bitPosition)
{

}

void Calculator::handleCalculatorFunction(Calc::Functions func)
{
    if(savedFunction != Calc::Functions::_none && numInMemory)
        executeFunction();

    switch (func) {
    case Calc::Functions::_equal:
        emit displayNumber(currentNumber);
        break;
    case Calc::Functions::_invert:
        break;
    default:
        savedFunction = func;
        break;
    }
}

void Calculator::handleNumberButton(Calc::NumberPad numberButton)
{

}

void Calculator::handlePrecisionSystemChange(Calc::BitPrecision prec)
{

}

void Calculator::handleMemoryFunctions(Calc::MemoryFunctions func)
{

}

qint64 Calculator::executeFunction()
{
    switch (savedFunction) {
    case Calc::Functions::_add:
        break;
    case Calc::Functions::_subtract:
        break;
    case Calc::Functions::_divide:
        break;
    }
    savedFunction = Calc::Functions::_none;
}

qint64 Calculator::_32(qint64 number)
{
    qint64 num32 = number%4294967296;
    return num32;
}

qint64 Calculator::_16(qint64 number)
{
    qint64 num16 = number % 65536;
    return num16;
}

qint64 Calculator::_8(qint64 number)
{
    qint64 num8 = number % 256;
    return num8;
}

qint64 Calculator::add(qint64 memory, qint64 number)
{
    memory = memory + number;
    return memory;
}

qint64 Calculator::subtract(qint64 memory, qint64 number)
{
    memory = memory - number;
    return memory;
}

qint64 Calculator::divide(qint64 memory, qint64 number)
{
    memory = memory / number;
    return memory;
}

qint64 Calculator::multiply(qint64 memory, qint64 number)
{
    memory = memory / number;
    return memory;
}
