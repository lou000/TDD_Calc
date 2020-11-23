#include "modeselection.h"

ModeSelection::ModeSelection(QWidget *parent) : QWidget(parent)
{
    numSystemSelection = new QWidget(this);
    precisionSelection = new QWidget(this);
    auto layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->addWidget(numSystemSelection, 0, 0);
    layout->addWidget(precisionSelection, 1, 0);


    //Setup number system button group
    numSystemSelection->setMinimumWidth(50);
    numSystemSelection->setMinimumHeight(120);
    numSystemSelection->setObjectName(QString("Box1"));
    numSystemSelection->setStyleSheet( "QWidget#Box1 { "
                         "border: 1px solid black;"
                         "border-radius: 4px;"
                         "}");
    auto sysLayout = new QGridLayout(numSystemSelection);
    auto sysGroup = new QButtonGroup(numSystemSelection);
    numSystemSelection->setLayout(sysLayout);
    sysGroup->setExclusive(true);

    //Setup precision button group
    precisionSelection->setMinimumWidth(50);
    precisionSelection->setMinimumHeight(120);
    precisionSelection->setObjectName(QString("Box2"));
    precisionSelection->setStyleSheet( "QWidget#Box2 { "
                         "border: 1px solid black;"
                         "border-radius: 4px;"
                         "}");
    auto precLayout = new QGridLayout(precisionSelection);
    auto precGroup = new QButtonGroup(precisionSelection);
    precisionSelection->setLayout(precLayout);
    precGroup->setExclusive(true);


    ///
    /// Numeral system buttons
    ///
    nsHex = new QRadioButton("Hex", numSystemSelection);
    nsDec = new QRadioButton("Dec", numSystemSelection);
    nsOct = new QRadioButton("Oct", numSystemSelection);
    nsBin = new QRadioButton("Bin", numSystemSelection);

    sysLayout->addWidget(nsHex, 0, 0);
    sysLayout->addWidget(nsDec, 1, 0);
    sysLayout->addWidget(nsOct, 2, 0);
    sysLayout->addWidget(nsBin, 3, 0);

    sysGroup->addButton(nsHex);
    sysGroup->addButton(nsDec);
    sysGroup->addButton(nsOct);
    sysGroup->addButton(nsBin);

    // Set default at startup
    nsDec->setChecked(true);

    // Connect to main signal
    QObject::connect(nsHex, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit numSystemChanged(Calc::NumeralSystem::Hex);});
    QObject::connect(nsDec, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit numSystemChanged(Calc::NumeralSystem::Dec);});
    QObject::connect(nsOct, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit numSystemChanged(Calc::NumeralSystem::Oct);});
    QObject::connect(nsBin, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit numSystemChanged(Calc::NumeralSystem::Bin);});

    //Button shortcuts
    nsHex->setShortcut(QKeySequence("F5"));
    nsDec->setShortcut(QKeySequence("F6"));
    nsOct->setShortcut(QKeySequence("F7"));
    nsBin->setShortcut(QKeySequence("F8"));


    ///
    /// Precision buttons
    ///
    p64bit = new QRadioButton("64bit", precisionSelection);
    p32bit = new QRadioButton("32bit", precisionSelection);
    p16bit = new QRadioButton("16bit", precisionSelection);
    p8bit = new QRadioButton(" 8bit", precisionSelection);

    precLayout->addWidget(p64bit, 0, 0);
    precLayout->addWidget(p32bit, 1, 0);
    precLayout->addWidget(p16bit, 2, 0);
    precLayout->addWidget(p8bit, 3, 0);

    precGroup->addButton(p64bit);
    precGroup->addButton(p32bit);
    precGroup->addButton(p16bit);
    precGroup->addButton(p8bit);

    // Set default at startup
    p64bit->setChecked(true);

    // Connect to main signal
    QObject::connect(p64bit, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit precisionChanged(Calc::BitPrecision::_64bit);});
    QObject::connect(p32bit, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit precisionChanged(Calc::BitPrecision::_32bit);});
    QObject::connect(p16bit, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit precisionChanged(Calc::BitPrecision::_16bit);});
    QObject::connect(p8bit, &QRadioButton::toggled, this,
                     [&](bool checked){if(checked) emit precisionChanged(Calc::BitPrecision::_8bit);});

    // Button shortcuts
    p64bit->setShortcut(QKeySequence("F12"));
    p32bit->setShortcut(QKeySequence("F2"));
    p16bit->setShortcut(QKeySequence("F3"));
    p8bit->setShortcut(QKeySequence("F4"));

}
