#-------------------------------------------------
#
# Project created by QtCreator 2018-05-10T22:12:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
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

RC_ICONS = worms.ico

asdasd

SOURCES += \
        ..\src\main.cpp \
        ..\src\client_connector.cpp \
        ..\src\socket.cpp \
        ..\src\socket_error.cpp \
        ..\src\client_lobby.cpp \
        ..\src\protocol.cpp \
        ..\src\client_lobby_feeder.cpp \
        ..\src\protocol_error.cpp \
        ..\src\thread.cpp

HEADERS += \
        ..\src\client_connector.h \
        ..\src\socket.h \
        ..\src\socket_error.h \
        ..\src\client_lobby.h \
        ..\src\protocol.h \
        ..\src\protocol_error.h \
        ..\src\client_lobby_feeder.h \
        ..\src\thread.h \
        ..\include\yaml-cpp\yaml.h

FORMS += \
        client_connector.ui \
        client_lobby.ui

RESOURCES += \
        client_resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lyaml-cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lyaml-cpp
else:unix: LIBS += -L$$PWD/libs/ -lyaml-cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/release/ -lyaml-cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/debug/ -lyaml-cpp
else:unix: LIBS += -L$$PWD/../libs/ -lyaml-cpp

INCLUDEPATH += $$PWD/../libs
DEPENDPATH += $$PWD/../libs

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libs/release/libyaml-cpp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libs/debug/libyaml-cpp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libs/release/yaml-cpp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libs/debug/yaml-cpp.lib
else:unix: PRE_TARGETDEPS += $$PWD/../libs/libyaml-cpp.a
