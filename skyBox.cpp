#include"skyBox.h"

//@param box 天空盒数据指针
//@param texturePath 纹理路径
skyBox::skyBox(float box[], std::vector<std::string>& texturPath)
	:texturPath(texturPath)
{
	setup(box);
	texture = new CubeTexture(texturPath);
}

void skyBox::Draw(const Camera& camera)
{
	if (!InitialShader)
	{
		//初始化shader
		VertexShader v(vertShader);
		FragmentShader f(fragShader);
		shader = new Shader(v, f);
		InitialShader = true;
	}
	glDepthMask(GL_FALSE);
	glBindVertexArray(vao);
	shader->Bind();
	shader->UpLoadUniformMat4("SkyBoxProjection", camera.GetProjectionMatrix());
	shader->UpLoadUniformMat4("SkyBoxView", glm::mat4(glm::mat3(camera.GetViewMatrix())));
	//shader->UpLoadUniformMat4("SkyBoxView", camera.GetViewMatrix());
	glActiveTexture(GL_TEXTURE0);
	texture->BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}

void skyBox::setup(float box[])
{
	
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(box),&box,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);
}
