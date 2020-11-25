#include "calcmainwindow.h"
#include "external/framelesswindow/framelesswindow.h"
#include "external/DarkStyle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto style = new DarkStyle;
    QApplication::setStyle(style);
    FramelessWindow* framelessWindow = new FramelessWindow();
    CalcMainWindow* window = new CalcMainWindow(framelessWindow);
    framelessWindow->setContent(window);
    framelessWindow->setWindowTitle("Calculator   -   Project WO   -   by Lewicki Maciej and Artur Wołyniec");
    QFont font = QFont("Calibri", 10);
    a.setFont(font);
    auto palette = a.palette();
    style->polish(palette);
    a.setPalette(palette);
    QObject::connect(window, &CalcMainWindow::move, framelessWindow, [=](int x, int y)
    {
        framelessWindow->move(x, y);
    });
    QObject::connect(window, &CalcMainWindow::show, framelessWindow, [=]
    {
        framelessWindow->show();
    });
    window->show();
    return a.exec();
}
