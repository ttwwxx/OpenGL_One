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

//窗口设置
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 1024;

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
unsigned int LaodImageToGPU(const char *filename, GLint internalFormat, GLenum format, int textureSlot) {
    unsigned int TexBuffer;
    glGenTextures(1, &TexBuffer);
    glBindTexture(GL_TEXTURE_2D, TexBuffer);

    int width, height, nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);

    if (data)
    {
        glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("load image failed.");
    }
    stbi_image_free(data);
    return TexBuffer;
}
int main()
{
    //glfw初始化和配置
#pragma endregion
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //鼠标设置
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //设置顶点数据：位置，颜色，UV
    float vertices[] = {
    // positions          // normals           // texture coords
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
        LaodImageToGPU("face.png",GL_RGBA, GL_RGBA,0),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        64.0f);
#pragma endregion  

// 定义VAO.VBO
    unsigned int VBO;
    unsigned int VAO;
    //unsigned int EBO;

    
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    /*glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

    ////颜色信息
    //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)) );
    //glEnableVertexAttribArray(3);
    //UV
    //Normal

    unsigned int diffuseMap;
   



    //实例化相机类
        //Camera camera (glm::vec3(0.0f, 0.0f, 3.0f) ,glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    //计算变换矩阵
        glm::mat4 trans;

        glm::mat4 modelMat;
        glm::mat4 viewMat;
        glm::mat4 projMat;

        modelMat = glm::rotate(modelMat,  glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        projMat = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
     //viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
    //trans = glm::scale(trans, glm::vec3(0.5f, 2.0f, 0.2f));


    while (!glfwWindowShouldClose(window))
    {  
        Light myLight(myShader, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10.0f, 10.0f, -5.0f));
        viewMat = camera.GetViewMatrix();
        //trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        ////trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));//3. 最后平移到世界位置
        //trans = glm::rotate(trans, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));//// 2. 然后旋转
        //trans = glm::scale(trans, glm::vec3(2.5f, 1.0f, 1.0f));//// 1. 首先缩放（在局部空间）
        
        processInput(window);

        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        //清除以前的z-buffer，更新
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      
        myShader->setInt("material.diffuse", 0);

    
        // 设置纹理参数
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindVertexArray(VAO);
        /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/

      


        for (int i = 0; i < 10; i++)
        {
            glm::mat4 roop_modelMat = glm::mat4(1.0f);
            roop_modelMat = glm::translate(roop_modelMat, cubePositions[i]);
            myShader->use();
          
            myShader->setMat4("modelMat",roop_modelMat);
            myShader->setMat4("viewMat", viewMat);
            myShader->setMat4("projMat", projMat);
            myShader->setVec3("emission", glm::vec3(1.0f, 0.5f, 0.7f));
            myShader->setVec3("ambientColor", glm::vec3(0.2f, 0.1f, 0.0f));
            myShader->setVec3("light.Position", myLight.Position);
            myShader->setVec3("light.Color", myLight.Color);
            
            myShader->setVec3("material.specular", myMaterial->specular);
            myShader->setInt("material.diffuse", myMaterial->diffuse);
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
 

    glfwTerminate(); 
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}