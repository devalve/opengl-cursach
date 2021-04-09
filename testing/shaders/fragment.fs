#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 ourCoord;
uniform sampler2D ourTextureSampler;

void main()
{
    FragColor = texture(ourTextureSampler, ourCoord);
};
