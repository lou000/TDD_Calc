#include "displaybin.h"

DisplayBin::DisplayBin(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 10, 10, 10);
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
        y+=2;
    }


    auto label1 =  new QLabel("6");
    label1->setObjectName("binDisp");
    auto label2 =  new QLabel("3");
    label2->setObjectName("binDisp");
    auto label3 =  new QLabel("4");
    label3->setObjectName("binDisp");
    auto label4 =  new QLabel("7");
    label4->setObjectName("binDisp");
    auto label5 =  new QLabel("3");
    label5->setObjectName("binDisp");
    auto label6 =  new QLabel("2");
    label6->setObjectName("binDisp");
    auto label7 =  new QLabel("3");
    label7->setObjectName("binDisp");
    auto label8 =  new QLabel("1");
    label8->setObjectName("binDisp");
    auto label9 =  new QLabel("1");
    label9->setObjectName("binDisp");
    auto label10 =  new QLabel("5");
    label10->setObjectName("binDisp");
    auto label11 =  new QLabel("0");
    label11->setObjectName("binDisp");

    layout->addWidget(label1, 1, 0);
    layout->addWidget(label2, 1, 1);

    layout->addWidget(label3, 1, 17);
    layout->addWidget(label4, 1, 18);

    layout->addWidget(label5, 1, 37);
    layout->addWidget(label6, 1, 38);

    layout->addWidget(label7, 3, 0);
    layout->addWidget(label8, 3, 1);

    layout->addWidget(label9, 3, 17);
    layout->addWidget(label10, 3, 18);

    layout->addWidget(label11,  3, 38);

    this->setObjectName(QString("Box"));
    this->setStyleSheet( "QWidget#Box { "
                         "background-color:#404244;"
                         "border: 1px solid black;"
                         "border-radius: 4px;"
                         "}");
}

