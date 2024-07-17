#version 460 core
in vec3 nNormal;
in vec2 nTexCoord;
in vec3 WorldPos;
out vec4 FragColor;
//texture
uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

const float PI=3.14159;
vec3 Fresnel(float hDOTv,vec3 F0);
float Distribution(float roughNess,float nDOTh);
float GGXFunction(vec3 n,vec3 v,vec3 l,float roughNess);
float GSchlick(float nDOTv,float roughNess);

void main()
{
	vec3 N=normalize(texture(normalMap,nTexCoord).rgb);//法向量
	vec3 L=normalize((lightPos-WorldPos).rgb);//入射向量
	vec3 V=normalize((viewPos-WorldPos).rgb);
	vec3 H=normalize(L+V);
	float hDOTv=dot(H,V);
	float nDOTh=dot(N,H);
	float nDOTL=dot(N,L);
	float roughNess=texture(roughnessMap,nTexCoord).r;
	float metallic=texture(metallicMap,nTexCoord).r;
	vec3 albedo=texture(albedoMap,nTexCoord).rgb;
	float ao=texture(aoMap,nTexCoord).r;
	
	vec3 F0=vec3(0.04);
	F0=mix(F0,albedo,metallic);//mix是插值函数
	vec3 F=Fresnel(hDOTv,F0);
	float D=Distribution(roughNess,nDOTh);
	float G=GGXFunction(N,V,L,roughNess);
	vec3 kd=F;
	vec3 ks=vec3(1.0)-kd;
	
	float dis=length(WorldPos-lightPos);
	float attenuation=1.0/(dis*dis);
	vec3 radiance=lightColor*attenuation;

	//spec
	float nominator=dot(ks,F)*D*G;
	float denominator=4.0*max(dot(V,N),0.0)*max(dot(L,N),0.0)+0.001;
	float spec=nominator/denominator;

	vec3 Lo=(dot(kd,albedo)/PI+spec)*radiance*nDOTL;
	//vec3 ambient=ao*0.03*albedo;//?
	vec3 ambient=ao*vec3(0.03)*albedo;
	vec3 color=Lo+ambient;
	FragColor=vec4(color,1.0);


}

vec3 Fresnel(float hDOTv,vec3 F0)
{
	//float re=F0+(1-F0)*pow(1-hDOTv,5);
	//return re;
	return F0+(1-F0)*pow(clamp(1.0-hDOTv,0.0,1.0),5.0);//限制了值
}

float Distribution(float roughNess,float nDOTh)
{
	float a2=roughNess*roughNess;
	float nDOTh2=nDOTh*nDOTh;
	float behindNum=nDOTh2*(a2-1.0)+1.0;
	return a2/(PI*behindNum*behindNum);
}

float GSchlick(float nDOTv,float roughNess)
{
	float k=(roughNess+1.0)*(roughNess+1.0)/8.0;//直接光照
	float behindNum=nDOTv*(1-k)+k;
	return nDOTv/behindNum;
}

float GGXFunction(vec3 n,vec3 v,vec3 l,float roughNess)
{
	float ndv=dot(n,v);
	float ndl=dot(n,l);
	return GSchlick(ndv,roughNess)*GSchlick(ndl,roughNess);
}
