#version 460 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;
out vec3 nNormal;
out vec2 nTexCoord;
out vec3 FragPos;
uniform mat4 MVP;
uniform mat4 model;
void main()
{
    gl_Position = MVP*vec4(pos.x, pos.y, pos.z, 1.0);
    nTexCoord=texCoord;
    nNormal=mat3(transpose(inverse(model)))*normal;
    FragPos=vec3(model*vec4(pos,1.0));
}