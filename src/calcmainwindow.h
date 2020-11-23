#pragma once

#include <QMainWindow>
#include "src/displaymain.h"
#include "src/displaybin.h"
#include "src/modeselection.h"
#include "src/functionbuttons.h"
#include "src/numberbuttons.h"
#include "src/actionbar.h"
#include "memorybuttons.h"

class CalcMainWindow : public QMainWindow
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    CalcMainWindow(QWidget *parent = nullptr);

signals:
    void move(int x, int y);
    void show();

private:
    DisplayMain*     mainDisplay    = nullptr;
    DisplayBin*      binDisplay     = nullptr;
    ModeSelection*   modeSelection  = nullptr;
    LeftFunctionButtons* leftFunctionButtons  = nullptr;
    RightFunctionButtons* rightFunctionButtons = nullptr;
    MemoryButtons*    memoryButtons     = nullptr;
    DecNumberButtons* decNumberButtons  = nullptr;
    HexNumberButtons* hexNumberButtons  = nullptr;
    ActionBar*        actionBar         = nullptr;
};
