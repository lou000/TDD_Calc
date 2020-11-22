#include "numberbuttons.h"

DecNumberButtons::DecNumberButtons(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setSpacing(5);
    setLayout(layout);

    button0 = new QPushButton("0" ,this);
    button1 = new QPushButton("1" ,this);
    button2 = new QPushButton("2" ,this);
    button3 = new QPushButton("3" ,this);
    button4 = new QPushButton("4" ,this);
    button5 = new QPushButton("5" ,this);
    button6 = new QPushButton("6" ,this);
    button7 = new QPushButton("7" ,this);
    button8 = new QPushButton("8" ,this);
    button9 = new QPushButton("9" ,this);
    buttonBackSpace = new QPushButton("<-" ,this);
    buttonClear = new QPushButton("C" ,this);
    buttonCE = new QPushButton("CE" ,this);
    buttonDeadComa = new QPushButton("," ,this);

    // Disable a dead button
    buttonDeadComa->setEnabled(false);

    button0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button9->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonBackSpace->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonClear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonCE->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonDeadComa->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(buttonBackSpace, 0, 0);
    layout->addWidget(buttonCE,        0, 1);
    layout->addWidget(buttonClear,     0, 2);
    layout->addWidget(button7,         1, 0);
    layout->addWidget(button8,         1, 1);
    layout->addWidget(button9,         1, 2);
    layout->addWidget(button4,         2, 0);
    layout->addWidget(button5,         2, 1);
    layout->addWidget(button6,         2, 2);
    layout->addWidget(button1,         3, 0);
    layout->addWidget(button2,         3, 1);
    layout->addWidget(button3,         3, 2);
    layout->addWidget(button0,         4, 0, 1, 2);
    layout->addWidget(buttonDeadComa,  4, 2);

    // Change the object name to use a brighter stylesheet
    button0->setObjectName("numerical");
    button1->setObjectName("numerical");
    button2->setObjectName("numerical");
    button3->setObjectName("numerical");
    button4->setObjectName("numerical");
    button5->setObjectName("numerical");
    button6->setObjectName("numerical");
    button7->setObjectName("numerical");
    button8->setObjectName("numerical");
    button9->setObjectName("numerical");
    buttonBackSpace->setObjectName("numerical");
    buttonClear->setObjectName("numerical");
    buttonCE->setObjectName("numerical");
    buttonDeadComa->setObjectName("numerical");

    // Connect to main signal
    QObject::connect(button0,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::_0);});
    QObject::connect(button1,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::_1);});
    QObject::connect(button2,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::_2);});
    QObject::connect(button3,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::_3);});
    QObject::connect(button4,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::_4);});
    QObject::connect(button5,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::_5);});
    QObject::connect(button6,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::_6);});
    QObject::connect(button7,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::_7);});
    QObject::connect(button8,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::_8);});
    QObject::connect(button9,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::_9);});
    QObject::connect(buttonBackSpace,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::backSpace);});
    QObject::connect(buttonClear,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::Clear);});
    QObject::connect(buttonCE,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::ClearEnter);});


    // Buttons shortcuts
    button0->setShortcut(QKeySequence("0"));
    button1->setShortcut(QKeySequence("1"));
    button2->setShortcut(QKeySequence("2"));
    button3->setShortcut(QKeySequence("3"));
    button4->setShortcut(QKeySequence("4"));
    button5->setShortcut(QKeySequence("5"));
    button6->setShortcut(QKeySequence("6"));
    button7->setShortcut(QKeySequence("7"));
    button8->setShortcut(QKeySequence("8"));
    button9->setShortcut(QKeySequence("9"));
    buttonBackSpace->setShortcut(QKeySequence(Qt::Key_Backspace));
    buttonClear->setShortcut(QKeySequence(Qt::Key_Escape));
    buttonCE->setShortcut(QKeySequence(Qt::Key_Delete));

}

