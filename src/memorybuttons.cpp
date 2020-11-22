#include "memorybuttons.h"

MemoryButtons::MemoryButtons(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setSpacing(5);
    setLayout(layout);

    memClearButton =    new QPushButton("MC" ,this);
    memRestoreButton =  new QPushButton("MR" ,this);
    memSaveButton =     new QPushButton("MS" ,this);
    memAddButton =      new QPushButton("M+" ,this);
    memSubtractButton = new QPushButton("M-" ,this);

    memClearButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    memRestoreButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    memSaveButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    memAddButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    memSubtractButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(memClearButton,    0, 0);
    layout->addWidget(memRestoreButton,  0, 1);
    layout->addWidget(memSaveButton,     0, 2);
    layout->addWidget(memAddButton,      0, 3);
    layout->addWidget(memSubtractButton, 0, 4);

    //Connecting buttons to main signal
    QObject::connect(memClearButton,    &QPushButton::pressed, [&](){emit memoryButtonPressed(Calc::MemoryFunctions::_memClear);});
    QObject::connect(memRestoreButton,  &QPushButton::pressed, [&](){emit memoryButtonPressed(Calc::MemoryFunctions::_memRestore);});
    QObject::connect(memSaveButton,     &QPushButton::pressed, [&](){emit memoryButtonPressed(Calc::MemoryFunctions::_memSave);});
    QObject::connect(memAddButton,      &QPushButton::pressed, [&](){emit memoryButtonPressed(Calc::MemoryFunctions::_memAdd);});
    QObject::connect(memSubtractButton, &QPushButton::pressed, [&](){emit memoryButtonPressed(Calc::MemoryFunctions::_memSubtract);});

    //Button shortcuts
    memClearButton->setShortcut(QKeySequence("Ctrl+L"));
    memRestoreButton->setShortcut(QKeySequence("Ctrl+R"));
    memSaveButton->setShortcut(QKeySequence("Ctrl+M"));
    memAddButton->setShortcut(QKeySequence("Ctrl+P"));
    memSubtractButton->setShortcut(QKeySequence("Ctrl+Q"));


}
