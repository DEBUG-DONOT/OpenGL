#version 460 core
layout(location=0) in vec3 aPos;
out vec3 TexCoord;

uniform mat4 SkyBoxProjection;
uniform mat4 SkyBoxView;
//uniform mat4 SkyBoxMVP;

void main()
{
	gl_Position=SkyBoxProjection*SkyBoxView*vec4(aPos,1.0);
	//gl_Position=SkyBoxMVP*vec4(aPos,1.0);
	TexCoord=aPos;
}