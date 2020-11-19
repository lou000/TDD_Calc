#include "displaybin.h"

DisplayBin::DisplayBin(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 0, 10, 0);
    this->setLayout(layout);


    for(int i=0; i<NUMBER_OF_BITS; i++)
    {
        labels.append(new BitLabel(i, this));
    }


    int y = 0;
    for(int row=0; row<2; row++)
    {
        int x = 0;
        for(int group = 0; group<8; group++)
        {
            for(int pos = 0; pos<4; pos++)
            {
                int index = NUMBER_OF_BITS - (pos + group*4 + row*32) - 1;
                layout->addWidget(labels.at(index), y, x);
                x++;
            }
            if(group<7)
            {
                layout->addItem(new QSpacerItem(25, 0), y, x);
                x++;
            }
        }
        y++;
        layout->addItem(new QSpacerItem(0, 20), y, x);
        y++;
    }
    this->setObjectName(QString("Box"));
    this->setStyleSheet( "QWidget#Box { "
                         "background-color:#404244;"
                         "border: 1px solid black;"
                         "border-radius: 4px;"
                         "}");
}

