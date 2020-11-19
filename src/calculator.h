#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>

enum CalcFunction
{
    None,
    Add,
    Divide
};

class Calculator
{
public:
    Calculator();

private:
    qint64 displayedNumber;
    qint64 previousNumber;
    qint64 memory;
    CalcFunction savedFunction = None;
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
