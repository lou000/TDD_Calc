QT += core gui
QT += widgets

CONFIG += c++11
#CONFIG += run_tests


SOURCES += \
    external/DarkStyle.cpp \
    external/framelesswindow/framelesswindow.cpp \
    external/framelesswindow/windowdragger.cpp \
    src/bitlabel.cpp \
    src/calculator.cpp \
    src/displaybin.cpp \
    src/displaymain.cpp \
    src/functionbuttons.cpp \
    src/memorybuttons.cpp \
    src/modeselection.cpp \
    src/numberbuttons.cpp \
    src/actionbar.cpp \
    src/calcmainwindow.cpp

HEADERS += \
    external/DarkStyle.h \
    external/framelesswindow/framelesswindow.h \
    external/framelesswindow/windowdragger.h \
    src/globalinclude.h \
    src/bitlabel.h \
    src/calculator.h \
    src/displaybin.h \
    src/displaymain.h \
    src/functionbuttons.h \
    src/memorybuttons.h \
    src/modeselection.h \
    src/numberbuttons.h \
    src/actionbar.h \
    src/calcmainwindow.h \
    src/windows_mess.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

run_tests {
    TARGET = calc_tests
    # test specific files and options here
    SOURCES += \
        tests/calcTests.cpp

    QT += testlib
} else {
   # app specific files and options here
    SOURCES += \
        src/main.cpp
}

RESOURCES += \
    external/darkstyle.qrc \
    external/framelesswindow.qrc

FORMS += \
    external/framelesswindow/framelesswindow.ui
