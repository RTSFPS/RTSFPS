CC=g++

INCLUDES_FRAMEWORKS=-I./src/ -I./Frameworks/GLew/include -I./Frameworks/glm -I./Frameworks/SDL2/include -I./Frameworks/Bullet/src


INCLUDES_CODE=	-I./src/ \
		-I./src/Common/ \
		-I./src/Components/ \
		-I./src/Entitys/ \
		-I./src/EntitySystem/ \
		-I./src/EventMessages/ \
		-I./src/EventSystem/ \
		-I./src/Factories/ \
		-I./src/GraphicTools/ \
		-I./src/Managers/ \
		-I./src/SysemTools/
	
		


CFLAGS=$(INCLUDES_FRAMEWORKS) $(INCLUDES_CODE)
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU -lGLEW -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath

# CFLAGS+=-Wall -Wextra -Winit-self -Woverloaded-virtual -Wuninitialized -Wint-to-pointer-cast -Weffc++ -O3 -std=c++11 -msse3
CFLAGS+=-O3 -std=c++11 -msse3 -w


SOURCES=./src/main.cpp ./src/tools.cpp ./src/conf.cpp \
	./src/Common/ContentLoader.cpp \
	./src/Components/Camera.cpp ./src/Components/CharacterController.cpp ./src/Components/FramesPerSecond.cpp ./src/Components/Material.cpp \
	./src/Components/Mesh.cpp ./src/Components/MeshRenderer.cpp ./src/Components/Renderer.cpp ./src/Components/RenderManager.cpp \
	./src/Components/RigidBody.cpp ./src/Components/SkyBoxRenderer.cpp ./src/Components/TextRenderer.cpp ./src/Components/Transform.cpp \
	./src/Entitys/EventHandler.cpp ./src/Entitys/InputHandler.cpp ./src/Entitys/Player.cpp \
	./src/EventMessages/EventInput.cpp ./src/EventMessages/EventSystemMessages.cpp \
	./src/EventSystem/EventSystem.cpp \
	./src/Factories/EntityFactory.cpp ./src/Factories/MeshFactory.cpp \
	./src/GraphicTools/DrawFont.cpp ./src/GraphicTools/GLstuff.cpp ./src/GraphicTools/SDLgraph.cpp ./src/GraphicTools/Shader.cpp \
	./src/Managers/PhysicsManager.cpp \
	./src/SystemTools/INIparser.cpp ./src/SystemTools/ObjectCreator.cpp ./src/SystemTools/OBJparser.cpp
	
 
EXECUTABLE=RTSFPS

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE) $(SOURCES) 
