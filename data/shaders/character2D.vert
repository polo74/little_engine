#version 330 core

#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 uvs;

out vec2 texCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	gl_Position = projection *  view * model * vec4(vertex, 0.0, 1.0);
	texCoord = uvs;
}
