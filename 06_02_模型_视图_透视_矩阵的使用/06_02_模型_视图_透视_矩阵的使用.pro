TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    GLApplication.cpp \
    MyGLApplication.cpp \
    GLScene.cpp \
    MyGLScene.cpp \
    GL/src/glad.cpp \
    GLObject.cpp \
    GLShader.cpp \
    Utils/FileUtil.cpp \
    Utils/ImageUtil.cpp \
    GLTexture.cpp


INCLUDEPATH += GL/include/

LIBS += -lSDL2 -lSDL2_image -lGL -lGLU -ldl

HEADERS += \
    GLApplication.h \
    MyGLApplication.h \
    GLScene.h \
    MyGLScene.h \
    GLObject.h \
    GLShader.h \
    Utils/FileUtil.h \
    Utils/ImageUtil.h \
    GLTexture.h

DISTFILES += \
    shader.frag \
    shader.vert
