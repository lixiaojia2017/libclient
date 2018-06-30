INCLUDEPATH += $$PWD
CONFIG += dll
CONFIG += c++11

QT += widgets\
      webengine\
      webenginecore\
      webenginewidgets\
      webchannel

HEADERS =\
    $$PWD/qpdfwidget.h \
    $$PWD/pdfjsbridge.h

SOURCES =\
    $$PWD/qpdfwidget.cpp \
    $$PWD/pdfjsbridge.cpp

RESOURCES += $$PWD/pdfview.qrc
