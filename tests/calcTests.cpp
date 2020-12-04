#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <bitset>
#include "external/framelesswindow/framelesswindow.h"
#include "../src/calcmainwindow.h"
#include "../src/windows_mess.h"
#include "end_to_end_tests.cpp"

// add necessary includes here

class Tests : public QObject
{
    Q_OBJECT

    FramelessWindow* framelessWindow;
    CalcMainWindow* mainWindow;
    BitLabel* bitLabel;
public:
    Tests();
    ~Tests();
private:
    template <typename T, typename ...Args>
    void testShortcut(QWidget* widget, T* sender, void(T::*signal)(Args...), Qt::Key key, Qt::KeyboardModifier mod);

private slots:
    void cleanup();
    void testActionBarInit();
    void testActionBarSignals();
    void testActionBarFunctionality();
    void testBitLabelInit();
    void testBitLabelSignals();
    void testBitLabelFunctionality();
    void testCalcMainWindowInit();
//    void testCalcMainWindowSignals(); No signals to test
//    void testCalcMainWindowFunctionality(); No functionality to test
    void testDisplayBinInit();
    void testDisplayBinSignals();
    void testDisplayBinFunctionality();
    void testMainDisplayInit();
//    void testMainDisplaySignals(); No signals to test
    void testMainDisplayFunctionality();
    void testFunctionButtonsInit();
    void testFunctionButtonsSignals();
    void testFunctionButtonsFunctionality();
    void testMemoryButtonsInit();
    void testMemoryButtonsSignals();
    void testMemoryButtonsFunctionality();
    void testModeSelectionInit();
    void testModeSelectionSignals();
    void testModeSelectionsFunctionality();
    void testNumberButtonsInit();
    void testNumberButtonsSignals();
    void testNumberButtonsFunctionality();
    void testButtonShortcuts();

    void testCalculatorInit();
    void testCalculatorSignals();
    void testCalculatorFunctionality();


    void testEndToEndFuzz(){endToEndFuzzTest(mainWindow, 20, 100);};
};

Tests::Tests()
{
    framelessWindow = new FramelessWindow();
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

    bitLabel = new BitLabel(0);

    qRegisterMetaType<Calc::Functions>("Calc::Functions");
    qRegisterMetaType<Calc::NumeralSystem>("Calc::NumeralSystem");
    qRegisterMetaType<Calc::BitPrecision>("Calc::BitPrecision");
    qRegisterMetaType<Calc::MemoryFunctions>("Calc::MemoryFunctions");
    qRegisterMetaType<Calc::NumberPad>("Calc::NumberPad");
}

Tests::~Tests()
{
    delete mainWindow;
    delete framelessWindow;
}

void Tests::cleanup()
{
    delete mainWindow;
    framelessWindow->hide();
    delete framelessWindow;
    framelessWindow = new FramelessWindow();
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

    bitLabel = new BitLabel(0);

    qRegisterMetaType<Calc::Functions>("Calc::Functions");
    qRegisterMetaType<Calc::NumeralSystem>("Calc::NumeralSystem");
    qRegisterMetaType<Calc::BitPrecision>("Calc::BitPrecision");
}

void Tests::testActionBarInit()
{
    //Test all menus
    QCOMPARE(mainWindow->actionBar->menus.length(), 3);
    QCOMPARE(mainWindow->actionBar->menus.at(0)->title(), "View");
    QCOMPARE(mainWindow->actionBar->menus.at(1)->title(), "Edit");
    QCOMPARE(mainWindow->actionBar->menus.at(2)->title(), "Help");

    //Test actions in menu "View"
    QCOMPARE(mainWindow->actionBar->menus.at(0)->actions().length(), 1);
    QCOMPARE(mainWindow->actionBar->menus.at(0)->actions().at(0)->text(), "Group numbers");

    //Test actions in menu "Edit"
    QCOMPARE(mainWindow->actionBar->menus.at(1)->actions().length(), 2);
    QCOMPARE(mainWindow->actionBar->menus.at(1)->actions().at(0)->text(), "Copy");
    QCOMPARE(mainWindow->actionBar->menus.at(1)->actions().at(1)->text(), "Paste");

    //Test actions in menu "Help"
    QCOMPARE(mainWindow->actionBar->menus.at(2)->actions().length(), 2);
    QCOMPARE(mainWindow->actionBar->menus.at(2)->actions().at(0)->text(), "Info");
    QCOMPARE(mainWindow->actionBar->menus.at(2)->actions().at(1)->text(), "Display Help");
}

void Tests::testActionBarSignals()
{
    QSignalSpy toggleGroupNumSpy(mainWindow->actionBar, &ActionBar::toggleGroupNumbers);
    QVERIFY(toggleGroupNumSpy.isValid());
    mainWindow->actionBar->menus.at(0)->actions().at(0)->trigger();
    QCOMPARE(toggleGroupNumSpy.count(), 1);

    QSignalSpy copySpy(mainWindow->actionBar, &ActionBar::copy);
    QVERIFY(copySpy.isValid());
    mainWindow->actionBar->menus.at(1)->actions().at(0)->trigger();
    QCOMPARE(copySpy.count(), 1);

    QSignalSpy pasteSpy(mainWindow->actionBar, &ActionBar::paste);
    QVERIFY(pasteSpy.isValid());
    mainWindow->actionBar->menus.at(1)->actions().at(1)->trigger();
    QCOMPARE(pasteSpy.count(), 1);

    QSignalSpy infoSpy(mainWindow->actionBar, &ActionBar::info);
    QVERIFY(infoSpy.isValid());
    mainWindow->actionBar->menus.at(2)->actions().at(0)->trigger();
    QCOMPARE(infoSpy.count(), 1);

    QSignalSpy helpSpy(mainWindow->actionBar, &ActionBar::help);
    QVERIFY(helpSpy.isValid());
    mainWindow->actionBar->menus.at(2)->actions().at(1)->trigger();
    QCOMPARE(helpSpy.count(), 1);
}

