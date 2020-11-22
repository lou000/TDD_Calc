#ifndef MODESELECTION_H
#define MODESELECTION_H

#include <QWidget>
#include <QGridLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include "globalinclude.h"

class ModeSelection : public QWidget
{
    Q_OBJECT
    MAKE_TESTABLE

public:
    explicit ModeSelection(QWidget *parent = nullptr);

private:
    QWidget* numSystemSelection;
    QWidget* precisionSelection;

signals:
    void numSystemChanged(Calc::NumeralSystem numSystem);
    void precisionChanged(Calc::BitPrecision precision);

};

#endif // MODESELECTION_H
