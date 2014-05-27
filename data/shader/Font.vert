#version 420

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;

uniform mat4 matrix;

out vec2 texture_coordinates;

void main () 
{
	texture_coordinates = vertex_uv;
	gl_Position = matrix * vec4 (vertex_position, 1.0);
}