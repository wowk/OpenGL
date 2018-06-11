TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    GL/src/glad.c

INCLUDEPATH += GL/include
LIBS += -lSDL2 -lGL -lGLU -ldl

DISTFILES += \
    shader.frag \
    shader.vert
