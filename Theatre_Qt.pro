#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T08:10:16
#
#-------------------------------------------------

QT       += core gui network
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp \
        dialogs/TDLogin.cpp \
        utils/TDB.cpp \
        windows/TBooking.cpp \
        windows/TComments.cpp \
        windows/TLogin.cpp \
        windows/TMainMenu.cpp \
        windows/TMainWindow.cpp \
        windows/TModel.cpp \
        windows/TReviews.cpp \
        windows/TStatistics.cpp \
    utils/TConfig.cpp \
    windows/edit_theatre.cpp \
    windows/create_theatre.cpp \
    windows/theatres.cpp \
    windows/theatre.cpp \
    windows/create_actor.cpp \
    windows/actors.cpp \
    windows/actor.cpp

HEADERS += \
        dialogs/TDLogin.h \
        utils/TConfig.h \
        utils/TDB.h \
        windows/TBooking.h \
        windows/TComments.h \
        windows/TLogin.h \
        windows/TMainMenu.h \
        windows/TMainWindow.h \
        windows/TModel.h \
        windows/TReviews.h \
        windows/TStatistics.h \
    windows/edit_theatre.h \
    windows/create_theatre.h \
    windows/theatres.h \
    windows/theatre.h \
    windows/create_actor.h \
    windows/actors.h \
    windows/actor.h

RESOURCES += res/res.qrc
