#version 330

in vec2 uvs;

out vec4 out_Color;

uniform sampler2D my_texture;

void main()
{
    out_Color = texture(my_texture, uvs);
}
