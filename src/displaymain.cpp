#include "displaymain.h"

DisplayMain::DisplayMain(QWidget *parent) : QWidget(parent)
{
    displayText = new QLabel("0", this); //startup values set here and in class declaration

    displayText->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    displayText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
    font.setPixelSize(35);
    displayText->setFont(font);
}

void DisplayMain::setNumeralSystem(Calc::NumeralSystem sys)
{
    dispSystem = sys;
    switch (dispSystem) {

    case Calc::NumeralSystem::Oct:
    case Calc::NumeralSystem::Dec:
    case Calc::NumeralSystem::Hex:
    {
        QFont font;
        font.setPixelSize(35);
        displayText->setFont(font);
        break;
    }

    case Calc::NumeralSystem::Bin:
    {
        QFont font;
        font.setPixelSize(22);
        displayText->setFont(font);
        break;
    }
    }
    displayNumber(number);
}

void DisplayMain::toggleGroupNumbers()
{
    grouped = !grouped;
    displayNumber(number);
}

void DisplayMain::copyFromDisplay()
{
    QApplication::clipboard()->setText(displayText->text());
}

// This is the only function that we need right now
// later i might add a second label to display memory, last number and currently executed function
void DisplayMain::displayNumber(qint64 num)
{
    number = num;
    switch (dispSystem) {
    case Calc::NumeralSystem::Bin:
    {
        auto text = QString::fromStdString(std::bitset<64>(num).to_string());
        //remove leading zeros
        for(int i=0; i<text.length(); i++)
        {
            if(text.at(i) == "0")
            {
                text.remove(i, 1);
                i--;
            }
            else break;
        }
        if(grouped)
        {
            for(int i=text.length()-4; i>=0; i-=4)
            {
                text.insert(i, "   ");
            }
            if(text.length() > 32 + 7*3)    // 7*4 - space added in prev step
                text.insert(text.length()-32 - 7*3, "\n");
            displayText->setText(text);
        }
        else{
            if(text.length() > 32)
                text.insert(text.length()-32, "\n");
            displayText->setText(text);
        }
        break;
    }

    case Calc::NumeralSystem::Oct:
    {
        auto text = QString::number(num, 8);
        if(grouped)
            for(int i=text.length()-3; i>=0; i-=3)
            {
                text.insert(i, " ");
            }
        displayText->setText(text);
        break;
    }

    case Calc::NumeralSystem::Dec:
    {
        auto text = QString::number(num);
        if(grouped)
            for(int i=text.length()-3; i>=0; i-=3)
            {
                text.insert(i, " ");
            }
        displayText->setText(text);
        break;
    }

    case Calc::NumeralSystem::Hex:
    {
        auto text = QString::number(num, 16).toUpper();
        if(grouped)
            for(int i=text.length()-4; i>=0; i-=4)
            {
                text.insert(i, " ");
            }
        displayText->setText(text);
        break;
    }
    }
}

