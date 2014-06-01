CC=g++

INCLUDES_FRAMEWORKS=-I./src/ -I./src/Frameworks/GLew/include -I./src/Frameworks/glm -I./src/Frameworks/SDL2/include -I./src/Frameworks/Bullet/src


INCLUDES_CODE=-I./src/ \
		-I./src/Engine \
		-I./src/Gameplay


CFLAGS=$(INCLUDES_FRAMEWORKS) $(INCLUDES_CODE)
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU -lGLEW -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath

# CFLAGS+=-Wall -Wextra -Winit-self -Woverloaded-virtual -Wuninitialized -Wint-to-pointer-cast -Weffc++ -O3 -std=c++11 -msse3
CFLAGS+=-O3 -std=c++11 -msse3 -w


SOURCES=./src/main.cpp ./src/tools.cpp ./src/conf.cpp \
	./src/Engine/drawfont.cpp ./src/Engine/freecam.cpp ./src/Engine/renderer.cpp ./src/Engine/GLstuff.cpp \
	./src/Engine/INIparser.cpp ./src/Engine/keys.cpp ./src/Engine/OBJparser.cpp ./src/Engine/SDLgraph.cpp \
	./src/Engine/ObjectCreator.cpp \
	./src/Engine/shader.cpp ./src/Engine/skybox.cpp \
	./src/Gameplay/test.cpp
 
EXECUTABLE=RTSFPS

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE) $(SOURCES) 
