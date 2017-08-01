#include <iostream>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <CG1_Tools/CVK_ShaderSet.h>
#include <CG1_Tools/CompatibilityTools.h>

const int width = 800;
const int height = 800;
int lineCount = 26;

void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        lineCount = (lineCount+1)%27;
        std::cout << lineCount << std::endl;
    }
}


int main() 
{
    glfwInit();
    CompatibilityTools::useOpenGL33CoreProfile();
    GLFWwindow* window = glfwCreateWindow(width, height, "05_Das_Haus_Vom_Nikolaus", 0, 0);
    glfwSetWindowPos( window, 600, 50);
    glfwMakeContextCurrent(window);
    glewInit();
    glClearColor(1, 1, 1, 1);

    // set callback-function
    glfwSetMouseButtonCallback(window, mouseCallback);

    //generate a vertex array object (VAO)
    GLuint vertexarray;
    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);

    //generate a vertex buffer object (VBO)
    GLuint vertexBufferHandle;
    glGenBuffers(1, &vertexBufferHandle);

    const float s = 0.2;
    GLfloat vertices[] = {
        -s,-s,s,
        -s,s,s,
        0.0f,2.0f*s,0.0f,
        s,s,s,
        s,-s,s,
        -s,s,s,
        s,s,s,
        -s,-s,s,
        s,-s,s,
        s,s,-s,
        s,s,s,
        s,-s,-s,
        s,-s,s,
        -s,-s,-s,
        -s,s,-s,
        0.0f,2.0f*s,0.0f,
        s,s,-s,
        s,-s,-s,
        -s,s,-s,
        s,s,-s,
        -s,-s,-s,
        s,-s,-s,
        -s,-s,s,
        -s,s,-s,
        -s,s,s,
        -s,-s,-s,
        -s,-s,s
    };
    //bind it and store geometry into the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //compile a shader program using CG1_Tools/CVK_ShaderSet.cpp
    const char *shadernames[2] = {SHADERS_PATH "/Minimal/minimal.vert", SHADERS_PATH "/Minimal/minimal.frag"};
    CVKShaderSet shaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames);

    //use the shader program
    shaderProgram.UseProgram();

    //renderloop
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_LINE_STRIP, 0, lineCount+1);

        //show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up
    glDeleteBuffers(1,&vertexBufferHandle);
    glDeleteVertexArrays(1, &vertexarray);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
