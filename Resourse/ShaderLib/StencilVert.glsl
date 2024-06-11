#version 460 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;


uniform mat4 model1;
uniform mat4 view1;
uniform mat4 projection1;
void main()
{
    gl_Position = projection1*view1*model1*vec4(pos.x, pos.y, pos.z, 1.0);

}