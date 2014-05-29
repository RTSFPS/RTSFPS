#pragma once
#define NO_SDL_GLEXT


#include <glm.hpp>
#include <ext.hpp>

using namespace glm;


#include "shader.h"



class skybox
{
public:

	void initSkyBox(float size);
	void closeSkyBox();

	void renderSkyBox();

private:
	enum {SKY_LEFT=0,SKY_BACK=1,SKY_RIGHT=2,SKY_FRONT=3,SKY_TOP=4,SKY_BOTTOM=5};
	unsigned int skyboxtextures[6];
	unsigned int loadTexture(string filename);
    
    float size;
    
    shader* skyShader;
    int matrix_location;
    mat4 matrix;
    
    
    float* vert_left;
    float* vert_back;
    float* vert_right;
    float* vert_front;
    float* vert_top;
    float* vert_bottom;

    float* text_left;
    float* text_back;
    float* text_right;
    float* text_front;
    float* text_top;
    float* text_bottom;
    
    unsigned int left_vertVBO;
    unsigned int left_textVBO;
    unsigned int left_VAO;
    
    unsigned int back_vertVBO;
    unsigned int back_textVBO;
    unsigned int back_VAO;
    
    unsigned int right_vertVBO;
    unsigned int right_textVBO;
    unsigned int right_VAO;
    
    unsigned int front_vertVBO;
    unsigned int front_textVBO;
    unsigned int fron_VAO;
    
    unsigned int top_vertVBO;
    unsigned int top_textVBO;
    unsigned int top_VAO;
    
    unsigned int bottom_vertVBO;
    unsigned int bottom_textVBO;
    unsigned int bottom_VAO;
};