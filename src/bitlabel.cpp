#include "bitlabel.h"

BitLabel::BitLabel(int bitNumber, QWidget* parent) : QLabel(parent)
{
    this->setText("0");
    this->bitPosition = bitNumber;
    this->setContentsMargins(0, 0, 0, 0);
    this->setMargin(0);
}

void BitLabel::flipBit()
{

    this->setText(QString::number(!static_cast<bool>(this->text().toInt())));
}

void BitLabel::setBit(bool val)
{
    this->setText(QString::number(val));
}



void BitLabel::mousePressEvent(QMouseEvent *event)
{
    flipBit();
    event->accept();
    emit clicked(this->bitPosition);
}


