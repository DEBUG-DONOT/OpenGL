#include <iostream>
#include<glad/glad.h>//gald放在glfw前面
#include<GLFW/glfw3.h>
#include"Tool.h"
#include"shader.h"
#include"Texture.h"

float vertices[] = 
{
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};
unsigned int indices[] = 
{
    // 注意索引从0开始! 
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形

    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};
void processInput(GLFWwindow* window, float* mixNum);
int main()
{
    Initialization::GLFWInitialization();
    GLFWwindow* window = glfwCreateWindow(1600, 900, "LearnOpenGL", NULL, NULL);
    Initialization::GlfwWindowJudge(window);
    glfwMakeContextCurrent(window);
    Initialization::GladInitialization();
    glViewport(0, 0, 800, 600);

    unsigned int VBO,VAO,EBO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);

    VertexShader v("ShaderLib/BPVertex.glsl");
    FragmentShader f("ShaderLib/BPFrag.glsl");
    Shader s(v, f);
    Texture t("Texture/container.jpg");
    Texture t1("Texture/wall.jpg");
    //渲染循环
    float mixNum = 0.1;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window,&mixNum);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        s.Bind();
        s.UpLoadUniformInt("ourTex", 0);
        s.UpLoadUniformInt("ourTex1", 1);
        s.UpLoadUniformFloat("mixNum", mixNum);
        t.BindTexture();
        t1.BindTexture(1);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window,float* mixNum)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        *mixNum += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (*mixNum >= 1.0f)
            *mixNum = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        *mixNum -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (*mixNum <= 0.0f)
            *mixNum = 0.0f;
    }
}