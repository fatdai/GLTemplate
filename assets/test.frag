#version 330

in vec2 TexCoord0;

uniform sampler2D gSampler;

out vec4 outFlagColor;

void main()
{
    outFlagColor = texture(gSampler,TexCoord0);
}