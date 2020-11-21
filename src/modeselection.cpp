#include "modeselection.h"

ModeSelection::ModeSelection(QWidget *parent) : QWidget(parent)
{
    numSystemSelection = new QWidget(this);
    precisionSelection = new QWidget(this);
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->addWidget(numSystemSelection, 0, 0);
    layout->addWidget(precisionSelection, 1, 0);

    numSystemSelection->setMinimumWidth(50);
    numSystemSelection->setMinimumHeight(120);
    numSystemSelection->setObjectName(QString("Box1"));
    numSystemSelection->setStyleSheet( "QWidget#Box1 { "
                         "border: 1px solid black;"
                         "border-radius: 4px;"
                         "}");
    precisionSelection->setMinimumWidth(50);
    precisionSelection->setMinimumHeight(120);
    precisionSelection->setObjectName(QString("Box2"));
    precisionSelection->setStyleSheet( "QWidget#Box2 { "
                         "border: 1px solid black;"
                         "border-radius: 4px;"
                         "}");


    //Numeral system buttons
    auto sysLayout = new QGridLayout(numSystemSelection);
    numSystemSelection->setLayout(sysLayout);
    auto sysGroup = new QButtonGroup(numSystemSelection);
    sysGroup->setExclusive(true);

    auto nsHex = new QRadioButton("Hex", numSystemSelection);
    sysLayout->addWidget(nsHex, 0, 0);
    sysGroup->addButton(nsHex);

    auto nsDec = new QRadioButton("Dec", numSystemSelection);
    nsDec->setChecked(true);
    sysLayout->addWidget(nsDec, 1, 0);
    sysGroup->addButton(nsDec);

    auto nsOct = new QRadioButton("Oct", numSystemSelection);
    sysLayout->addWidget(nsOct, 2, 0);
    sysGroup->addButton(nsOct);

    auto nsBin = new QRadioButton("Bin", numSystemSelection);
    sysLayout->addWidget(nsBin, 3, 0);
    sysGroup->addButton(nsBin);

    QObject::connect(nsHex, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit numSystemChanged(Calc::NumeralSystem::Hex);});
    QObject::connect(nsDec, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit numSystemChanged(Calc::NumeralSystem::Dec);});
    QObject::connect(nsOct, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit numSystemChanged(Calc::NumeralSystem::Oct);});
    QObject::connect(nsBin, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit numSystemChanged(Calc::NumeralSystem::Bin);});


    //Precision buttons
    auto precLayout = new QGridLayout(precisionSelection);
    precisionSelection->setLayout(precLayout);
    auto precGroup = new QButtonGroup(precisionSelection);
    precGroup->setExclusive(true);

    auto p64bit = new QRadioButton("64bit", precisionSelection);
    precLayout->addWidget(p64bit, 0, 0);
    precGroup->addButton(p64bit);
    p64bit->setChecked(true);

    auto p32bit = new QRadioButton("32bit", precisionSelection);
    precLayout->addWidget(p32bit, 1, 0);
    precGroup->addButton(p32bit);

    auto p16bit = new QRadioButton("16bit", precisionSelection);
    precLayout->addWidget(p16bit, 2, 0);
    precGroup->addButton(p16bit);

    auto p8bit = new QRadioButton(" 8bit", precisionSelection);
    precLayout->addWidget(p8bit, 3, 0);
    precGroup->addButton(p8bit);

    QObject::connect(p64bit, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit precisionChanged(Calc::BitPrecision::_64bit);});
    QObject::connect(p32bit, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit precisionChanged(Calc::BitPrecision::_32bit);});
    QObject::connect(p16bit, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit precisionChanged(Calc::BitPrecision::_16bit);});
    QObject::connect(p8bit, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit precisionChanged(Calc::BitPrecision::_8bit);});

}
