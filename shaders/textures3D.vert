#version 330

#extension GL_ARB_explicit_uniform_location : require

layout (location = 0) in vec3 in_Vertex;
layout (location = 1) in vec2 in_uvs;

out vec2 uvs;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);

	uvs= in_uvs;
}
