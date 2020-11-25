#include "calcmainwindow.h"
#include "QLabel"
CalcMainWindow::CalcMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(500, 500);
    auto centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    actionBar = new ActionBar(this);
    mainDisplay = new DisplayMain(centralWidget);
    binDisplay = new DisplayBin(centralWidget);
    modeSelection = new ModeSelection(centralWidget);
    leftFunctionButtons = new LeftFunctionButtons(centralWidget);
    rightFunctionButtons = new RightFunctionButtons(centralWidget);
    hexNumberButtons = new HexNumberButtons(centralWidget);
    decNumberButtons = new DecNumberButtons(centralWidget);
    memoryButtons = new MemoryButtons(centralWidget);


    auto layout = new QGridLayout(centralWidget);
    layout->setContentsMargins(10, 30, 10, 10);
                                        // r  c  r  c
    layout->addWidget(mainDisplay,         0, 0, 1, 10);
    layout->addWidget(binDisplay,          1, 0, 1, 10);
    layout->addWidget(modeSelection,       2, 0, 6, 2);
    layout->addWidget(leftFunctionButtons, 2, 2, 6, 2);
    layout->addWidget(hexNumberButtons,    2, 4, 6, 1);
    layout->addWidget(memoryButtons,       2, 5, 1, 5);
    layout->addWidget(decNumberButtons,    3, 5, 5, 3);
    layout->addWidget(rightFunctionButtons,3, 8, 5, 2);

    mainDisplay->setMinimumHeight(90);
    binDisplay->setMaximumHeight(70);
    centralWidget->setLayout(layout);

    layout->setRowStretch(0, 6);
    layout->setRowStretch(1, 6);
    layout->setRowStretch(2, 2);
    layout->setRowStretch(3, 11);

    layout->setColumnStretch(0, 2);
    layout->setColumnStretch(1, 2);

    // Connect mode selection to enabling/disabling buttons
    QObject::connect(modeSelection, &ModeSelection::numSystemChanged,[&](Calc::NumeralSystem numSystem){
        switch(numSystem)
        {
        case Calc::NumeralSystem::Hex:
            decNumberButtons->setButtonsEnabled(Calc::NumeralSystem::Hex);
            hexNumberButtons->setButtonsEnabled(true);
            break;
        case Calc::NumeralSystem::Dec:
            decNumberButtons->setButtonsEnabled(Calc::NumeralSystem::Dec);
            hexNumberButtons->setButtonsEnabled(false);
            break;
        case Calc::NumeralSystem::Oct:
            decNumberButtons->setButtonsEnabled(Calc::NumeralSystem::Oct);
            hexNumberButtons->setButtonsEnabled(false);
            break;
        case Calc::NumeralSystem::Bin:
            decNumberButtons->setButtonsEnabled(Calc::NumeralSystem::Bin);
            hexNumberButtons->setButtonsEnabled(false);
            break;
        }
    });

    // Connect binaryDisplay slots
    QObject::connect(modeSelection, &ModeSelection::precisionChanged,[&](Calc::BitPrecision precision){
        binDisplay->changeDisplayPrecision(precision);
    });
    // Connect mainDisplay slots
    QObject::connect(actionBar, &ActionBar::toggleGroupNumbers, mainDisplay, &DisplayMain::toggleGroupNumbers);
    QObject::connect(actionBar, &ActionBar::copy, mainDisplay, &DisplayMain::copyFromDisplay);
    QObject::connect(modeSelection, &ModeSelection::numSystemChanged, mainDisplay, &DisplayMain::setNumeralSystem);

    // Set default state of buttons
    decNumberButtons->setButtonsEnabled(Calc::NumeralSystem::Dec);
    hexNumberButtons->setButtonsEnabled(false);


    // TESTING
    mainDisplay->displayNumber(45686222222);
    binDisplay->setBits(45686222222);
}


