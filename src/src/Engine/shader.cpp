#define NO_SDL_GLEXT

#include <Windows.h>
#include <GLew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>
#include <stdlib.h>
#include <fstream>


#include <SDL.h>
#include <SDL_opengl.h>


using namespace std;

#include "../tools.h"
#include "shader.h"




shader::shader(string filenameVertexShader, string filenameFragmentShader)
{
	ifstream inputVSfile(filenameVertexShader.c_str());

	if (!inputVSfile) error("[shader] Error opening Vertex Shader File "+filenameFragmentShader);

	vsSource="";
	char ch[256];
	while(!inputVSfile.eof())
	{
		inputVSfile.getline(ch,256);
		vsSource+=ch;
		vsSource+="\n";
	}
	inputVSfile.close();






		vsID=glCreateShader(GL_VERTEX_SHADER);

		const char* VSsource=vsSource.c_str();

			
		glShaderSource(vsID,1,&VSsource,NULL);

		glCompileShader(vsID);


		GLint shaderCompiled;

		glGetShaderiv(vsID, GL_COMPILE_STATUS, &shaderCompiled);
		if(shaderCompiled == GL_FALSE)
		{
			char errorbuff[256];
			glGetShaderInfoLog(vsID,256,NULL,errorbuff);

			error("ERROR: "+filenameVertexShader+"\n"+errorbuff);
		}


	


	ifstream inputFSfile(filenameFragmentShader.c_str());

	if (!inputFSfile) error("[shader] Error opening Fragment Shader File "+filenameFragmentShader);

	fsSource="";
	
	while(!inputFSfile.eof())
	{
		inputFSfile.getline(ch,256);
		fsSource+=ch;
		fsSource+="\n";
	}
	inputFSfile.close();

		fsID=glCreateShader(GL_FRAGMENT_SHADER);

		const char* FSsource=fsSource.c_str();

		glShaderSource(fsID,1,&FSsource,NULL);

		glCompileShader(fsID);


		glGetShaderiv(fsID, GL_COMPILE_STATUS, &shaderCompiled);
		if(shaderCompiled == GL_FALSE)
		{

			char errorbuff[256];
			glGetShaderInfoLog(fsID,256,NULL,errorbuff);

			error("ERROR: "+filenameFragmentShader+"\n"+errorbuff);
		}




		prog=glCreateProgram();

		


		glAttachShader(prog,vsID);
		glAttachShader(prog,fsID);

		
		glLinkProgram(prog);

	
}

shader::~shader()
{
	glDetachShader(prog,vsID);
	glDetachShader(prog,fsID);
	glDeleteShader(vsID);
	glDeleteShader(fsID);
	glDeleteProgram(prog);
}


  
void shader::useShader()
{
	glUseProgram(prog);
}


void shader::delShader()
{
	glUseProgram(0);
}