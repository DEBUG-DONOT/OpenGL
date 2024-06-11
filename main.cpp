#include <iostream>
#include"Tool.h"
#include"ResourseManager/Texture.h"
#include"Camera.h"
#include<glm/gtc/matrix_transform.hpp>
#include"FunctionLayer/GameObject.h"
#include"FunctionLayer/Component.h"
#include"FunctionLayer/Transform.h"
#include"ResourseManager/model.h"
#include"skyBox.h"

std::vector<std::string> faces
{
    "Resourse/skybox/right.jpg",
    "Resourse/skybox/left.jpg",
    "Resourse/skybox/top.jpg",
    "Resourse/skybox/bottom.jpg",
    "Resourse/skybox/front.jpg",
    "Resourse/skybox/back.jpg"
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
    std::string path = "Resourse/shenhe/shenhe.pmx";
    std::string path1 = "Resourse/nanosuit/nanosuit.obj";
    GameObject go;
    auto* x = go.AddComponent<ModelComponent>();
    x->LoadModel(path);
    go.AddComponent<TransformComponent>();
    glEnable(GL_MULTISAMPLE);
    VertexShader v("Resourse/ShaderLib/BPVertex.glsl");  
    FragmentShader f("Resourse/ShaderLib/BPFrag.glsl");
    Shader s(v, f); 
    skyBox skb(faces);
    double deltaTime=0, lastFrame=0,currFrame;
    Initialization::OpenGLInitialization();
    Initialization::GammaCorrectionControl(true);
    glm::mat4 temp = glm::scale(glm::mat4(1.0), glm::vec3(1.1, 1, 1));
    while (!glfwWindowShouldClose(window))
    {
        currFrame = glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;
        camera.ProcessInput(window, deltaTime);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        s.Bind();
        s.UpLoadUniformMat4("MVP",camera.GetMVP());
        s.UpLoadUniformMat4("model", camera.GetModelMatrix());
        s.UpLoadUniformFloat3("lightPos", mLight.GetPos());
        s.UpLoadUniformFloat3("viewPos", camera.GetCameraPos());
        x->Draw(s);
        skb.Draw(camera);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

