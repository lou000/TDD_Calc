#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QDebug>
#include "globalinclude.h"


class Calculator
{
    MAKE_TESTABLE
public:
    Calculator();

private:
    qint64 displayedNumber;
    qint64 previousNumber;
   //https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
    qint64 memory;

    Calc::Functions savedFunction = Calc::_none;
};

/*
 *  void functionPressed(Func function){
 *
 *      if(function has one arg)
 *              calculator.savedFunction = None
 *              executeFunction(function)
 *      else
 *
 *      if(calculator.savedFunction !=  CalcFunction::None;)
 *              executeFunction(calculator.savedFunction);
 *      else
 *              calculator.savedFunction = function
 *
 *  }
 *
 *  void executeFunction(Func function){
 *
 *  }
 *
*/


#endif // CALCULATOR_H
