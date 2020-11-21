#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "globalinclude.h"

class MemoryButtons : public QWidget
{
    Q_OBJECT
public:
    explicit MemoryButtons(QWidget *parent = nullptr);
private:
    QPushButton* memClearButton;
    QPushButton* memRestoreButton;
    QPushButton* memSaveButton;
    QPushButton* memAddButton;
    QPushButton* memSubtractButton;

signals:
    void memoryButtonPressed(Calc::MemoryFunctions function);

};

