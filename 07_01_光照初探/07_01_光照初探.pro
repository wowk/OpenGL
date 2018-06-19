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
    GLTexture.cpp \
    GLCamera.cpp \
    MyCube.cpp


INCLUDEPATH += GL/include/

LIBS += -lSDL2 -lSDL2_image -lGL -lGLU -ldl

HEADERS += \
    Utils/FileUtil.h \
    Utils/ImageUtil.h \
    GLApplication.hpp \
    GLObject.hpp \
    GLScene.hpp \
    GLShader.hpp \
    GLTexture.hpp \
    MyGLApplication.hpp \
    MyGLScene.hpp \
    GLCamera.hpp \
    MyCube.hpp

DISTFILES += \
    shader.frag \
    shader.vert
