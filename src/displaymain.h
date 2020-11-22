#ifndef DISPLAYMAIN_H
#define DISPLAYMAIN_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include "globalinclude.h"

class DisplayMain : public QWidget
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    explicit DisplayMain(QWidget *parent = nullptr);

private:
    QLabel* displayText;
    void paintEvent(QPaintEvent *) {
            QStyleOption opt;
            opt.init(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }

public slots:
    void displayNumber(qint64 number, Calc::NumeralSystem dispSystem);

};

#endif // DISPLAYMAIN_H
