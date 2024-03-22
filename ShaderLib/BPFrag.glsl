#version 460 core
in vec3 nNormal;
in vec2 nTexCoord;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

vec3 BlinnPhong();
void main()
{
   FragColor=vec4(BlinnPhong(),1.0);
   //FragColor=texture(texture_diffuse1,nTexCoord);
    //FragColor=vec4(vec3(gl_FragCoord.z),1.0);
} 

vec3 BlinnPhong()
{
	vec3 color=texture(texture_diffuse1,nTexCoord).rgb;
	float ambintNum=0.1;
	vec3 ambint=color*ambintNum;

	vec3 normal_=normalize(nNormal);
	vec3 lightDir=normalize(lightPos-FragPos);//��frag��light
	float diffNum=max(dot(normal_,lightDir),0.0);
	vec3 diffuse=diffNum*color;

	float specStrength=0.5;
	vec3 viewDir=normalize(viewPos-FragPos);//��frag��view
	vec3 reflectDir=reflect(-lightDir,normal_);
	float specNum=pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specular=specStrength*texture(texture_specular1,nTexCoord).rgb;

	return diffuse+ambint+specular;

}