HexNumberButtons::HexNumberButtons(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setSpacing(5);
    setLayout(layout);

    buttonA = new QPushButton("A" ,this);
    buttonB = new QPushButton("B" ,this);
    buttonC = new QPushButton("C" ,this);
    buttonD = new QPushButton("D" ,this);
    buttonE = new QPushButton("E" ,this);
    buttonF = new QPushButton("F" ,this);

    buttonA->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonC->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonD->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonE->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonF->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(buttonA, 0, 0);
    layout->addWidget(buttonB, 1, 0);
    layout->addWidget(buttonC, 2, 0);
    layout->addWidget(buttonD, 3, 0);
    layout->addWidget(buttonE, 4, 0);
    layout->addWidget(buttonF, 5, 0);

    // Change the object name to use a brighter stylesheet
    buttonA->setObjectName("numerical");
    buttonB->setObjectName("numerical");
    buttonC->setObjectName("numerical");
    buttonD->setObjectName("numerical");
    buttonE->setObjectName("numerical");
    buttonF->setObjectName("numerical");

    // Connect to main signal
    QObject::connect(buttonA,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::A);});
    QObject::connect(buttonB,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::B);});
    QObject::connect(buttonC,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::C);});
    QObject::connect(buttonD,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::D);});
    QObject::connect(buttonE,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::E);});
    QObject::connect(buttonF,   &QPushButton::pressed, [&](){emit numericalButtonPressed(Calc::NumberPad::F);});

    // Buttons shortcuts
    buttonA->setShortcut(QKeySequence("A"));
    buttonB->setShortcut(QKeySequence("B"));
    buttonC->setShortcut(QKeySequence("C"));
    buttonD->setShortcut(QKeySequence("D"));
    buttonE->setShortcut(QKeySequence("E"));
    buttonF->setShortcut(QKeySequence("F"));

}

void DecNumberButtons::setButtonsEnabled(Calc::NumeralSystem system)
{
    // This below is really ugly but at the same time its very clear and explicit
    switch (system) {
    case Calc::NumeralSystem::Hex:
        button0->setEnabled(true);
        button1->setEnabled(true);
        button2->setEnabled(true);
        button3->setEnabled(true);
        button4->setEnabled(true);
        button5->setEnabled(true);
        button6->setEnabled(true);
        button7->setEnabled(true);
        button8->setEnabled(true);
        button9->setEnabled(true);
        break;
    case Calc::NumeralSystem::Dec:
        button0->setEnabled(true);
        button1->setEnabled(true);
        button2->setEnabled(true);
        button3->setEnabled(true);
        button4->setEnabled(true);
        button5->setEnabled(true);
        button6->setEnabled(true);
        button7->setEnabled(true);
        button8->setEnabled(true);
        button9->setEnabled(true);
        break;
    case Calc::NumeralSystem::Oct:
        button0->setEnabled(true);
        button1->setEnabled(true);
        button2->setEnabled(true);
        button3->setEnabled(true);
        button4->setEnabled(true);
        button5->setEnabled(true);
        button6->setEnabled(true);
        button7->setEnabled(true);
        button8->setEnabled(false);
        button9->setEnabled(false);
        break;
    case Calc::NumeralSystem::Bin:
        button0->setEnabled(true);
        button1->setEnabled(true);
        button2->setEnabled(false);
        button3->setEnabled(false);
        button4->setEnabled(false);
        button5->setEnabled(false);
        button6->setEnabled(false);
        button7->setEnabled(false);
        button8->setEnabled(false);
        button9->setEnabled(false);
        break;
    }
}

void HexNumberButtons::setButtonsEnabled(bool enabled)
{
    buttonA->setEnabled(enabled);
    buttonB->setEnabled(enabled);
    buttonC->setEnabled(enabled);
    buttonD->setEnabled(enabled);
    buttonE->setEnabled(enabled);
    buttonF->setEnabled(enabled);
}
