TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    heap.cpp \
    freelists.cpp \
    buddysystem.cpp

HEADERS += \
    heap.h \
    freelists.h \
    freelist.h \
    buddysystem.h \
    block.h

