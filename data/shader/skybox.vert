#version 330
 
in vec3 inVertex;
out vec3 texCoord;
uniform mat4 matrix;
 
void main() 
{
    gl_Position = matrix * vec4(inVertex, 1.0);
    texCoord = inVertex;
}