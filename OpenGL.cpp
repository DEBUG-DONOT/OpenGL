#include <iostream>
#include"Tool.h"
#include"shader.h"
#include"Texture.h"
#include"Camera.h"
#include<glm/gtc/matrix_transform.hpp>
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
    
    VertexShader v("ShaderLib/BPVertex.glsl");  
    FragmentShader f("ShaderLib/BPFrag.glsl");

    Shader s(v, f);

    skyBox skb(skyboxVertices, faces);
    /*unsigned int skbVAO, skbVBO;
    glGenBuffers(1, &skbVBO);
    glGenVertexArrays(1, &skbVAO);
    glBindVertexArray(skbVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skbVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
    CubeTexture cube(faces);
    VertexShader sv("ShaderLib/skyBoxVert.glsl");
    FragmentShader sf("ShaderLib/skyBoxFrag.glsl");
    Shader skbs(sv,sf);*/



    double deltaTime=0, lastFrame=0,currFrame;
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
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
        skb.Draw(camera);
        
        /*glDepthMask(GL_FALSE);
        glBindVertexArray(skbVAO);
        skbs.Bind();
        skbs.UpLoadUniformMat4("SkyBoxProjection", camera.GetProjectionMatrix());
        skbs.UpLoadUniformMat4("SkyBoxView", glm::mat4(glm::mat3(camera.GetViewMatrix())));
        glActiveTexture(GL_TEXTURE0);
        cube.BindTexture();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthMask(GL_TRUE);*/

        s.Bind();
        s.UpLoadUniformMat4("MVP",camera.GetMVP());
        s.UpLoadUniformMat4("model", camera.GetModelMatrix());
        s.UpLoadUniformFloat3("lightPos", mLight.GetPos());
        s.UpLoadUniformFloat3("viewPos", camera.GetCameraPos());
        //model.Draw(s.GetID());
        model.Draw(s);

      



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

