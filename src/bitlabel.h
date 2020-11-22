#pragma once
#include <QLabel>
#include <QMouseEvent>
#include "globalinclude.h"

class BitLabel : public QLabel
{
    Q_OBJECT
public:
    BitLabel(int bitNumber, QWidget* parent);
    void mousePressEvent(QMouseEvent* event);

private:
    int bitPosition = 0;

signals:
    void clicked(int bitPosition);

public slots:
    void flipBit();
    void setBit(bool val);
};

