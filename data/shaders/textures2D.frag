#version 330 core

out vec4 out_Color;

in vec2 texCoord;

uniform sampler2D my_texture;
uniform vec3 color;

void main()
{
	out_Color = texture(my_texture, texCoord);
}
