#version 430 core

in vec2 texture_coordinates;
out vec4 frag_colour;

layout (binding = 0) uniform sampler2D basic_texture;




void main () {
	vec4 texel = texture(basic_texture, texture_coordinates);
	frag_colour = texel;
}