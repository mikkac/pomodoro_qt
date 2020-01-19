#-------------------------------------------------
#
# Project created by QtCreator 2020-01-14T14:36:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pomodoro
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++1z

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SRCPATH += $$PWD"/src"
SOURCES += \
        $$SRCPATH/main.cpp \
        $$SRCPATH/pomodoro_view.cpp \
        $$SRCPATH/pomodoro_model.cpp \
        $$SRCPATH/mode_manager.cpp \
        $$SRCPATH/timer.cpp \
        $$SRCPATH/settings_manager.cpp \
        $$SRCPATH/ui_settings_widget.cpp

INCLUDEPATH += $$PWD"/inc"
HEADERS += \
        $$INCLUDEPATH/pomodoro_view.h \
        $$INCLUDEPATH/ipomodoro_model.h \
        $$INCLUDEPATH/imode_manager.h \
        $$INCLUDEPATH/isettings_manager.h \
        $$INCLUDEPATH/itimer.h \
        $$INCLUDEPATH/pomodoro_model.h \
        $$INCLUDEPATH/mode_manager.h \
        $$INCLUDEPATH/settings_manager.h \
        $$INCLUDEPATH/timer.h \
        $$INCLUDEPATH/common.h \
        $$INCLUDEPATH/ui_settings_widget.h

FORMS += \
        pomodoro_view.ui \
        settings_widget.ui
