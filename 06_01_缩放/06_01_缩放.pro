TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    GL/src/glad.cpp

INCLUDEPATH += GL/include
LIBS += -lGL -lGLU -lSDL2 -lSDL2_image -ldl -std=c++11


DISTFILES += \
    shader.frag \
    shader.vert
