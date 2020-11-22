#include "displaybin.h"

DisplayBin::DisplayBin(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 10, 10, 10);
    this->setLayout(layout);

    this->setObjectName(QString("Box"));
    this->setStyleSheet( "QWidget#Box { "
                         "background-color:#404244;"
                         "border: 1px solid black;"
                         "border-radius: 4px;"
                         "}");


    // Setup the binary display labels
    for(int i=0; i<NUMBER_OF_BITS; i++)
    {
        auto label = new BitLabel(i, this);
        auto policy = label->sizePolicy();
        policy.setRetainSizeWhenHidden(true); //make it so it doesnt shrink when hidden
        label->setSizePolicy(policy);
        labels.append(label);
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

    //Connect all labels to signal
    for(auto label : labels)
        QObject::connect(label, &BitLabel::clicked, this, [&](int bitPosition){emit bitFlipped(bitPosition);});


    // This below adds the small numbers that label bits 63, 47, 32, 31, 15, 0
    // each digit has to be separate to line up with the grid
    auto label1 =  new QLabel("6");
    auto policy = label1->sizePolicy();
    policy.setRetainSizeWhenHidden(true); //make it so it doesnt shrink when hidden
    label1->setSizePolicy(policy);
    auto label2 =  new QLabel("3");
    auto label3 =  new QLabel("4");
    auto label4 =  new QLabel("7");
    auto label5 =  new QLabel("3");
    auto label6 =  new QLabel("2");
    auto label7 =  new QLabel("3");
    auto label8 =  new QLabel("1");
    auto label9 =  new QLabel("1");
    auto label10 =  new QLabel("5");
    auto label11 =  new QLabel("0");

    label1->setObjectName("binDisp");
    label2->setObjectName("binDisp");
    label3->setObjectName("binDisp");
    label4->setObjectName("binDisp");
    label5->setObjectName("binDisp");
    label6->setObjectName("binDisp");
    label7->setObjectName("binDisp");
    label8->setObjectName("binDisp");
    label9->setObjectName("binDisp");
    label10->setObjectName("binDisp");
    label11->setObjectName("binDisp");

    layout->addWidget(label1, 1, 0);
    layout->addWidget(label2, 1, 1);
    layout->addWidget(label3, 1, 20);
    layout->addWidget(label4, 1, 21);
    layout->addWidget(label5, 1, 37);
    layout->addWidget(label6, 1, 38);
    layout->addWidget(label7, 3, 0);
    layout->addWidget(label8, 3, 1);
    layout->addWidget(label9, 3, 20);
    layout->addWidget(label10, 3, 21);
    layout->addWidget(label11,  3, 38);

    helperLabels.append(label11);
    helperLabels.append(label10);
    helperLabels.append(label9);
    helperLabels.append(label8);
    helperLabels.append(label7);
    helperLabels.append(label6);
    helperLabels.append(label5);
    helperLabels.append(label4);
    helperLabels.append(label3);
    helperLabels.append(label2);
    helperLabels.append(label1);


}

void DisplayBin::changeDisplayPrecision(Calc::BitPrecision precision)
{
    int cutoffBit = 0;
    int cutoffHLabel = 0;

    switch (precision) {

    case Calc::BitPrecision::_64bit:
        cutoffBit = 64;
        cutoffHLabel = 11;
        break;

    case Calc::BitPrecision::_32bit:
        cutoffBit = 32;
        cutoffHLabel = 5;
        break;

    case Calc::BitPrecision::_16bit:
        cutoffBit = 16;
        cutoffHLabel = 3;
        break;

    case Calc::BitPrecision::_8bit:
        cutoffBit = 8;
        cutoffHLabel = 1;
        break;
    }

    for(int i=0; i<NUMBER_OF_BITS; i++)
    {
        if(i>=cutoffBit)
            labels[i]->setVisible(false);
        else
            labels[i]->setVisible(true);
    }
    for(int i=0; i<helperLabels.length(); i++)
    {
        if(i>=cutoffHLabel)
            helperLabels[i]->setVisible(false);
        else
            helperLabels[i]->setVisible(true);
    }
}

void DisplayBin::setBits(quint64 number)
{
    for(int i=0; i<NUMBER_OF_BITS; i++)
        labels[i]->setBit(CHECK_BIT(number, i+1));
}