void Tests::testActionBarFunctionality()
{
    //TODO: tests and functionality
    QSKIP("Functionality not implemented.");
}

void Tests::testBitLabelInit()
{
    QCOMPARE(bitLabel->bitPosition(), 0);
    QCOMPARE(bitLabel->m_bitPosition, 0);
    QCOMPARE(bitLabel->text(), "0");
}

void Tests::testBitLabelSignals()
{
    QSignalSpy clickSpy(bitLabel, &BitLabel::clicked);
    QVERIFY(clickSpy.isValid());
    bitLabel->mousePressEvent( new QMouseEvent(QMouseEvent::Type::MouseButtonPress, QPointF(0,0),
                                          Qt::MouseButton::LeftButton, Qt::MouseButtons(Qt::MouseButton::LeftButton),
                                          Qt::KeyboardModifiers()));
    QCOMPARE(clickSpy.count(), 1);
}

void Tests::testBitLabelFunctionality()
{
    bitLabel->setBit(false);
    QCOMPARE(bitLabel->text(), "0");
    bitLabel->setBit(true);
    QCOMPARE(bitLabel->text(), "1");
    bitLabel->flipBit();
    QCOMPARE(bitLabel->text(), "0");

    bitLabel->mousePressEvent( new QMouseEvent(QMouseEvent::Type::MouseButtonPress, QPointF(0,0),
                                          Qt::MouseButton::LeftButton, Qt::MouseButtons(Qt::MouseButton::LeftButton),
                                          Qt::KeyboardModifiers()));
    QCOMPARE(bitLabel->text(), "1");
}

void Tests::testCalcMainWindowInit()
{
    QCOMPARE(mainWindow->size(), QSize(500, 500));
    QVERIFY(mainWindow->centralWidget());

    QVERIFY(mainWindow->mainDisplay);
    QVERIFY(mainWindow->binDisplay);
    QVERIFY(mainWindow->modeSelection);
    QVERIFY(mainWindow->leftFunctionButtons);
    QVERIFY(mainWindow->rightFunctionButtons);
    QVERIFY(mainWindow->memoryButtons);
    QVERIFY(mainWindow->decNumberButtons);
    QVERIFY(mainWindow->hexNumberButtons);
    QVERIFY(mainWindow->actionBar);

}

void Tests::testDisplayBinInit()
{
    //We are not testing the helperLabels here becouse they are static
    int count = 0;
    for(auto label : mainWindow->binDisplay->labels)
    {
        QCOMPARE(label->bitPosition(), count);
        QCOMPARE(label->text(), "0");
        count++;
    }
}

void Tests::testDisplayBinSignals()
{
    int count = 1;
    QSignalSpy clickSpy(mainWindow->binDisplay, &DisplayBin::bitFlipped);
    for(auto label : mainWindow->binDisplay->labels)
    {
        QVERIFY(clickSpy.isValid());
        label->mousePressEvent( new QMouseEvent(QMouseEvent::Type::MouseButtonPress, QPointF(0,0),
                                              Qt::MouseButton::LeftButton, Qt::MouseButtons(Qt::MouseButton::LeftButton),
                                              Qt::KeyboardModifiers()));
        QCOMPARE(clickSpy.count(), count);
        count++;
    }
}

