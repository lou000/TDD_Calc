#pragma once

#include <QMainWindow>
#include "src/displaymain.h"
#include "src/displaybin.h"
#include "src/modeselection.h"
#include "src/functionbuttons.h"
#include "src/numberbuttons.h"
#include "src/actionbar.h"

class CalcMainWindow : public QMainWindow
{
    Q_OBJECT
    friend class Tests;

public:
    CalcMainWindow(QWidget *parent = nullptr);
    ~CalcMainWindow();

signals:
    void move(int x, int y);
    void show();

private:
    DisplayMain*     mainDisplay    = nullptr;
    DisplayBin*      binDisplay     = nullptr;
    ModeSelection*   modeSelection  = nullptr;
    FunctionButtons* functionButtons = nullptr;
    NumberButtons*   numberButtons  = nullptr;
    ActionBar*       actionBar      = nullptr;
};
