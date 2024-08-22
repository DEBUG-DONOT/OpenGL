#version 460 core
in vec3 nNormal;
in vec2 nTexCoord;
in vec3 WorldPos;
out vec4 FragColor;
//texture
//uniform sampler2D albedoMap;
uniform sampler2D texture_albedo1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_metallic1;
uniform sampler2D texture_roughness1;
uniform sampler2D texture_ao1;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

const float PI=3.14159;
vec3 GetNormal();
vec3 Fresnel(float hDOTv,vec3 F0);
float Distribution(float roughNess,float nDOTh);
float GGXFunction(vec3 n,vec3 v,vec3 l,float roughNess);
float GSchlick(float nDOTv,float roughNess);


void main()
{
	//vec3 N=normalize(texture(normalMap,nTexCoord).rgb);//法向量
	vec3 N=GetNormal();
	vec3 L=normalize((lightPos-WorldPos).rgb);//入射向量
	vec3 V=normalize((viewPos-WorldPos).rgb);
	vec3 H=normalize(L+V);
	float hDOTv=dot(H,V);
	float nDOTh=dot(N,H);
	float nDOTL=dot(N,L);
	float roughNess=texture(texture_roughness1,nTexCoord).r;
	float metallic=texture(texture_metallic1,nTexCoord).r;
	vec3 albedo=texture(texture_albedo1,nTexCoord).rgb;
	float ao=texture(texture_ao1,nTexCoord).r;
	
	vec3 F0=vec3(0.04);
	F0=mix(F0,albedo,metallic);//mix是插值函数
	vec3 F=Fresnel(hDOTv,F0);
	float D=Distribution(roughNess,nDOTh);
	float G=GGXFunction(N,V,L,roughNess);
	vec3 kd=F;
	vec3 ks=vec3(1.0)-kd;
	kd*=1.0-metallic;

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
	//HDR变换
	color=color/(vec3(1.0)+color);
	//gamma矫正
	color=pow(color,vec3(1.0/2.2));
	FragColor=vec4(color,1.0);


}

vec3 GetNormal()
{
	//根据TBN将贴图中的东西整出来
	//和手动计算方法不同，主要是用偏导代替了其中的一些计算
	vec3 tangentNormal = texture(texture_normal1, nTexCoord).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(nTexCoord);
    vec2 st2 = dFdy(nTexCoord);

    vec3 N   = normalize(nNormal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
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