void Tests::testDisplayBinFunctionality()
{
    auto labels = mainWindow->binDisplay->labels;
    auto binDisplay = mainWindow->binDisplay;
    // Test that all labels change value and emit correct signal after they are clicked
    {
        int count = 1;
        QSignalSpy clickSpy(binDisplay, &DisplayBin::bitFlipped);
        for(auto label : binDisplay->labels)
        {
            auto prevText = label->text();
            QVERIFY(clickSpy.isValid());
            label->mousePressEvent( new QMouseEvent(QMouseEvent::Type::MouseButtonPress, QPointF(0,0),
                                                  Qt::MouseButton::LeftButton, Qt::MouseButtons(Qt::MouseButton::LeftButton),
                                                  Qt::KeyboardModifiers()));
            QCOMPARE(clickSpy.count(), count);
            QCOMPARE(clickSpy.at(count-1).at(0).toInt(), count-1);
            if(prevText == "0")
                QCOMPARE(label->text(), "1");
            else
                QCOMPARE(label->text(), "0");
            count++;
        }
    }
    // Test setBits function, compare two concatenated strings, one from
    // our labels and one from std implementation of bitset
    {
        auto labelsToBinString = [](QVector<BitLabel*> labels) -> QString{
            QString binString = "";
            for(auto label : labels)
                binString.prepend(label->text());
            return binString;
        };

        auto numberToBinString = [](qint64 number) -> QString{
          return QString::fromStdString(std::bitset<64>(number).to_string());
        };

        // Test limits
        binDisplay->setBits(std::numeric_limits<qint64>::max());
        QCOMPARE(labelsToBinString(labels), numberToBinString(std::numeric_limits<qint64>::max()));
        binDisplay->setBits(std::numeric_limits<qint64>::min());
        QCOMPARE(labelsToBinString(labels), numberToBinString(std::numeric_limits<qint64>::min()));
        binDisplay->setBits(0);
        QCOMPARE(labelsToBinString(labels), numberToBinString(0));

        // Test 1000 random numbers
        for(int i=0; i<1000; i++)
        {
            qint64 rand = QRandomGenerator::global()->generate64();
            binDisplay->setBits(rand);
            QCOMPARE(labelsToBinString(labels), numberToBinString(rand));
        }
    }

    //Test changeDisplayPrecision function, we need window to be visible for this
    {
        mainWindow->show();
        QVERIFY(QTest::qWaitForWindowExposed(mainWindow));

        binDisplay->changeDisplayPrecision(Calc::BitPrecision::_8bit);
        // the labels are stored in reverse order
        for(int i=labels.length()-1; i>=0; i--)
        {
            if(i>=8)
                QVERIFY(!labels.at(i)->isVisible());
            else
                QVERIFY(labels.at(i)->isVisible());
        }
        binDisplay->changeDisplayPrecision(Calc::BitPrecision::_16bit);
        for(int i=labels.length()-1; i>=0; i--)
        {
            if(i>=16)
                QVERIFY(!labels.at(i)->isVisible());
            else
                QVERIFY(labels.at(i)->isVisible());
        }
        binDisplay->changeDisplayPrecision(Calc::BitPrecision::_32bit);
        for(int i=labels.length()-1; i>=0; i--)
        {
            if(i>=32)
                QVERIFY(!labels.at(i)->isVisible());
            else
                QVERIFY(labels.at(i)->isVisible());
        }
        binDisplay->changeDisplayPrecision(Calc::BitPrecision::_64bit);
        for(int i=labels.length()-1; i>=0; i--)
        {
                QVERIFY(labels.at(i)->isVisible());
        }

        mainWindow->hide();
    }
}

void Tests::testMainDisplayInit()
{
    QCOMPARE(mainWindow->mainDisplay->displayText->text(), "0");
}

void Tests::testMainDisplayFunctionality()
{
    auto disp = mainWindow->mainDisplay;

    //Testing setNumeralSystem
    disp->setNumeralSystem(Calc::NumeralSystem::Bin);
    QCOMPARE(disp->dispSystem, Calc::NumeralSystem::Bin);
    QCOMPARE(disp->displayText->font().pixelSize(), 22);

    disp->setNumeralSystem(Calc::NumeralSystem::Dec);
    QCOMPARE(disp->dispSystem, Calc::NumeralSystem::Dec);
    QCOMPARE(disp->displayText->font().pixelSize(), 35);

    disp->setNumeralSystem(Calc::NumeralSystem::Hex);
    QCOMPARE(disp->dispSystem, Calc::NumeralSystem::Hex);
    QCOMPARE(disp->displayText->font().pixelSize(), 35);

    disp->setNumeralSystem(Calc::NumeralSystem::Oct);
    QCOMPARE(disp->dispSystem, Calc::NumeralSystem::Oct);
    QCOMPARE(disp->displayText->font().pixelSize(), 35);

    //Testing displayNumber


}

void Tests::testFunctionButtonsInit()
{
    auto leftButtons = mainWindow->leftFunctionButtons;
    auto rightButtons = mainWindow->rightFunctionButtons;

    QCOMPARE(leftButtons->numOfParanthesesOpened, 0);
    QVERIFY(leftButtons->modButton);
    QVERIFY(leftButtons->paranthesesOpenButton);
    QVERIFY(leftButtons->paranthesesCloseButton);
    QVERIFY(leftButtons->rolButton);
    QVERIFY(leftButtons->rorButton);
    QVERIFY(leftButtons->orButton);
    QVERIFY(leftButtons->xorButton);
    QVERIFY(leftButtons->lshButton);
    QVERIFY(leftButtons->rshButton);
    QVERIFY(leftButtons->notButton);
    QVERIFY(leftButtons->andButton);

    QVERIFY(rightButtons->invertButton);
    QVERIFY(rightButtons->divideButton);
    QVERIFY(rightButtons->multiplyButton);
    QVERIFY(rightButtons->subtractButton);
    QVERIFY(rightButtons->addButton);
    QVERIFY(rightButtons->deadButton1);
    QVERIFY(rightButtons->deadButton2);
    QVERIFY(rightButtons->deadButton3);
    QVERIFY(rightButtons->equalButton);
    QVERIFY(!rightButtons->deadButton1->isEnabled());
    QVERIFY(!rightButtons->deadButton2->isEnabled());
    QVERIFY(!rightButtons->deadButton3->isEnabled());
}

