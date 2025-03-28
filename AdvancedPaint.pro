QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

SOURCES += \
    src/basetool/basetool.cpp \
    src/brushtool/brushtool.cpp \
    src/canvas/canvas.cpp \
    src/erasetool/erasetool.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pentool/pentool.cpp \
    src/spraytool/spraytool.cpp \
    src/toolcontroller/toolcontroller.cpp

HEADERS += \
    src/basetool/basetool.h \
    src/brushtool/brushtool.h \
    src/canvas/canvas.h \
    src/erasetool/erasetool.h \
    src/mainwindow.h \
    src/pentool/pentool.h \
    src/spraytool/spraytool.h \
    src/toolcontroller/toolcontroller.h

FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
