#version 150 core

uniform mat4 matrix;


in vec3 inVertex;
in vec3 inColor;

out vec3 vertex_Color;

void main () 
{
	vertex_Color = inColor;
	gl_Position  = matrix * vec4(inVertex,1.0);
	
}