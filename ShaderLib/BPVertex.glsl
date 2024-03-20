#version 460 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;
out vec2 nTexCoord;
uniform mat4 MVP;
void main()
{
    gl_Position = MVP*vec4(pos.x, pos.y, pos.z, 1.0);
    nTexCoord=texCoord;
}