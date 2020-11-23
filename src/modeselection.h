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
    QRadioButton* nsHex;
    QRadioButton* nsDec;
    QRadioButton* nsOct;
    QRadioButton* nsBin;

    QWidget* precisionSelection;
    QRadioButton* p64bit;
    QRadioButton* p32bit;
    QRadioButton* p16bit;
    QRadioButton* p8bit;

signals:
    void numSystemChanged(Calc::NumeralSystem numSystem);
    void precisionChanged(Calc::BitPrecision precision);

};

#endif // MODESELECTION_H
