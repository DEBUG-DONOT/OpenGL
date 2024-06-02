#include <iostream>
#include"Tool.h"
#include"Texture.h"
#include"Camera.h"
#include<glm/gtc/matrix_transform.hpp>
#include"GameObject.h"
#include"Component.h"
#include"model.h"
#include"skyBox.h"

std::vector<std::string> faces
{
    "skybox/right.jpg",
    "skybox/left.jpg",
    "skybox/top.jpg",
    "skybox/bottom.jpg",
    "skybox/front.jpg",
    "skybox/back.jpg"
};
float skyboxVertices[] = {
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
int main()
{
    Initialization::GLFWInitialization();
    auto window = Initialization::CreateWindow(1600, 900, "LG");
    Initialization::GlfwWindowJudge(window);
    glfwMakeContextCurrent(window);
    Initialization::GladInitialization();
    glViewport(0, 0, 1600, 900);
    Camera camera(glm::vec3(0,10,30), glm::vec3(0, 10, 0), glm::vec3(0, 1, 0));
    camera.SetScene(glm::radians(45.0), 16.0 / 9.0, 0.1f, 100.0f);
    Light mLight(glm::vec3(0, 10, 30), glm::vec3(0, 10, 0), glm::vec3(255, 255, 255));

    std::string path = "shenhe/shenhe.pmx";
    std::string path1 = "nanosuit/nanosuit.obj";
    
    //Model model(path);
    GameObject go;
    auto x = go.AddComponent("Model");
    //x不是空指针但是modelComponent是空指针
    //有两种可能，要么是类型不匹配，要么是多态转换失败
    if (auto modelComponent = static_cast<Model*>(x))
    {
        std::cout << "sucess trans" << std::endl;
        if (!modelComponent) std::cout << "nullptr" << std::endl;
        modelComponent->loadModel(path);
    }
    else
    {
        std::cout << "bad cast" << std::endl;
        //throw std::runtime_error("bad cast");
    }
    glEnable(GL_MULTISAMPLE);
    VertexShader v("ShaderLib/BPVertex.glsl");  
    FragmentShader f("ShaderLib/BPFrag.glsl");
    Shader s(v, f);
    skyBox skb(faces);
    double deltaTime=0, lastFrame=0,currFrame;
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    Initialization::GammaCorrectionControl(true);
    //glEnable(GL_STENCIL_TEST);
    //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //glm::mat4 temp = glm::translate(glm::mat4(1.0), glm::vec3(10, 2, 2));
    glm::mat4 temp = glm::scale(glm::mat4(1.0), glm::vec3(1.1, 1, 1));
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
        //model.Draw(s);
        //modelComponent->Draw(s);
        skb.Draw(camera);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

