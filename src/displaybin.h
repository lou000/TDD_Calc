#ifndef DISPLAYBIN_H
#define DISPLAYBIN_H

#include <QWidget>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include "bitlabel.h"
#include "globalinclude.h"



class DisplayBin : public QWidget
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    explicit DisplayBin(QWidget *parent = nullptr);

private:
    QVector<BitLabel*> labels;  // The labels are stored in reverse bit order
    QVector<QLabel*> helperLabels;
    void paintEvent(QPaintEvent *) {
            QStyleOption opt;
            opt.init(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }
signals:
    void bitFlipped(int bitPosition);

public slots:
    void setBits(qint64 number);
    void changeDisplayPrecision(Calc::BitPrecision precision);

};

#endif // DISPLAYBIN_H
