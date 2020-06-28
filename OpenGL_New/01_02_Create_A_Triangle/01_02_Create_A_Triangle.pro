TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    ../src/glad.c


INCLUDEPATH += ../include/

LIBS += -lSDL2 -ldl

DISTFILES += \
    vertex.vert \
    fragment.frag
