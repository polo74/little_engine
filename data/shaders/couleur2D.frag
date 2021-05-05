#version 330

in vec3 med_color;

out vec4 out_color;

void main()
{
    out_color = vec4(med_color, 1.0f);
}
