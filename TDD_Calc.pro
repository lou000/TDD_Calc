QT += core gui
QT += widgets

CONFIG += c++11
CONFIG += run_tests


SOURCES += \
    src/displaybin.cpp \
    src/displaymain.cpp \
    src/functionbuttons.cpp \
    src/modeselection.cpp \
    src/numberbuttons.cpp \
    src/actionbar.cpp \
    src/calcmainwindow.cpp

HEADERS += \
    src/displaybin.h \
    src/displaymain.h \
    src/functionbuttons.h \
    src/modeselection.h \
    src/numberbuttons.h \
    src/actionbar.h \
    src/calcmainwindow.h

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
