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


SOURCES += \
 main.cpp \
 \
 dialogs/TDCheck.cpp \
 dialogs/TDLogin.cpp \
 \
 templates/TCreate.cpp \
 templates/TEdit.cpp \
 templates/TTModel.cpp \
 templates/TTModels.cpp \
 \
 utils/TCheckBox.cpp \
 utils/TComboBox.cpp \
 utils/TConfig.cpp \
 utils/TDB.cpp \
 utils/TFileUpload.cpp \
 utils/TListBox.cpp \
 \
 windows/TChoose.cpp \
 windows/TMainMenu.cpp \
 windows/TMainWindow.cpp \
 \
 windows/actor/TActor.cpp \
 windows/actor/TActors.cpp \
 windows/actor/TActorCreate.cpp \
 windows/actor/TActorEdit.cpp \
 \
 windows/article/TArticle.cpp \
 windows/article/TArticleCreate.cpp \
 windows/article/TArticleEdit.cpp \
 windows/article/TArticles.cpp \
 \
 windows/del/TDeleted.cpp \
 windows/del/TDeletedTab.cpp \
 \
 windows/hall/draw/THall.cpp \
 windows/hall/draw/THallCanvas.cpp \
 windows/hall/draw/THallTools.cpp \
 \
 windows/hall/THallCreate.cpp \
 windows/hall/THallEdit.cpp \
 windows/hall/THallPreview.cpp \
 windows/hall/THalls.cpp \
 \
 windows/perf/TPerf.cpp \
 windows/perf/TPerfApprove.cpp \
 windows/perf/TPerfCreate.cpp \
 windows/perf/TPerfEdit.cpp \
 windows/perf/TPerfs.cpp \
 \
 windows/poster/TPoster.cpp \
 windows/poster/TPosterCreate.cpp \
 windows/poster/TPosterEdit.cpp \
 windows/poster/TPosters.cpp \
 \
 windows/settings/TWSettings.cpp \
 \
 windows/theatre/TTheatre.cpp \
 windows/theatre/TTheatres.cpp \
 windows/theatre/TTheatreCreate.cpp \
 windows/theatre/TTheatreEdit.cpp \
 \
 windows/user/TUser.cpp \
 windows/user/TUsers.cpp \
 windows/user/TUserCreate.cpp \
 windows/user/TUserEdit.cpp \

HEADERS +=  \
 dialogs/TDCheck.h \
 dialogs/TDLogin.h \
  \
 templates/TCreate.h \
 templates/TEdit.h \
 templates/TTModel.h \
 templates/TTModels.h \
  \
 utils/TCheckBox.h \
 utils/TComboBox.h \
 utils/TConfig.h \
 utils/TDB.h \
 utils/TFileUpload.h \
 utils/TListBox.h \
  \
 windows/TChoose.h \
 windows/TMainMenu.h \
 windows/TMainWindow.h \
  \
 windows/actor/TActor.h \
 windows/actor/TActors.h \
 windows/actor/TActorCreate.h \
 windows/actor/TActorEdit.h \
  \
 windows/article/TArticle.h \
 windows/article/TArticleCreate.h \
 windows/article/TArticleEdit.h \
 windows/article/TArticles.h \
  \
 windows/del/TDeleted.h \
 windows/del/TDeletedTab.h \
  \
 windows/hall/draw/THall.h \
 windows/hall/draw/THallCanvas.h \
 windows/hall/draw/THallTools.h \
  \
 windows/hall/THallCreate.h \
 windows/hall/THallEdit.h \
 windows/hall/THallPreview.h \
 windows/hall/THalls.h \
  \
 windows/perf/TPerf.h \
 windows/perf/TPerfApprove.h \
 windows/perf/TPerfCreate.h \
 windows/perf/TPerfEdit.h \
 windows/perf/TPerfs.h \
  \
 windows/poster/TPoster.h \
 windows/poster/TPosterCreate.h \
 windows/poster/TPosterEdit.h \
 windows/poster/TPosters.h \
  \
 windows/settings/TWSettings.h \
  \
 windows/theatre/TTheatre.h \
 windows/theatre/TTheatres.h \
 windows/theatre/TTheatreCreate.h \
 windows/theatre/TTheatreEdit.h \
  \
 windows/user/TUser.h \
 windows/user/TUsers.h \
 windows/user/TUserCreate.h \
 windows/user/TUserEdit.h \

RESOURCES += res/res.qrc
