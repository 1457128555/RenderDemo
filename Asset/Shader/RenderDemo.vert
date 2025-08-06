#version 300 es

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTexCoord;

out vec4 oTexCoord;

void main() 
{
    gl_Position = vec4(vPos, 1.0);
    oTexCoord = vec4(vTexCoord, 0.f, 1.f);
}