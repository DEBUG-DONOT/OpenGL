#version 460 core

out vec4 FragColor;
in vec3 TexCoord;

uniform samplerCube skybox;

void main()
{
	float gamma =2.2;
	FragColor=texture(skybox,TexCoord);
	//FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
}