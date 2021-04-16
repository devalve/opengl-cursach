#version 330 core

out vec4 FragColor;

in vec2 ourCoord;


uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D ourTextureSampler;

uniform vec3 lightColor;
uniform vec3 posColor;
uniform vec3 objColor;

void main()
{
    float ambientStr = 0.1;
    vec3 ambient = ambientStr*lightColor;
    vec3 res=ambient*objColor;

    FragColor = mix(texture(tex0, ourCoord), texture(tex1, ourCoord), 0.2);
};