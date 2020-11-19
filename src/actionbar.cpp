#include "actionbar.h"

ActionBar::ActionBar(QWidget *parent) : QMenuBar(parent)
{
    auto view = addMenu("View");
    view->addAction("Group numbers", [&](){emit toggleGroupNumbers();})->setShortcut(QKeySequence("Ctrl+g"));
    auto edit = addMenu("Edit");
    edit->addAction("Copy", [&](){emit copy();})->setShortcut(QKeySequence("Ctrl+c"));
    edit->addAction("Paste", [&](){emit paste();})->setShortcut(QKeySequence("Ctrl+v"));
    auto help = addMenu("Help");
    help->addAction("Info", [&](){emit info();});
    help->addAction("Display Help", [&](){ emit this->help();})->setShortcut(QKeySequence("F1"));
}
