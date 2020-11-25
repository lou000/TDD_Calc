#ifndef DISPLAYMAIN_H
#define DISPLAYMAIN_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include <QClipboard>
#include <bitset>
#include "globalinclude.h"

class DisplayMain : public QWidget
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    explicit DisplayMain(QWidget *parent = nullptr);

private:
    qint64 number = 0;
    bool grouped = false;
    QLabel* displayText;
    Calc::NumeralSystem dispSystem = Calc::NumeralSystem::Dec;
    void paintEvent(QPaintEvent *) {
            QStyleOption opt;
            opt.init(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }

public slots:
    void setNumeralSystem(Calc::NumeralSystem sys);
    void displayNumber(qint64 number);
    void toggleGroupNumbers();
    // We can do the copy here but paste should go through controller
    // so it can be properly distribiuted to both displays and also
    // modified to appropriate precision
    void copyFromDisplay();

};

#endif // DISPLAYMAIN_H
