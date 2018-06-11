TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    GL/src/glad.c

LIBS += -lSDL2 -lSDL2_image -lGL -lGLU -ldl

INCLUDEPATH += ./GL/include/
