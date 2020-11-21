#include "functionbuttons.h"

LeftFunctionButtons::LeftFunctionButtons(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setSpacing(5);
    setLayout(layout);


    paranthesesIndicator = new QLabel("", this);
    paranthesesIndicator->setAlignment(Qt::AlignCenter);
    paranthesesIndicator->setObjectName(QString("Box"));
    paranthesesIndicator->setStyleSheet( "QWidget#Box { "
                         "background-color:#404244;"
                         "border: 1px solid black;"
                         "border-radius: 4px;"
                         "}");

    modButton = new QPushButton("Mod", this);
    paranthesesOpenButton = new QPushButton("(", this);
    paranthesesCloseButton = new QPushButton(")", this);
    rolButton = new QPushButton("RoL", this);
    rorButton = new QPushButton("RoR", this);
    orButton  = new QPushButton("Or", this);
    xorButton = new QPushButton("Xor", this);
    lshButton = new QPushButton("Lsh", this);
    rshButton = new QPushButton("Rsh", this);
    notButton = new QPushButton("Not", this);
    andButton = new QPushButton("And", this);

    paranthesesIndicator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    modButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    paranthesesOpenButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    paranthesesCloseButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rolButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rorButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    orButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    xorButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lshButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rshButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    notButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    andButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(paranthesesIndicator, 0, 0);
    layout->addWidget(modButton, 0, 1);
    layout->addWidget(paranthesesOpenButton, 1, 0);
    layout->addWidget(paranthesesCloseButton, 1, 1);
    layout->addWidget(rolButton, 2, 0);
    layout->addWidget(rorButton, 2, 1);
    layout->addWidget(orButton,  3, 0);
    layout->addWidget(xorButton, 3, 1);
    layout->addWidget(lshButton, 4, 0);
    layout->addWidget(rshButton, 4, 1);
    layout->addWidget(notButton, 5, 0);
    layout->addWidget(andButton, 5, 1);


    QObject::connect(modButton, &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_mod);});
    QObject::connect(rolButton, &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_rol);});
    QObject::connect(rorButton, &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_ror);});
    QObject::connect(orButton,  &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_or );});
    QObject::connect(xorButton, &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_xor);});
    QObject::connect(lshButton, &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_lsh);});
    QObject::connect(rshButton, &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_rsh);});
    QObject::connect(notButton, &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_not);});
    QObject::connect(andButton, &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_and);});

    // For now we connect the parantheses buttons to signal and to display
    // in the future we may want to control the display from somewhere else
    // I dont fully understant the functionality so this UI and slots API may need more work.
    QObject::connect(paranthesesOpenButton, &QPushButton::pressed,  [&](){
        numOfParanthesesOpened++;
        paranthesesIndicator->setText("(=" + QString::number(numOfParanthesesOpened));
        emit functionButtonPressed(Calc::Functions::_parOpen);
    });
    QObject::connect(paranthesesCloseButton, &QPushButton::pressed, [&](){
        numOfParanthesesOpened--;
        if(numOfParanthesesOpened<=0)
        {
            numOfParanthesesOpened = 0;
            paranthesesIndicator->setText("");
        }
        else
            paranthesesIndicator->setText("(=" + QString::number(numOfParanthesesOpened));

        emit functionButtonPressed(Calc::Functions::_parClose);
    });
}

// This slot below clears the parantheses count and display
// it should be called when user presses "C" button or "=" button and maybe more...
void LeftFunctionButtons::clearParanthesesCount()
{
    numOfParanthesesOpened = 0;
    paranthesesIndicator->setText("");
}

RightFunctionButtons::RightFunctionButtons(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setSpacing(5);
    setLayout(layout);

    invertButton = new QPushButton("+/-" ,this);
    deadButton1 = new QPushButton("root" ,this);
    divideButton = new QPushButton("/" ,this);
    deadButton2 = new QPushButton("%" ,this);
    multiplyButton = new QPushButton("*" ,this);
    deadButton3 = new QPushButton("1/x" ,this);
    subtractButton = new QPushButton("-" ,this);
    addButton = new QPushButton("+" ,this);
    equalButton = new QPushButton("=" ,this);

    invertButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    deadButton1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    divideButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    deadButton2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    multiplyButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    deadButton3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    subtractButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    equalButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(invertButton,   0, 0);
    layout->addWidget(deadButton1,    0, 1);
    layout->addWidget(divideButton,   1, 0);
    layout->addWidget(deadButton2,    1, 1);
    layout->addWidget(multiplyButton, 2, 0);
    layout->addWidget(deadButton3,    2, 1);
    layout->addWidget(subtractButton, 3, 0);
    layout->addWidget(addButton,      4, 0);
    layout->addWidget(equalButton,    3, 1, 2, 1);

    //Disable the disabled buttons...
    deadButton1->setEnabled(false);
    deadButton2->setEnabled(false);
    deadButton3->setEnabled(false);

    QObject::connect(invertButton,   &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_mod);});
    QObject::connect(divideButton,   &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_rol);});
    QObject::connect(multiplyButton, &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_ror);});
    QObject::connect(subtractButton, &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_or );});
    QObject::connect(addButton,      &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_xor);});
    QObject::connect(equalButton,    &QPushButton::pressed, [&](){emit functionButtonPressed(Calc::Functions::_lsh);});

}
