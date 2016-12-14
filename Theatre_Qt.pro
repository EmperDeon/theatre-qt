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


SOURCES +=        main.cpp \
           \
                  dialogs/TDCheck.cpp \
                  dialogs/TDLogin.cpp \
           \
				  templates/TTModel.cpp \
           \
                  utils/TComboBox.cpp \
                  utils/TConfig.cpp \
                  utils/TDB.cpp \
                  utils/TListBox.cpp \
           \
                  windows/TMainMenu.cpp \
                  windows/TMainWindow.cpp \
           \
                  windows/user/TUser.cpp \
                  windows/user/TUsers.cpp \
                  windows/user/TUserCreate.cpp \
                  windows/user/TUserEdit.cpp \
           \
                  windows/edit_theatre.cpp \
                  windows/create_theatre.cpp \
                  windows/theatres.cpp \
                  windows/theatre.cpp \
                  windows/create_actor.cpp \
                  windows/actors.cpp \
                  windows/actor.cpp 

HEADERS += \
       dialogs/TDCheck.h \
              dialogs/TDLogin.h \
       \
              templates/TTModel.h \
       \
              utils/TComboBox.h \
              utils/TConfig.h \
              utils/TDB.h \
              utils/TListBox.h \
       \
              windows/TMainMenu.h \
              windows/TMainWindow.h \
       \
              windows/user/TUser.h \
              windows/user/TUsers.h \
              windows/user/TUserCreate.h \
              windows/user/TUserEdit.h \
       \
              windows/edit_theatre.h \
              windows/create_theatre.h \
              windows/theatres.h \
              windows/theatre.h \
              windows/create_actor.h \
              windows/actors.h \
              windows/actor.h

RESOURCES += res/res.qrc
