TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    GL/src/glad.c

INCLUDEPATH += GL/include
LIBS += -lGL -lGLU -lSDL2 -lSDL2_image -ldl

DISTFILES += \
    shader.frag \
    shader.vert
