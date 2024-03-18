#version 460 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;
//out vec3 nColor;
out vec2 nTexCoord;
uniform mat4 MVP;
void main()
{
    gl_Position = MVP*vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //nColor=aPos;
    nTexCoord=aTexCoord;
}