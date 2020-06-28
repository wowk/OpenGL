TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    ../src/glad.c

HEADERS += \
    include/glad/glad.h \
    include/KHR/khrplatform.h

INCLUDEPATH += ../include/

LIBS += -lSDL2 -ldl
