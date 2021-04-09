#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 ourCoord;
uniform sampler2D ourTextureSampler;
uniform float countTex;
uniform sampler2D tex0;
uniform sampler2D tex1;

void main()
{
    FragColor = mix(texture(tex0, ourCoord), texture(tex1, vec2(-ourCoord.x, ourCoord.y)), countTex);
};