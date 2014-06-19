#version 150 core

in vec3 vertex_Color;
out vec4 outcolor;


void main () 
{
	outcolor = vec4(vertex_Color,1.0);
}