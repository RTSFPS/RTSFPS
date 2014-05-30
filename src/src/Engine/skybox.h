#pragma once
#define NO_SDL_GLEXT


#include <glm.hpp>
#include <ext.hpp>

using namespace glm;


#include "shader.h"
#include "renderer.h"



class skybox
{
public:

	void initSkyBox(float size);
	void closeSkyBox();

	void renderSkyBox(mat4x4 m);

	

private:
	enum {SKY_LEFT=0,SKY_BACK=1,SKY_RIGHT=2,SKY_FRONT=3,SKY_TOP=4,SKY_BOTTOM=5};
	unsigned int skyboxtextures[6];
	unsigned int loadTexture(string filename);
    
    float size;
    
	shader* SkyShader;
    int matrix_location;

    
    
    float vert_left[12];
    float vert_back[12];
    float vert_right[12];
    float vert_front[12];
    float vert_top[12];
    float vert_bottom[12];

    float text_left[8];
    float text_back[8];
    float text_right[8];
    float text_front[8];
    float text_top[8];
    float text_bottom[8];
    
	
	renderer* back;
	renderer* left;
	renderer* front;
	renderer* right;
	renderer* top;
	renderer* bottom;
};