#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec2 in_Vertex;

void main()
{
    gl_Position = projection * view * model * vec4(in_Vertex.x, in_Vertex.y, 0.0, 1.0);
}