void Tests::testFunctionButtonsSignals()
{
    auto leftButtons = mainWindow->leftFunctionButtons;
    auto rightButtons = mainWindow->rightFunctionButtons;
    QSignalSpy clickSpyLeft(leftButtons, &LeftFunctionButtons::functionButtonPressed);
    QSignalSpy clickSpyRight(rightButtons, &RightFunctionButtons::functionButtonPressed);
    QVERIFY(clickSpyLeft.isValid());
    QVERIFY(clickSpyRight.isValid());
    int count = 1;
    leftButtons->modButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);
    leftButtons->paranthesesOpenButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);
    leftButtons->paranthesesCloseButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);
    leftButtons->rolButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);
    leftButtons->rorButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);
    leftButtons->orButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);
    leftButtons->xorButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);
    leftButtons->lshButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);
    leftButtons->rshButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);
    leftButtons->notButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);
    leftButtons->andButton->click();
    QCOMPARE(clickSpyLeft.count(), count++);

    count = 1;
    rightButtons->invertButton->click();
    QCOMPARE(clickSpyRight.count(), count++);
    rightButtons->divideButton->click();
    QCOMPARE(clickSpyRight.count(), count++);
    rightButtons->multiplyButton->click();
    QCOMPARE(clickSpyRight.count(), count++);
    rightButtons->subtractButton->click();
    QCOMPARE(clickSpyRight.count(), count++);
    rightButtons->addButton->click();
    QCOMPARE(clickSpyRight.count(), count);//not increasing count, next button shouldnt signal
    rightButtons->deadButton1->click();
    QCOMPARE(clickSpyRight.count(), count);//not increasing count, next button shouldnt signal
    rightButtons->deadButton2->click();
    QCOMPARE(clickSpyRight.count(), count);//not increasing count, next button shouldnt signal
    rightButtons->deadButton3->click();
    QCOMPARE(clickSpyRight.count(), count++);
    rightButtons->equalButton->click();
    QCOMPARE(clickSpyRight.count(), count++);
}

void Tests::testFunctionButtonsFunctionality()
{
    //Testing the parantheses display and counter
    auto leftButtons = mainWindow->leftFunctionButtons;
    leftButtons->clearParanthesesCount();
    leftButtons->paranthesesOpenButton->click();
    QCOMPARE(leftButtons->numOfParanthesesOpened, 1);
    QCOMPARE(leftButtons->paranthesesIndicator->text(), "(=1");
    leftButtons->paranthesesOpenButton->click();
    QCOMPARE(leftButtons->numOfParanthesesOpened, 2);
    QCOMPARE(leftButtons->paranthesesIndicator->text(), "(=2");
    leftButtons->paranthesesCloseButton->click();
    QCOMPARE(leftButtons->numOfParanthesesOpened, 1);
    QCOMPARE(leftButtons->paranthesesIndicator->text(), "(=1");
    leftButtons->paranthesesCloseButton->click();
    QCOMPARE(leftButtons->numOfParanthesesOpened, 0);
    QCOMPARE(leftButtons->paranthesesIndicator->text(), "");
    leftButtons->paranthesesCloseButton->click();
    QCOMPARE(leftButtons->numOfParanthesesOpened, 0);
    QCOMPARE(leftButtons->paranthesesIndicator->text(), "");
    leftButtons->paranthesesOpenButton->click();
    QCOMPARE(leftButtons->numOfParanthesesOpened, 1);
    QCOMPARE(leftButtons->paranthesesIndicator->text(), "(=1");
    leftButtons->clearParanthesesCount();
    QCOMPARE(leftButtons->numOfParanthesesOpened, 0);
    QCOMPARE(leftButtons->paranthesesIndicator->text(), "");
}

void Tests::testMemoryButtonsInit()
{
    auto memoryButtons = mainWindow->memoryButtons;
    QVERIFY(memoryButtons->memClearButton);
    QVERIFY(memoryButtons->memRestoreButton);
    QVERIFY(memoryButtons->memSaveButton);
    QVERIFY(memoryButtons->memAddButton);
    QVERIFY(memoryButtons->memSubtractButton);
}

void Tests::testMemoryButtonsSignals()
{
    auto memoryButtons = mainWindow->memoryButtons;
    QSignalSpy clickSpy(memoryButtons, &MemoryButtons::memoryButtonPressed);
    QVERIFY(clickSpy.isValid());

    int count = 1;
    memoryButtons->memClearButton->click();
    QCOMPARE(clickSpy.count(), count++);
    memoryButtons->memRestoreButton->click();
    QCOMPARE(clickSpy.count(), count++);
    memoryButtons->memSaveButton->click();
    QCOMPARE(clickSpy.count(), count++);
    memoryButtons->memAddButton->click();
    QCOMPARE(clickSpy.count(), count++);
    memoryButtons->memSubtractButton->click();
    QCOMPARE(clickSpy.count(), count++);
}

void Tests::testMemoryButtonsFunctionality()
{
    //TODO: implementation and tests
    QSKIP("Functionality not implemented.");
}

void Tests::testModeSelectionInit()
{
    auto modeSelection = mainWindow->modeSelection;
    QVERIFY(modeSelection->numSystemSelection);
    QVERIFY(modeSelection->precisionSelection);
    QVERIFY(modeSelection->nsHex);
    QVERIFY(modeSelection->nsDec);
    QVERIFY(modeSelection->nsOct);
    QVERIFY(modeSelection->nsBin);
    QVERIFY(modeSelection->p64bit);
    QVERIFY(modeSelection->p32bit);
    QVERIFY(modeSelection->p16bit);
    QVERIFY(modeSelection->p8bit);

    // Verify the startup state
    QVERIFY(modeSelection->p64bit->isChecked());
    QVERIFY(modeSelection->nsDec->isChecked());
}

