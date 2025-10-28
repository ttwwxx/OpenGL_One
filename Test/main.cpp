#include <glad/glad.h>      
#include <GLFW/glfw3.h>    

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>         
#include"Shader.h"
#include"Material.h"
#include"Camera.h"
#include"Light.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 1024;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 2) in vec3 aPos;\n"
"layout (location = 3) in vec3 aColor;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"       vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);\n"
"}\n\0";


const char* fragmentShaderSource = 
"#version 330 core\n"
"in vec4 vertexColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vertexColor;\n"
"}\n\0";

float lastX = 512;
float lastY = 512;
bool firstMouse = true;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(-10.0f), glm::radians(15.0f), glm::vec3(0, 1.0f, 0.0f));


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    //z
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
    {
        camera.speedZ = 0.5f;

    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.speedZ = -0.5f;
    }
    else {
        camera.speedZ = 0.0f;
}
    //X
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.speedX = -0.5f;

    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.speedX = 0.5f;
    }
    else {
        camera.speedX = 0.0f;
    }
    //X
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.speedY = -0.5f;

    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.speedY = 0.5f;
    }
    else {
        camera.speedY = 0.0f;
    }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{

    if (firstMouse == true)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float deltaX, deltaY;
    deltaX = xPos - lastX;
    deltaY = yPos - lastY;

    lastX = xPos;
    lastY = yPos;
   /* printf("%f\n", deltaX);*/

    camera.ProcessMouseMovement(deltaX, deltaY);
}
int main()
{

#pragma endregion
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// 鼠标设置
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
 
    float vertices[] = {
        ////---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        // 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        // 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        //-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        //-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
        /* -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        * 
            顶点                   UV
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f*/
        //顶点位置            法线
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };


    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    //开启z-buffer
    glEnable(GL_DEPTH_TEST);
#pragma region Init Shader Program
    Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
#pragma endregion
#pragma region Init Material
    Material* myMaterial = new Material(myShader,
        glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0f, 0.5f, 0.31f),
        32.0f);
#pragma endregion  
 Light myLight(myShader, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.2f, 1.0f, 2.0f));
    
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    ////颜色信息
    //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)) );
    //glEnableVertexAttribArray(3);

    /*glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(4);*/

    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(5);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    unsigned int TexBufferA;
    glGenTextures(1, &TexBufferA);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TexBufferA);

    //上下颠倒：stb读取数据是（0，0）左上开始，opengl坐标是左下（0，0）
    stbi_set_flip_vertically_on_load(true);
    
    int width, height, nrChannel;
    unsigned char* data = stbi_load("pic.jpg", &width, &height, &nrChannel, 0);

    if (data)
    {
        glad_glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB,width , height, 0, GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
         printf("load image failed.");
    }
    stbi_image_free(data);

    unsigned int TexBufferB;
    glGenTextures(1, &TexBufferB);
    glActiveTexture(GL_TEXTURE1);//填充槽位
    glBindTexture(GL_TEXTURE_2D, TexBufferB);
    unsigned char* data2 = stbi_load("face.png", &width, &height, &nrChannel, 0);
    if (data2)
    {
        glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("load image failed.");
    }
    stbi_image_free(data2);

    //实例化相机类
        //Camera camera (glm::vec3(0.0f, 0.0f, 3.0f) ,glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    //计算变换矩阵
        glm::mat4 trans;

        glm::mat4 modelMat;
        glm::mat4 viewMat;
        glm::mat4 projMat;

        modelMat = glm::rotate(modelMat,  glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        projMat = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 100.0f);
     //viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
    //trans = glm::scale(trans, glm::vec3(0.5f, 2.0f, 0.2f));


    while (!glfwWindowShouldClose(window))
    {  
        
        viewMat = camera.GetViewMatrix();
        //trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        ////trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));//3. 最后平移到世界位置
        //trans = glm::rotate(trans, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));//// 2. 然后旋转
        //trans = glm::scale(trans, glm::vec3(2.5f, 1.0f, 1.0f));//// 1. 首先缩放（在局部空间）
        
        processInput(window);

        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        //清除以前的z-buffer，更新
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBufferA);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, TexBufferB);

        glBindVertexArray(VAO);
        /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);


        for (int i = 0; i < 10; i++)
        {
            glm::mat4 roop_modelMat = glm::mat4(1.0f);
            roop_modelMat = glm::translate(roop_modelMat, cubePositions[i]);
            myShader->use();
           /* glUniform1i(glGetUniformLocation(myShader->ID, "mainTexture"), 0);
            glUniform1i(glGetUniformLocation(myShader->ID, "mixTexture"), 1);*/
            //glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "transform"), 1, GL_FALSE,glm::value_ptr(trans) );
            /*glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(roop_modelMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
            glUniform3f(glGetUniformLocation(myShader->ID, "emission"), 0.2f, 0.5f, 0.21f);
            glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.5f, 0.3f, 1.0f);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPos"), 2.0f, 2.0f, 2.0f);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"), 1.0f, 1.0f, 1.0f);
            glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);*/
            //float offset = 0.5f;
            //myShader->setFloat("xOffset", offset);

            myShader->setMat4("modelMat",roop_modelMat);
            myShader->setMat4("viewMat", viewMat);
            myShader->setMat4("projMat", projMat);
            myShader->setVec3("emission", glm::vec3(1.0f, 0.5f, 0.7f));
            myShader->setVec3("ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
            myShader->setVec3("lightPos", myLight.Position);
            myShader->setVec3("lightColor", myLight.Color);
            
            
            myShader->setVec3("material.ambient", myMaterial->ambient);
            myShader->setVec3("material.specular", myMaterial->specular);
            myShader->setVec3("material.diffuse", myMaterial->diffuse);
            myShader->setFloat("material.shininess", myMaterial->shininess);
            myShader->setVec3("cameraPos", camera.Position);



            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
       
      /*  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera.UpdateCameraPosition();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate(); 
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}