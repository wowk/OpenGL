TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    GL/src/glad.cpp \
    GLApplication.cpp \
    GLCamera.cpp \
    GLLight.cpp \
    GLMaterial.cpp \
    GLMesh.cpp \
    GLModel.cpp \
    GLObject.cpp \
    GLScene.cpp \
    GLShader.cpp \
    GLTexture.cpp \
    main.cpp \
    MyGLApplication.cpp \
    MyGlass.cpp \
    MyGLScene.cpp \
    Utils.cpp

DISTFILES += \
    resources/models/knight/knight.c4d \
    resources/models/hw_alps/hw_alps.shader \
    resources/models/female/female02.zip \
    resources/models/fh0gwod4bpj4-knight.zip \
    resources/models/hw_alps.zip \
    resources/images/container.jpg \
    resources/models/City/Maps/ang1.jpg \
    resources/models/City/Maps/cty1.jpg \
    resources/models/City/Maps/cty2x.jpg \
    resources/models/City/c1.jpg \
    resources/models/City/c10.jpg \
    resources/models/City/c11.jpg \
    resources/models/City/c12.jpg \
    resources/models/City/c2.jpg \
    resources/models/City/c3.jpg \
    resources/models/City/c4.jpg \
    resources/models/City/c5.jpg \
    resources/models/City/c6.jpg \
    resources/models/City/c7.jpg \
    resources/models/City/c8.jpg \
    resources/models/City/c9.jpg \
    resources/models/female/female02_1.jpg \
    resources/models/female/female02_10.jpg \
    resources/models/female/female02_2.jpg \
    resources/models/knight/armor.jpg \
    resources/models/knight/gen.face.jpg \
    resources/images/awsomeface.png \
    resources/images/transparent_window.png \
    resources/models/hw_alps/alps_bk.tga \
    resources/models/hw_alps/alps_dn.tga \
    resources/models/hw_alps/alps_ft.tga \
    resources/models/hw_alps/alps_lf.tga \
    resources/models/hw_alps/alps_rt.tga \
    resources/models/hw_alps/alps_up.tga \
    resources/models/City/City.mtl \
    resources/models/City/readme The City.txt \
    resources/models/City/The_City.mtl \
    resources/models/female/female02.mtl \
    resources/models/female/License.txt \
    resources/models/hw_alps/license.txt \
    resources/models/sphere/sphere.mtl \
    resources/shaders/glass.frag \
    resources/shaders/globalLight.frag \
    resources/shaders/model.frag \
    resources/shaders/glass.vert \
    resources/shaders/globalLight.vert \
    resources/shaders/model.vert

HEADERS += \
    GLApplication.hpp \
    GLCamera.hpp \
    GLLight.hpp \
    GLMaterial.hpp \
    GLMesh.hpp \
    GLModel.hpp \
    GLObject.hpp \
    GLScene.hpp \
    GLShader.hpp \
    GLTexture.hpp \
    MyGLApplication.hpp \
    MyGlass.hpp \
    MyGLScene.hpp \
    Utils.hpp

INCLUDEPATH += GL/include
LIBS += -lSDL2 -lSDL2_image -lassimp -ldl
