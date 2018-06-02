#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T16:48:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BOOK-M
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


SOURCES += \
        main.cpp \
    administrator.cpp \
    find_password.cpp \
    login.cpp \
    new_user.cpp \
    reader.cpp

HEADERS += \
    administrator.h \
    find_password.h \
    login.h \
    new_user.h \
    reader.h

FORMS += \
    administrator.ui \
    find_password.ui \
    login.ui \
    new_user.ui \
    reader.ui

RESOURCES += \
    image/image.qrc

CONFIG += c++11

