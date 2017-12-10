#version 330 core

//in vec3 ourColor;

uniform sampler2D earthSample;

in vec2 texCoords;
out vec4 color;

void main()
{
    vec3 baseColor = texture(earthSample,texCoords).xyz;

    color = vec4(baseColor, 1.0f);
}