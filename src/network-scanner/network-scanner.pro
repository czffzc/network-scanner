QT       += core gui
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hostdetail.cpp \
    hostscan.cpp \
    main.cpp \
    mainwindow.cpp \
    pingthread.cpp \
    port.cpp \
    portscan.cpp

HEADERS += \
    common.h \
    hostdetail.h \
    hostscan.h \
    mainwindow.h \
    myping.h \
    osDetect.h \
    pingthread.h \
    port.h \
    portscan.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


LIBS += -lws2_32

RESOURCES += \
    service.qrc

RC_ICONS = scanner.ico