void Tests::testModeSelectionSignals()
{
    auto modeSelection = mainWindow->modeSelection;
    QSignalSpy clickSpySys(modeSelection, &ModeSelection::numSystemChanged);
    QVERIFY(clickSpySys.isValid());
    QSignalSpy clickSpyPrec(modeSelection, &ModeSelection::precisionChanged);
    QVERIFY(clickSpyPrec.isValid());

    int count = 1;
    modeSelection->nsHex->click();
    QCOMPARE(clickSpySys.count(), count++);
    modeSelection->nsDec->click();
    QCOMPARE(clickSpySys.count(), count++);
    modeSelection->nsOct->click();
    QCOMPARE(clickSpySys.count(), count++);
    modeSelection->nsBin->click();
    QCOMPARE(clickSpySys.count(), count);
    modeSelection->nsBin->click();          // We click again on already set one and signal should
    QCOMPARE(clickSpySys.count(), count);   // not be emitted

    count = 1;
    modeSelection->p32bit->click();
    QCOMPARE(clickSpyPrec.count(), count++);
    modeSelection->p64bit->click();
    QCOMPARE(clickSpyPrec.count(), count++);
    modeSelection->p16bit->click();
    QCOMPARE(clickSpyPrec.count(), count++);
    modeSelection->p8bit->click();          // We click again on already set one and signal should
    QCOMPARE(clickSpyPrec.count(), count);  // not be emitted
}

void Tests::testModeSelectionsFunctionality()
{
    auto modeSelection = mainWindow->modeSelection;
    auto labels = mainWindow->binDisplay->labels;
    auto decButtons = mainWindow->decNumberButtons;
    auto hexButtons = mainWindow->hexNumberButtons;
    mainWindow->show();
    QVERIFY(QTest::qWaitForWindowExposed(mainWindow));

    modeSelection->p8bit->click();
    // the labels are stored in reverse order
    for(int i=labels.length()-1; i>=0; i--)
    {
        if(i>=8)
            QVERIFY(!labels.at(i)->isVisible());
        else
            QVERIFY(labels.at(i)->isVisible());
    }
    modeSelection->p16bit->click();
    for(int i=labels.length()-1; i>=0; i--)
    {
        if(i>=16)
            QVERIFY(!labels.at(i)->isVisible());
        else
            QVERIFY(labels.at(i)->isVisible());
    }
    modeSelection->p32bit->click();
    for(int i=labels.length()-1; i>=0; i--)
    {
        if(i>=32)
            QVERIFY(!labels.at(i)->isVisible());
        else
            QVERIFY(labels.at(i)->isVisible());
    }
    modeSelection->p64bit->click();
    for(int i=labels.length()-1; i>=0; i--)
    {
            QVERIFY(labels.at(i)->isVisible());
    }

    modeSelection->nsHex->click();
    QVERIFY(decButtons->button0->isEnabled());
    QVERIFY(decButtons->button1->isEnabled());
    QVERIFY(decButtons->button2->isEnabled());
    QVERIFY(decButtons->button3->isEnabled());
    QVERIFY(decButtons->button4->isEnabled());
    QVERIFY(decButtons->button5->isEnabled());
    QVERIFY(decButtons->button6->isEnabled());
    QVERIFY(decButtons->button7->isEnabled());
    QVERIFY(decButtons->button8->isEnabled());
    QVERIFY(decButtons->button9->isEnabled());
    QVERIFY(hexButtons->buttonA->isEnabled());
    QVERIFY(hexButtons->buttonB->isEnabled());
    QVERIFY(hexButtons->buttonC->isEnabled());
    QVERIFY(hexButtons->buttonD->isEnabled());
    QVERIFY(hexButtons->buttonE->isEnabled());
    QVERIFY(hexButtons->buttonF->isEnabled());

    modeSelection->nsDec->click();
    QVERIFY(decButtons->button0->isEnabled());
    QVERIFY(decButtons->button1->isEnabled());
    QVERIFY(decButtons->button2->isEnabled());
    QVERIFY(decButtons->button3->isEnabled());
    QVERIFY(decButtons->button4->isEnabled());
    QVERIFY(decButtons->button5->isEnabled());
    QVERIFY(decButtons->button6->isEnabled());
    QVERIFY(decButtons->button7->isEnabled());
    QVERIFY(decButtons->button8->isEnabled());
    QVERIFY(decButtons->button9->isEnabled());
    QVERIFY(!hexButtons->buttonA->isEnabled());
    QVERIFY(!hexButtons->buttonB->isEnabled());
    QVERIFY(!hexButtons->buttonC->isEnabled());
    QVERIFY(!hexButtons->buttonD->isEnabled());
    QVERIFY(!hexButtons->buttonE->isEnabled());
    QVERIFY(!hexButtons->buttonF->isEnabled());

    modeSelection->nsOct->click();
    QVERIFY(decButtons->button0->isEnabled());
    QVERIFY(decButtons->button1->isEnabled());
    QVERIFY(decButtons->button2->isEnabled());
    QVERIFY(decButtons->button3->isEnabled());
    QVERIFY(decButtons->button4->isEnabled());
    QVERIFY(decButtons->button5->isEnabled());
    QVERIFY(decButtons->button6->isEnabled());
    QVERIFY(decButtons->button7->isEnabled());
    QVERIFY(!decButtons->button8->isEnabled());
    QVERIFY(!decButtons->button9->isEnabled());
    QVERIFY(!hexButtons->buttonA->isEnabled());
    QVERIFY(!hexButtons->buttonB->isEnabled());
    QVERIFY(!hexButtons->buttonC->isEnabled());
    QVERIFY(!hexButtons->buttonD->isEnabled());
    QVERIFY(!hexButtons->buttonE->isEnabled());
    QVERIFY(!hexButtons->buttonF->isEnabled());

    modeSelection->nsBin->click();
    QVERIFY(decButtons->button0->isEnabled());
    QVERIFY(decButtons->button1->isEnabled());
    QVERIFY(!decButtons->button2->isEnabled());
    QVERIFY(!decButtons->button3->isEnabled());
    QVERIFY(!decButtons->button4->isEnabled());
    QVERIFY(!decButtons->button5->isEnabled());
    QVERIFY(!decButtons->button6->isEnabled());
    QVERIFY(!decButtons->button7->isEnabled());
    QVERIFY(!decButtons->button8->isEnabled());
    QVERIFY(!decButtons->button9->isEnabled());
    QVERIFY(!hexButtons->buttonA->isEnabled());
    QVERIFY(!hexButtons->buttonB->isEnabled());
    QVERIFY(!hexButtons->buttonC->isEnabled());
    QVERIFY(!hexButtons->buttonD->isEnabled());
    QVERIFY(!hexButtons->buttonE->isEnabled());
    QVERIFY(!hexButtons->buttonF->isEnabled());

    mainWindow->hide();
}

