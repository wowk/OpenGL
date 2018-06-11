TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    GL/src/glad.c

LIBS += -lGL -lGLU -lSDL2 -ldl
INCLUDEPATH += GL/include/

DISTFILES += \
    shader.frag \
    shader.vert
