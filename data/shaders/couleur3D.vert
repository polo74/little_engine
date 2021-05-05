// Version du GLSL

#version 330

// Entr�es

layout (location = 0) in vec3 in_Vertex;
layout (location = 1) in vec3 in_Color;

// Uniform

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Sortie

out vec3 color;

// Fonction main

void main()
{
    // Position finale du vertex en 3D

    gl_Position = projection * view * model * vec4(in_Vertex, 1.0);

    // Envoi de la couleur au Fragment Shader

    color = in_Color;
}
