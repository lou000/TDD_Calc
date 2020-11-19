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


    auto bottomSpace = new QWidget(this);
    bottomSpace->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto layout = new QGridLayout(centralWidget);
    layout->setContentsMargins(10, 30, 10, 10);
    layout->addWidget(mainDisplay, 0, 0);
    layout->addWidget(binDisplay, 1, 0);
    layout->addWidget(bottomSpace, 2, 0);
    mainDisplay->setMinimumHeight(70);
    binDisplay->setMinimumHeight(90);
    centralWidget->setLayout(layout);

//    QObject::connect(actionBar, &ActionBar::copy, [&](){mainDisplay->setStyleSheet("background-color: red");});


}

CalcMainWindow::~CalcMainWindow()
{
}

