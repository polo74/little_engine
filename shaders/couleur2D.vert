#version 330

layout (location = 0) in vec2 in_vertex;

out vec3 med_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;

void main()
{
	med_color = color;
	gl_Position = vec4(in_vertex, 0.0, 1.0);
}
