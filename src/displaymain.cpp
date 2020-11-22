#include "displaymain.h"

DisplayMain::DisplayMain(QWidget *parent) : QWidget(parent)
{
    displayText = new QLabel("0", this);
    displayText->setAlignment(Qt::AlignRight);
    auto layout = new QGridLayout(this);
    layout->addWidget(displayText);
    this->setLayout(layout);
    this->setObjectName(QString("Box"));
    this->setStyleSheet( "QWidget#Box { "
                         "background-color:#4A4B4C;"
                         "border: 1px solid black;"
                         "border-radius: 4px;"
                         "}");

    QFont font;
    font.setPixelSize(50);
    displayText->setFont(font);
}

// This is the only function that we need right now
// later i might add a second label to display memory, last number and currently executed function
void DisplayMain::displayNumber(qint64 number, Calc::NumeralSystem dispSystem)
{
    displayText->setText(QString::number(number));
}