void Tests::testNumberButtonsInit()
{
    auto decButtons = mainWindow->decNumberButtons;
    auto hexButtons = mainWindow->hexNumberButtons;

    QVERIFY(decButtons->button0->isEnabled());
    QVERIFY(decButtons->button1->isEnabled());
    QVERIFY(decButtons->button2->isEnabled());
    QVERIFY(decButtons->button3->isEnabled());
    QVERIFY(decButtons->button4->isEnabled());
    QVERIFY(decButtons->button5->isEnabled());
    QVERIFY(decButtons->button6->isEnabled());
    QVERIFY(decButtons->button7->isEnabled());
    QVERIFY(decButtons->button8->isEnabled());
    QVERIFY(decButtons->button9->isEnabled());
    QVERIFY(decButtons->buttonBackSpace->isEnabled());
    QVERIFY(decButtons->buttonClear->isEnabled());
    QVERIFY(decButtons->buttonCE->isEnabled());
    QVERIFY(!decButtons->buttonDeadComa->isEnabled());

    //We start in decimal mode so only 0-9 numbers should be enabled
    QVERIFY(!hexButtons->buttonA->isEnabled());
    QVERIFY(!hexButtons->buttonB->isEnabled());
    QVERIFY(!hexButtons->buttonC->isEnabled());
    QVERIFY(!hexButtons->buttonD->isEnabled());
    QVERIFY(!hexButtons->buttonE->isEnabled());
    QVERIFY(!hexButtons->buttonF->isEnabled());
}

void Tests::testNumberButtonsSignals()
{
    auto decButtons = mainWindow->decNumberButtons;
    auto hexButtons = mainWindow->hexNumberButtons;
    QSignalSpy clickSpyDec(decButtons, &DecNumberButtons::numericalButtonPressed);
    QVERIFY(clickSpyDec.isValid());
    QSignalSpy clickSpyHex(hexButtons, &HexNumberButtons::numericalButtonPressed);
    QVERIFY(clickSpyHex.isValid());

    int count = 1;
    decButtons->button0->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->button1->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->button2->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->button3->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->button4->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->button5->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->button6->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->button7->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->button8->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->button9->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->buttonBackSpace->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->buttonClear->click();
    QCOMPARE(clickSpyDec.count(), count++);
    decButtons->buttonCE->click();
    QCOMPARE(clickSpyDec.count(), count);
    decButtons->buttonDeadComa->click(); //shouldnt work, button permamently disabled
    QCOMPARE(clickSpyDec.count(), count);

    hexButtons->setButtonsEnabled(true); //for signal testing we need them to work
    count = 1;
    hexButtons->buttonA->click();
    QCOMPARE(clickSpyHex.count(), count++);
    hexButtons->buttonB->click();
    QCOMPARE(clickSpyHex.count(), count++);
    hexButtons->buttonC->click();
    QCOMPARE(clickSpyHex.count(), count++);
    hexButtons->buttonD->click();
    QCOMPARE(clickSpyHex.count(), count++);
    hexButtons->buttonE->click();
    QCOMPARE(clickSpyHex.count(), count++);
    hexButtons->buttonF->click();
    QCOMPARE(clickSpyHex.count(), count++);
}

