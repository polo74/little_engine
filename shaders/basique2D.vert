#version 330 core

uniform mat4 projection;
uniform mat4 view;

layout(location = 0) in vec2 in_Vertex;

void main()
{
    gl_Position = projection * view * vec4(in_Vertex, 0.0, 1.0);
}
