#ifndef ACTIONBAR_H
#define ACTIONBAR_H

#include <QWidget>
#include <QMenuBar>
#include "globalinclude.h"

class ActionBar : public QMenuBar
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    explicit ActionBar(QWidget *parent = nullptr);

signals:
    void toggleGroupNumbers();
    void copy();
    void paste();
    void help();
    void info();

};

#endif // ACTIONBAR_H
