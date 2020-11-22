#pragma once
#include <QLabel>
#include <QMouseEvent>
#include "globalinclude.h"

class BitLabel : public QLabel
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    BitLabel(int bitNumber, QWidget* parent);
    void mousePressEvent(QMouseEvent* event);
    int bitPosition(){ return m_bitPosition;}

private:
    int m_bitPosition = 0;

signals:
    void clicked(int bitPosition);

public slots:
    void flipBit();
    void setBit(bool val);
};

