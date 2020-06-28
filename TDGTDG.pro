#-------------------------------------------------
#
# Project created by QtCreator 2019-06-03T23:35:51
#
#-------------------------------------------------

QMAKE_LFLAGS_RELEASE = /INCREMENTAL:NO /DEBUG

QT       += core gui
QT       += multimedia
CONFIG+=resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TDGTDG
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow1.cpp \
    mainwindow11.cpp \
    mainwindow12.cpp \
    enemy.cpp \
    bullet.cpp \
    castle.cpp \
    plistreader.cpp \
    tower.cpp \
    towerposition.cpp \
    waypoint.cpp \
    audioplayer.cpp \
    money.cpp \
    bgmusic.cpp \
    cannon.cpp \
    cannonbullet.cpp \
    supercastle.cpp \
    icetower.cpp \
    icebullet.cpp

HEADERS += \
        mainwindow1.h \
    mainwindow11.h \
    mainwindow12.h \
    enemy.h \
    bullet.h \
    castle.h \
    plistreader.h \
    tower.h \
    towerposition.h \
    judge.h \
    waypoint.h \
    audioplayer.h \
    money.h \
    bgmusic.h \
    cannon.h \
    cannonbullet.h \
    supercastle.h \
    icetower.h \
    icebullet.h

FORMS += \
        mainwindow1.ui \
    mainwindow11.ui \
    mainwindow12.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    file.qrc