void Tests::testNumberButtonsFunctionality()
{
    auto decButtons = mainWindow->decNumberButtons;
    auto hexButtons = mainWindow->hexNumberButtons;

    decButtons->setButtonsEnabled(Calc::NumeralSystem::Bin);
    QVERIFY(decButtons->button0->isEnabled());
    QVERIFY(decButtons->button1->isEnabled());
    QVERIFY(!decButtons->button2->isEnabled());
    QVERIFY(!decButtons->button3->isEnabled());
    QVERIFY(!decButtons->button4->isEnabled());
    QVERIFY(!decButtons->button5->isEnabled());
    QVERIFY(!decButtons->button6->isEnabled());
    QVERIFY(!decButtons->button7->isEnabled());
    QVERIFY(!decButtons->button8->isEnabled());
    QVERIFY(!decButtons->button9->isEnabled());
    QVERIFY(decButtons->buttonBackSpace->isEnabled());
    QVERIFY(decButtons->buttonClear->isEnabled());
    QVERIFY(decButtons->buttonCE->isEnabled());
    QVERIFY(!decButtons->buttonDeadComa->isEnabled());

    decButtons->setButtonsEnabled(Calc::NumeralSystem::Oct);
    QVERIFY(decButtons->button0->isEnabled());
    QVERIFY(decButtons->button1->isEnabled());
    QVERIFY(decButtons->button2->isEnabled());
    QVERIFY(decButtons->button3->isEnabled());
    QVERIFY(decButtons->button4->isEnabled());
    QVERIFY(decButtons->button5->isEnabled());
    QVERIFY(decButtons->button6->isEnabled());
    QVERIFY(decButtons->button7->isEnabled());
    QVERIFY(!decButtons->button8->isEnabled());
    QVERIFY(!decButtons->button9->isEnabled());
    QVERIFY(decButtons->buttonBackSpace->isEnabled());
    QVERIFY(decButtons->buttonClear->isEnabled());
    QVERIFY(decButtons->buttonCE->isEnabled());
    QVERIFY(!decButtons->buttonDeadComa->isEnabled());

    decButtons->setButtonsEnabled(Calc::NumeralSystem::Dec);
    QVERIFY(decButtons->button0->isEnabled());
    QVERIFY(decButtons->button1->isEnabled());
    QVERIFY(decButtons->button2->isEnabled());
    QVERIFY(decButtons->button3->isEnabled());
    QVERIFY(decButtons->button4->isEnabled());
    QVERIFY(decButtons->button5->isEnabled());
    QVERIFY(decButtons->button6->isEnabled());
    QVERIFY(decButtons->button7->isEnabled());
    QVERIFY(decButtons->button8->isEnabled());
    QVERIFY(decButtons->button9->isEnabled());
    QVERIFY(decButtons->buttonBackSpace->isEnabled());
    QVERIFY(decButtons->buttonClear->isEnabled());
    QVERIFY(decButtons->buttonCE->isEnabled());
    QVERIFY(!decButtons->buttonDeadComa->isEnabled());

    decButtons->setButtonsEnabled(Calc::NumeralSystem::Hex);
    QVERIFY(decButtons->button0->isEnabled());
    QVERIFY(decButtons->button1->isEnabled());
    QVERIFY(decButtons->button2->isEnabled());
    QVERIFY(decButtons->button3->isEnabled());
    QVERIFY(decButtons->button4->isEnabled());
    QVERIFY(decButtons->button5->isEnabled());
    QVERIFY(decButtons->button6->isEnabled());
    QVERIFY(decButtons->button7->isEnabled());
    QVERIFY(decButtons->button8->isEnabled());
    QVERIFY(decButtons->button9->isEnabled());
    QVERIFY(decButtons->buttonBackSpace->isEnabled());
    QVERIFY(decButtons->buttonClear->isEnabled());
    QVERIFY(decButtons->buttonCE->isEnabled());
    QVERIFY(!decButtons->buttonDeadComa->isEnabled());

    hexButtons->setButtonsEnabled(true);
    QVERIFY(hexButtons->buttonA->isEnabled());
    QVERIFY(hexButtons->buttonB->isEnabled());
    QVERIFY(hexButtons->buttonC->isEnabled());
    QVERIFY(hexButtons->buttonD->isEnabled());
    QVERIFY(hexButtons->buttonE->isEnabled());
    QVERIFY(hexButtons->buttonF->isEnabled());

    hexButtons->setButtonsEnabled(false);
    QVERIFY(!hexButtons->buttonA->isEnabled());
    QVERIFY(!hexButtons->buttonB->isEnabled());
    QVERIFY(!hexButtons->buttonC->isEnabled());
    QVERIFY(!hexButtons->buttonD->isEnabled());
    QVERIFY(!hexButtons->buttonE->isEnabled());
    QVERIFY(!hexButtons->buttonF->isEnabled());
}

template <typename T, typename ...Args> //This template below lets us save few lines of code. Dear god, never again...
void Tests::testShortcut(QWidget* widget, T* sender, void(T::*signal)(Args...), Qt::Key key, Qt::KeyboardModifier mod)
{
    QSignalSpy spy(sender, signal);
    QVERIFY(spy.isValid());
    QTest::keyClick(widget, key, mod);
    QVERIFY(QTest::qWaitFor([&](){return spy.count() == 1;}, 200));
}

