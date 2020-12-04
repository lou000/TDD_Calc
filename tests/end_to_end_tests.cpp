#include "../src/calcmainwindow.h"
#include "../src/windows_mess.h"
#include <QClipboard>
#include <QGuiApplication>
#include <QtTest/QtTest>

struct KeyInput{
    KeyInput(Qt::Key k, Qt::KeyboardModifier m) : key(k), mod(m) {};
    Qt::Key key;
    Qt::KeyboardModifier mod;
};

static QVector<KeyInput> numberKeyPool{
    KeyInput(Qt::Key_0, Qt::NoModifier),
    KeyInput(Qt::Key_1, Qt::NoModifier),
    KeyInput(Qt::Key_2, Qt::NoModifier),
    KeyInput(Qt::Key_3, Qt::NoModifier),
    KeyInput(Qt::Key_4, Qt::NoModifier),
    KeyInput(Qt::Key_5, Qt::NoModifier),
    KeyInput(Qt::Key_6, Qt::NoModifier),
    KeyInput(Qt::Key_7, Qt::NoModifier),
    KeyInput(Qt::Key_8, Qt::NoModifier),
    KeyInput(Qt::Key_9, Qt::NoModifier),
    KeyInput(Qt::Key_A, Qt::NoModifier),
    KeyInput(Qt::Key_B, Qt::NoModifier),
    KeyInput(Qt::Key_C, Qt::NoModifier),
    KeyInput(Qt::Key_D, Qt::NoModifier),
    KeyInput(Qt::Key_E, Qt::NoModifier),
    KeyInput(Qt::Key_F, Qt::NoModifier),
    KeyInput(Qt::Key_Backspace, Qt::NoModifier),
    KeyInput(Qt::Key_Escape, Qt::NoModifier),
    KeyInput(Qt::Key_Delete, Qt::NoModifier)
};

static QVector<KeyInput> functionKeyPool{
    KeyInput(Qt::Key_5, Qt::ShiftModifier),
//    KeyInput(Qt::Key_9, Qt::ShiftModifier), not yet implemented
//    KeyInput(Qt::Key_0, Qt::ShiftModifier),
//    KeyInput(Qt::Key_J, Qt::NoModifier), diffirent hotkeys
//    KeyInput(Qt::Key_K, Qt::NoModifier),
    KeyInput(Qt::Key_Backslash, Qt::ShiftModifier),
    KeyInput(Qt::Key_6, Qt::ShiftModifier),
//    KeyInput(Qt::Key_Comma, Qt::ShiftModifier),diffirent hotkeys
//    KeyInput(Qt::Key_Period, Qt::ShiftModifier),
//    KeyInput(Qt::Key_1, Qt::ShiftModifier),
    KeyInput(Qt::Key_7, Qt::ShiftModifier),

    KeyInput(Qt::Key_F9, Qt::NoModifier),
    KeyInput(Qt::Key_Slash, Qt::NoModifier),
    KeyInput(Qt::Key_Asterisk, Qt::NoModifier),
    KeyInput(Qt::Key_Minus, Qt::NoModifier),
    KeyInput(Qt::Key_Plus, Qt::NoModifier)
};

bool waitForWindowToActivate(HWND win, int ms)
{
    return QTest::qWaitFor([=](){setWindowToForeground(win);
                              return GetForegroundWindow() == win;
                             }, ms);
}

bool waitForClipboardValue(int ms)
{
    return QTest::qWaitFor([=](){return QApplication::clipboard()->text() != "";}, ms);
}

bool compareCalcOutputs(CalcMainWindow* mainWindow, HWND origCalc, KeyInput input, int delay)
{
    // Send key to our calculator
    setWindowToForeground((HWND)mainWindow->effectiveWinId());
    if (!waitForWindowToActivate((HWND)mainWindow->effectiveWinId(), 5000)) return false;
    sendKeyToActiveWindow(input.key, input.mod);
    QTest::qWait(delay);

    //Read value via ctrl + c
    QString myVal;
    sendKeyToActiveWindow(Qt::Key_C, Qt::ControlModifier);
    if(waitForClipboardValue(5000))
        myVal = QApplication::clipboard()->text();
    else
        myVal = "Failed to copy output from myCalc or output is empty";
    QApplication::clipboard()->clear();

    // Send key to calculator reference
    setWindowToForeground(origCalc);
    if(!waitForWindowToActivate(origCalc, 5000)) return false;
    QTest::qWait(delay);
    sendKeyToActiveWindow(input.key, input.mod);
    QTest::qWait(delay);

    //Read value via ctrl + c
    QString origVal;
    sendKeyToActiveWindow(Qt::Key_C, Qt::ControlModifier);
    if(waitForClipboardValue(5000))
        origVal = QApplication::clipboard()->text();
    else
        origVal = "Failed to copy output from myCalc or output is empty";
    QApplication::clipboard()->clear();

    qDebug()<<"Input - "<<input.key<<input.mod;
    qDebug()<<"Output - our:"<<myVal<<"   ref:"<<origVal;
    return origVal == myVal;
}

void endToEndFuzzTest(CalcMainWindow* mainWindow, int iterations, int delay)
{
    mainWindow->show();
    QVERIFY(QTest::qWaitForWindowExposed(mainWindow));

    QVector<QPair<HWND, QString>> winList;
    EnumDesktopWindows(NULL, enumWindowCallback, reinterpret_cast<LPARAM>(&winList));
    HWND origCalc;
    for(auto pair : winList)
        if(pair.second == "Kalkulator")
            origCalc = pair.first;
    if(!origCalc)
        QVERIFY(0);

    auto seed = QDateTime::currentMSecsSinceEpoch();
    qDebug()<<"endToEndFuzzTest seed is:"<<seed;
    QRandomGenerator rnd(seed);

    QVERIFY(waitForWindowToActivate(origCalc, 5000));
    sendKeyToActiveWindow(Qt::Key_Escape, Qt::NoModifier);

    for(int i=0; i<iterations; i++)
    {
        auto actionType = rnd.bounded(1, 3);

        // Press some numbers
        if(actionType == 1)
        {
            qDebug()<<"\n\nNumbers!";
            auto numIter = rnd.bounded(1, 5);
            for(int i=0; i<numIter; i++)
            {
                auto numberInput = numberKeyPool.at(rnd.bounded(0, numberKeyPool.length()-1));
                QVERIFY(compareCalcOutputs(mainWindow, origCalc, numberInput, delay));
            }
        }
        // Press function key
        else if(actionType == 2)
        {
            qDebug()<<"\n\nFunction!";
            auto functInput = functionKeyPool.at(rnd.bounded(0, functionKeyPool.length()-1));
            QVERIFY(compareCalcOutputs(mainWindow, origCalc, functInput, delay));
        }
    }
}
