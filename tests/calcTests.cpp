#include <QtTest/QtTest>
#include "../src/calcmainwindow.h"

// add necessary includes here

class Tests : public QObject
{
    Q_OBJECT

    CalcMainWindow* mainWindow;
public:
    Tests();
    ~Tests();

private slots:
    void testInitCalcMainWindow();

};

Tests::Tests()
{
    mainWindow = new CalcMainWindow();
}

Tests::~Tests()
{
    delete mainWindow;
}

void Tests::testInitCalcMainWindow()
{
    QVERIFY(mainWindow->mainDisplay);
    QVERIFY(mainWindow->binDisplay);
    QVERIFY(mainWindow->modeSelection);
    QVERIFY(mainWindow->functionButtons);
    QVERIFY(mainWindow->numberButtons);
    QVERIFY(mainWindow->actionBar);
}

QTEST_MAIN(Tests)

#include "calcTests.moc"
