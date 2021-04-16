#version 330 core

out vec4 FragColor;

in vec2 ourCoord;


uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D ourTextureSampler;

void main()
{
    FragColor = mix(texture(tex0, ourCoord), texture(tex1, ourCoord), 0.2);
};