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
    Camera camera(glm::vec3(0, 10,30), glm::vec3(0, 10, 0), glm::vec3(0, 1, 0));
    camera.SetScene(glm::radians(45.0), 16.0 / 9.0, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);
    Light mLight(glm::vec3(0, 10, 30), glm::vec3(0, 10, 0), glm::vec3(255, 255, 255));
    std::string path = "shenhe/shenhe.pmx";
    Model model(path);
    VertexShader v("ShaderLib/BPVertex.glsl");  
    FragmentShader f("ShaderLib/BPFrag.glsl");
    Shader s(v, f);
    double deltaTime=0, lastFrame=0,currFrame;
    while (!glfwWindowShouldClose(window))
    {
        currFrame = glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;
        camera.ProcessInput(window, deltaTime);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        s.Bind();
        s.UpLoadUniformMat4("MVP",camera.GetMVP());
        s.UpLoadUniformMat4("model", camera.GetModelMatrix());
        s.UpLoadUniformFloat3("lightPos", mLight.GetPos());
        s.UpLoadUniformFloat3("viewPos", camera.GetCameraPos());
        model.Draw(s);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

