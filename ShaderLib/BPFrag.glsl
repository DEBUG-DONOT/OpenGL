#version 460 core
//in vec3 nColor;
in vec2 nTexCoord;
out vec4 FragColor;
//uniform vec4 ourColor;
uniform sampler2D ourTex;

//uniform sampler2D ourTex1;
//uniform float mixNum;
void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //FragColor=mix(texture(ourTex,nTexCoord),texture(ourTex1,nTexCoord),mixNum);
   //FragColor=vec4(nColor,1.0f);
   FragColor=texture(ourTex,nTexCoord);
} 