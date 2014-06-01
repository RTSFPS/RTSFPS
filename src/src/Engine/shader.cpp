#define NO_SDL_GLEXT

#include "../conf.h"

#ifdef OS_WIN
#include <Windows.h>
#endif
#include <glew.h>
#ifdef OS_WIN
#include <gl/GL.h>
#endif
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <SDL.h>
#include <SDL_opengl.h>


using namespace std;

#include "../tools.h"
#include "shader.h"


vector <string> split(const string& str, const string& delimiter = " ") {
    vector <string> tokens;

    string::size_type lastPos = 0;
    string::size_type pos = str.find(delimiter, lastPos);

    while (string::npos != pos) {
        // Found a token, add it to the vector.
        cout << str.substr(lastPos, pos - lastPos) << endl;
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = pos + delimiter.size();
        pos = str.find(delimiter, lastPos);
    }

    tokens.push_back(str.substr(lastPos, str.size() - lastPos));
    return tokens;
}

shader::shader(string shadername)
{

	string filenameVertexShader=shadername+".vert";
	string filenameFragmentShader=shadername+".frag";
	string filenameScriptShader=shadername+".scrpt";


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







	ifstream inputSSfile(filenameScriptShader.c_str());

	if (!inputSSfile) error("[shader] Error opening Script Shader File "+filenameScriptShader);

	string s;
	vector <string> fields;
	unsigned int i=0;
	while(!inputSSfile.eof())
	{
		memset (ch,0,256);
		inputSSfile.getline(ch,256);
		if(inputSSfile.eof()) break;
		s=ch;

		// log(" - glBindAttribLocation("+numstr(i)+","+s+")");
		  fields = split( s, ":" );
	

		
		glBindAttribLocation(prog, i, fields[1].c_str());
		i++;
	}



	inputSSfile.close();



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
