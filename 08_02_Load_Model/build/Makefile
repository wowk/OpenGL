srcdir=../
BIN = test

CFLAGS = -I $(srcdir)/. -I $(srcdir)GL/include
LIBS += -lSDL2 -lSDL2_image -lassimp -ldl #-lGL -lGLU

OBJS =	$(srcdir)/GL/src/glad.o \
		$(srcdir)/GLShader.o \
		$(srcdir)/GLTexture.o \
		$(srcdir)/main.o \
		$(srcdir)/Utils.o \
		$(srcdir)/GLMesh.o \
		$(srcdir)/GLModel.o \
		$(srcdir)/GLCamera.o \
		$(srcdir)/GLApplication.o \
		$(srcdir)/GLScene.o \
		$(srcdir)/MyGLApplication.o \
		$(srcdir)/MyGLScene.o \
		$(srcdir)/GLObject.o

all: $(OBJS)
	g++ *.o -o $(BIN) $(LIBS)

%.o:%.cpp
	g++ $(CFLAGS) -c $^

clean:
	-rm -rf *.o $(BIN)
