#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include "external/framelesswindow/framelesswindow.h"
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
    void testInitActionBar();
    void testActionBarShortcutsAndSignals();
    void testMainDisplayInit();

};

Tests::Tests()
{
    FramelessWindow* framelessWindow = new FramelessWindow();
    mainWindow = new CalcMainWindow(framelessWindow);
    framelessWindow->setContent(mainWindow);
    QObject::connect(mainWindow, &CalcMainWindow::move, framelessWindow, [=](int x, int y)
    {
        framelessWindow->move(x, y);
    });
    QObject::connect(mainWindow, &CalcMainWindow::show, framelessWindow, [=]
    {
        framelessWindow->show();
    });
}

Tests::~Tests()
{
    delete mainWindow;
}

void Tests::testInitCalcMainWindow()
{
    QVERIFY(mainWindow->mainDisplay);
//    QVERIFY(mainWindow->binDisplay);
//    QVERIFY(mainWindow->modeSelection);
//    QVERIFY(mainWindow->functionButtons);
//    QVERIFY(mainWindow->numberButtons);
    QVERIFY(mainWindow->actionBar);
}

void Tests::testInitActionBar()
{
    QCOMPARE(mainWindow->actionBar->actions().length(), 3);
    QCOMPARE(mainWindow->actionBar->actions().at(0)->text(), "View");
    QCOMPARE(mainWindow->actionBar->actions().at(1)->text(), "Edit");
    QCOMPARE(mainWindow->actionBar->actions().at(2)->text(), "Help");
}

void Tests::testActionBarShortcutsAndSignals()
{
    mainWindow->show();
    QVERIFY(QTest::qWaitForWindowExposed(mainWindow));

    QSignalSpy toggleGroupNumSpy(mainWindow->actionBar, &ActionBar::toggleGroupNumbers);
    QVERIFY(toggleGroupNumSpy.isValid());
    QTest::keyClick(mainWindow->actionBar, Qt::Key_G, Qt::ControlModifier);
    QCOMPARE(toggleGroupNumSpy.count(), 1);

    QSignalSpy copySpy(mainWindow->actionBar, &ActionBar::copy);
    QVERIFY(copySpy.isValid());
    QTest::keyClick(mainWindow, Qt::Key_C, Qt::ControlModifier);
    QCOMPARE(copySpy.count(), 1);

    QSignalSpy pasteSpy(mainWindow->actionBar, &ActionBar::paste);
    QVERIFY(pasteSpy.isValid());
    QTest::keyClick(mainWindow, Qt::Key_V, Qt::ControlModifier);
    QCOMPARE(pasteSpy.count(), 1);

    QSignalSpy helpSpy(mainWindow->actionBar, &ActionBar::help);
    QVERIFY(helpSpy.isValid());
    QTest::keyClick(mainWindow, Qt::Key_F1);
    QCOMPARE(helpSpy.count(), 1);
}

void Tests::testMainDisplayInit()
{
    QCOMPARE(mainWindow->mainDisplay->displayText->text(), "0");
}

QTEST_MAIN(Tests)

#include "calcTests.moc"
