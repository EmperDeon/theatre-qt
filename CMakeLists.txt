cmake_minimum_required(VERSION 3.3)
project(Theatre_Admin)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-std=c++14")

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5Concurrent)

set(P_S
        main.cpp

        dialogs/TDCheck.cpp
        dialogs/TDLogin.cpp

        templates/TTModel.cpp

        res/res.rc

        utils/TComboBox.cpp
        utils/TConfig.cpp
        utils/TDB.cpp
        utils/TListBox.cpp

        windows/TMainMenu.cpp
        windows/TMainWindow.cpp

        windows/user/TUser.cpp
        windows/user/TUsers.cpp
        windows/user/TUserCreate.cpp
        windows/user/TUserEdit.cpp

        windows/edit_theatre.cpp
        windows/create_theatre.cpp
        windows/theatres.cpp
        windows/theatre.cpp
        windows/create_actor.cpp
        windows/actors.cpp
        windows/actor.cpp

        )

set(P_H
        dialogs/TDCheck.h
        dialogs/TDLogin.h

        templates/TTModel.h

        utils/TComboBox.h
        utils/TConfig.h
        utils/TDB.h
        utils/TListBox.h

        windows/TMainMenu.h
        windows/TMainWindow.h

        windows/user/TUser.h
        windows/user/TUsers.h
        windows/user/TUserCreate.h
        windows/user/TUserEdit.h

        windows/edit_theatre.h
        windows/create_theatre.h
        windows/theatres.h
        windows/theatre.h
        windows/create_actor.h
        windows/actors.h
        windows/actor.h

        )

qt5_wrap_cpp(GENERATED_SOURCES ${P_H})
qt5_add_resources(RES res/res.qrc)

add_executable(Theatre_Admin ${P_S} ${P_H} ${RES})
qt5_use_modules(Theatre_Admin Core Widgets Network Concurrent)
target_compile_features(Theatre_Admin PRIVATE cxx_range_for)
target_link_libraries(Theatre_Admin ${Qt5Core_QTMAIN_LIBRARIES})