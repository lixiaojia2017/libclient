#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T16:48:37
#
#-------------------------------------------------

QT       += core gui network

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
    login.cpp \
    new_user.cpp \
    reader.cpp \
    backend/abstractrqt.cpp \
    backend/loginhdl.cpp \
    backend/responsehdl.cpp \
    backend/socketthread.cpp \
    backend/token.cpp \
    backend/userrqt.cpp \
    find_password.cpp \
    fileHandler/confighandler.cpp \
    3rd-party/aes256.cpp \
    fileHandler/qbyteaes.cpp \
    backend/handle/constructer/userconstructer.cpp \
    backend/handle/constructer/queryconstructer.cpp \
    backend/handle/constructer/abstractconstructer.cpp \
    backend/handle/constructer/operateuserconstructer.cpp \
    backend/handle/constructer/operategroupconstructer.cpp \
    backend/handle/constructer/operatebookconstructer.cpp \
    backend/handle/constructer/loadconstructer.cpp \
    backend/handle/constructer/appointconstructer.cpp \
    backend/handle/constructer/checkconstructer.cpp

HEADERS += \
    login.h \
    new_user.h \
    reader.h \
    backend/abstractrqt.h \
    backend/loginhdl.h \
    backend/responsehdl.h \
    backend/socketthread.h \
    backend/token.h \
    backend/userrqt.h \
    find_password.h \
    fileHandler/confighandler.h \
    3rd-party/aes256.h \
    3rd-party/json.hpp \
    fileHandler/qbyteaes.h \
    backend/handle/constructer/constructer.h.autosave \
    backend/handle/constructer/handle.h.autosave \
    backend/handle/constructer/loadhdl.h.autosave \
    backend/handle/constructer/operatebookhdl.h.autosave \
    backend/handle/constructer/operategrouphdl.h.autosave \
    backend/handle/constructer/operateuserhdl.h.autosave \
    backend/handle/constructer/queryhdl.h.autosave \
    backend/handle/constructer/userhdl.h.autosave \
    backend/handle/constructer/userconstructer.h \
    backend/handle/constructer/class querybook: public queryconstructer \
    backend/handle/constructer/queryconstructer.h \
    backend/handle/constructer/abstractconstructer.h \
    backend/handle/constructer/operateuserconstructer.h \
    backend/handle/constructer/operategroupconstructer.h \
    backend/handle/constructer/operatebookconstructer.h \
    backend/handle/constructer/loadconstructer.h \
    backend/handle/constructer/appointconstructer.h \
    backend/handle/constructer/checkconstructer.h

FORMS += \
    find_password.ui \
    login.ui \
    new_user.ui \
    reader.ui

RESOURCES += \
    image/image.qrc \
    image/qss.qrc

CONFIG += c++11
