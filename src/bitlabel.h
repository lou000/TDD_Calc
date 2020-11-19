#ifndef BITLABEL_H
#define BITLABEL_H

#include <QLabel>
#include <QMouseEvent>

class BitLabel : public QLabel
{
    Q_OBJECT
public:
    BitLabel(int bitNumber, QWidget* parent);
    void flipBit();
    void setBit(bool val);
    void mousePressEvent(QMouseEvent* event);

private:
    int bitNumber = 0;

signals:
    void clicked();
};

#endif // BITLABEL_H
