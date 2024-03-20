#version 460 core
in vec2 nTexCoord;
out vec4 FragColor;
uniform sampler2D texture_diffuse1;
//uniform sampler2D texture_specular1;
void main()
{
   FragColor=texture(texture_diffuse1,nTexCoord);
} 