#version 330 core

out vec4 out_Color;

in vec2 texCoord;

uniform sampler2D my_texture;
uniform vec3 color;

void main()
{
	out_Color = vec4(color, 1.0) * vec4(1.0, 1.0, 1.0, texture(my_texture, texCoord));
}
