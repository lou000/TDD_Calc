﻿#ifndef DISPLAYMAIN_H
#define DISPLAYMAIN_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>

enum NumeralSystem{
    Hex,
    Dec,
    Oct,
    Bin
};

class DisplayMain : public QWidget
{
    Q_OBJECT
    friend class Tests;

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
    void displayNumber(qint64 number, NumeralSystem dispSystem);

};

#endif // DISPLAYMAIN_H
