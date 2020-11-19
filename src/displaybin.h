#ifndef DISPLAYBIN_H
#define DISPLAYBIN_H

#include <QWidget>
#include "bitlabel.h"
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#define NUMBER_OF_BITS 64


class DisplayBin : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayBin(QWidget *parent = nullptr);

private:
    QVector<BitLabel *> labels;
    void paintEvent(QPaintEvent *) {
            QStyleOption opt;
            opt.init(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }
signals:

};

#endif // DISPLAYBIN_H
