#include "actionbar.h"

ActionBar::ActionBar(QWidget *parent) : QMenuBar(parent)
{
    auto view = addMenu("View");
    view->addAction("Group numbers", [&](){emit toggleGroupNumbers();})->setShortcut(QKeySequence("Ctrl+g"));
    auto edit = addMenu("Edit");
    edit->addAction("Copy", [&](){emit copy();})->setShortcut(QKeySequence::Copy);
    edit->addAction("Paste", [&](){emit paste();})->setShortcut(QKeySequence::Paste);
    auto help = addMenu("Help");
    help->addAction("Info", [&](){emit info();});
    help->addAction("Display Help", [&](){ emit this->help();})->setShortcut(QKeySequence::HelpContents);

    menus.append(view);
    menus.append(edit);
    menus.append(help);
}
