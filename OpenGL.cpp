#include <iostream>
#include"Tool.h"
#include"shader.h"
#include"Texture.h"
#include"Camera.h"
#include<glm/gtc/matrix_transform.hpp>
#include"model.h"

int main()
{
    Initialization::GLFWInitialization();
    GLFWwindow* window = glfwCreateWindow(1600, 900, "LearnOpenGL", NULL, NULL);
    Initialization::GlfwWindowJudge(window);
    glfwMakeContextCurrent(window);
    Initialization::GladInitialization();
    glViewport(0, 0, 1600, 900);
    Camera camera(glm::vec3(0,10,30), glm::vec3(0, 10, 0), glm::vec3(0, 1, 0));
    camera.SetScene(glm::radians(45.0), 16.0 / 9.0, 0.1f, 100.0f);
    Light mLight(glm::vec3(0, 10, 30), glm::vec3(0, 10, 0), glm::vec3(255, 255, 255));
    std::string path = "shenhe/shenhe.pmx";
    std::string path1 = "nanosuit/nanosuit.obj";
    Model model(path);
    Model model1(path1);
    VertexShader v("ShaderLib/BPVertex.glsl");  
    FragmentShader f("ShaderLib/BPFrag.glsl");

    VertexShader v1("ShaderLib/StencilVert.glsl");
    FragmentShader f1("ShaderLib/StencilFrag.glsl");

    Shader s(v, f);
    Shader s1(v1, f1);

    double deltaTime=0, lastFrame=0,currFrame;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glEnable(GL_STENCIL_TEST);
    //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glm::mat4 temp = glm::translate(glm::mat4(1.0), glm::vec3(10, 2, 2));
    while (!glfwWindowShouldClose(window))
    {
        currFrame = glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;
        camera.ProcessInput(window, deltaTime);
        ////////////////////////////////////////////////////
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
        s.Bind();
        s.UpLoadUniformMat4("MVP",camera.GetMVP());
        s.UpLoadUniformMat4("model", camera.GetModelMatrix());
        s.UpLoadUniformFloat3("lightPos", mLight.GetPos());
        s.UpLoadUniformFloat3("viewPos", camera.GetCameraPos());
        //model.Draw(s.GetID());
        model.Draw(s);
        
        s1.Bind();
        s1.UpLoadUniformMat4("model1", temp * camera.GetModelMatrix());
        s1.UpLoadUniformMat4("view1", camera.GetViewMatrix());
        s1.UpLoadUniformMat4("projection1", camera.GetProjectionMatrix());
        //model1.Draw(s1.GetID());
        model1.Draw(s1);
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

