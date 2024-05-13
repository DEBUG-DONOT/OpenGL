#include"skyBox.h"
float SBV[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

float* skyBox::standarVertex = &SBV[0];
//@param box 天空盒数据指针
//@param texturePath 纹理路径
skyBox::skyBox(float* box, std::vector<std::string>& texturePath)
	:texturePath(texturePath)
{
	setup(box);
	texture = new CubeTexture(texturePath);
	//初始化shader
	VertexShader sv("ShaderLib/skyBoxVert.glsl");
	FragmentShader sf("ShaderLib/skyBoxFrag.glsl");
	shader=new Shader(sv, sf); 
}

skyBox::skyBox(std::vector<std::string>& texturePath)
    :texturePath(texturePath)
{
    setup( this->standarVertex);
    texture = new CubeTexture(texturePath);
    //初始化shader
    VertexShader sv("ShaderLib/skyBoxVert.glsl");
    FragmentShader sf("ShaderLib/skyBoxFrag.glsl");
    shader = new Shader(sv, sf);
}

void skyBox::Draw(const Camera& camera)
{
	glDepthFunc(GL_LEQUAL);
	//glDepthMask(GL_FALSE);
	glBindVertexArray(vao);
	shader->Bind();
	shader->UpLoadUniformMat4("SkyBoxProjection", camera.GetProjectionMatrix());
	shader->UpLoadUniformMat4("SkyBoxView", glm::mat4(glm::mat3(camera.GetViewMatrix())));
	glActiveTexture(GL_TEXTURE0);
	texture->BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	//glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}

void skyBox::setup(float* box)
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 108*sizeof(float),box,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);
}