void Tests::testButtonShortcuts()
{
    mainWindow->show();
    QVERIFY(QTest::qWaitForWindowExposed(mainWindow));

    // Test actionBar shortcuts
    testShortcut(mainWindow, mainWindow->actionBar, &ActionBar::toggleGroupNumbers,
                 Qt::Key_G, Qt::ControlModifier);
    testShortcut(mainWindow, mainWindow->actionBar, &ActionBar::copy,
                 Qt::Key_C, Qt::ControlModifier);
    testShortcut(mainWindow, mainWindow->actionBar, &ActionBar::paste,
                 Qt::Key_V, Qt::ControlModifier);
    testShortcut(mainWindow, mainWindow->actionBar, &ActionBar::help,
                 Qt::Key_F1, Qt::NoModifier);

    // Test leftFunctionButtons shortcuts
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_Percent, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_ParenLeft, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_ParenRight, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_J, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_K, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_Bar, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_AsciiCircum, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_Less, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_Greater, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_Exclam, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->leftFunctionButtons, &LeftFunctionButtons::functionButtonPressed,
                 Qt::Key_Ampersand, Qt::NoModifier);

    // Test rightFunctionButtons shortcuts
    testShortcut(mainWindow, mainWindow->rightFunctionButtons, &RightFunctionButtons::functionButtonPressed,
                 Qt::Key_F9, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->rightFunctionButtons, &RightFunctionButtons::functionButtonPressed,
                 Qt::Key_Slash, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->rightFunctionButtons, &RightFunctionButtons::functionButtonPressed,
                 Qt::Key_Asterisk, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->rightFunctionButtons, &RightFunctionButtons::functionButtonPressed,
                 Qt::Key_Minus, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->rightFunctionButtons, &RightFunctionButtons::functionButtonPressed,
                 Qt::Key_Plus, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->rightFunctionButtons, &RightFunctionButtons::functionButtonPressed,
                 Qt::Key_Return, Qt::NoModifier);

    // Test memoryButtons shortcuts
    testShortcut(mainWindow, mainWindow->memoryButtons, &MemoryButtons::memoryButtonPressed,
                 Qt::Key_L, Qt::ControlModifier);
    testShortcut(mainWindow, mainWindow->memoryButtons, &MemoryButtons::memoryButtonPressed,
                 Qt::Key_R, Qt::ControlModifier);
    testShortcut(mainWindow, mainWindow->memoryButtons, &MemoryButtons::memoryButtonPressed,
                 Qt::Key_M, Qt::ControlModifier);
    testShortcut(mainWindow, mainWindow->memoryButtons, &MemoryButtons::memoryButtonPressed,
                 Qt::Key_P, Qt::ControlModifier);
    testShortcut(mainWindow, mainWindow->memoryButtons, &MemoryButtons::memoryButtonPressed,
                 Qt::Key_Q, Qt::ControlModifier);

    cleanup();
    mainWindow->show();
    QVERIFY(QTest::qWaitForWindowExposed(mainWindow));
    // Test numeric systems shortcuts
    testShortcut(mainWindow, mainWindow->modeSelection, &ModeSelection::numSystemChanged,
                 Qt::Key_F5, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->modeSelection, &ModeSelection::numSystemChanged,
                 Qt::Key_F6, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->modeSelection, &ModeSelection::numSystemChanged,
                 Qt::Key_F7, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->modeSelection, &ModeSelection::numSystemChanged,
                 Qt::Key_F8, Qt::NoModifier);

    // Test precision shortcuts
    testShortcut(mainWindow, mainWindow->modeSelection, &ModeSelection::precisionChanged,
                 Qt::Key_F2, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->modeSelection, &ModeSelection::precisionChanged,
                 Qt::Key_F12, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->modeSelection, &ModeSelection::precisionChanged,
                 Qt::Key_F3, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->modeSelection, &ModeSelection::precisionChanged,
                 Qt::Key_F4, Qt::NoModifier);

    // Test decNumberButtons
    mainWindow->hexNumberButtons->setButtonsEnabled(true);
    mainWindow->decNumberButtons->setButtonsEnabled(Calc::NumeralSystem::Hex);

    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_0, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_1, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_2, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_3, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_4, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_5, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_6, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_7, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_8, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_9, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_Backspace, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_Escape, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->decNumberButtons, &DecNumberButtons::numericalButtonPressed,
                 Qt::Key_Delete, Qt::NoModifier);

    // Test hexNumberButtons

    testShortcut(mainWindow, mainWindow->hexNumberButtons, &HexNumberButtons::numericalButtonPressed,
                 Qt::Key_A, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->hexNumberButtons, &HexNumberButtons::numericalButtonPressed,
                 Qt::Key_B, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->hexNumberButtons, &HexNumberButtons::numericalButtonPressed,
                 Qt::Key_C, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->hexNumberButtons, &HexNumberButtons::numericalButtonPressed,
                 Qt::Key_D, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->hexNumberButtons, &HexNumberButtons::numericalButtonPressed,
                 Qt::Key_E, Qt::NoModifier);
    testShortcut(mainWindow, mainWindow->hexNumberButtons, &HexNumberButtons::numericalButtonPressed,
                 Qt::Key_F, Qt::NoModifier);
}

void Tests::testCalculatorInit()
{
    //TODO: tests
    QSKIP("Tests not implemented.");
}

void Tests::testCalculatorSignals()
{
    //TODO: tests
    QSKIP("Tests not implemented.");
}

void Tests::testCalculatorFunctionality()
{
    //TODO: tests
    QSKIP("Tests not implemented.");
}



QTEST_MAIN(Tests)

#include "calcTests.moc"
