#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <CG1_Tools/CVK_ShaderSet.h>
#include <CG1_Tools/CompatibilityTools.h>

#include "Teapot.h"

using namespace glm;

const int width = 1024;
const int height = 720;

int main() 
{
    glfwInit();
    CompatibilityTools::useOpenGL33CoreProfile();
    GLFWwindow* window = glfwCreateWindow(width, height, "08_PhongShader", 0, 0);
    glfwSetWindowPos( window, 600, 50);
    glfwMakeContextCurrent(window);


    //init opengl 3 extensions
    glewInit();
    glClearColor(1, 1, 1, 1);


    //compile a shader program using CG1_Tools/CVK_ShaderSet.cpp
    const char *shadernames[2] = {SHADERS_PATH "/Phong/phong.vert", SHADERS_PATH "/Phong/phong.frag"};
    CVKShaderSet shaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames);
    
    GLuint viewMatrixHandle = glGetUniformLocation(shaderProgram.getProgramID(), "viewMatrix");
    GLuint projectionMatrixHandle = glGetUniformLocation(shaderProgram.getProgramID(), "projectionMatrix");
    GLuint modelMatrixHandle = glGetUniformLocation(shaderProgram.getProgramID(), "modelMatrix");
    GLuint lightPositionHandle = glGetUniformLocation(shaderProgram.getProgramID(), "lightPosition");
    
    const char *shadernames2[2] = {SHADERS_PATH "/Blending/blending.vert", SHADERS_PATH "/Blending/blending.frag"};
    CVKShaderSet shaderProgram2(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames2);

    GLuint viewMatrixHandle2 = glGetUniformLocation(shaderProgram2.getProgramID(), "viewMatrix");
    GLuint projectionMatrixHandle2 = glGetUniformLocation(shaderProgram2.getProgramID(), "projectionMatrix");
    GLuint modelMatrixHandle2 = glGetUniformLocation(shaderProgram2.getProgramID(), "modelMatrix");



    //generate a vertex buffer object (VBO) for vertices and normals
    GLuint vertexBufferHandles[2];
    glGenBuffers(2, vertexBufferHandles);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * _points * sizeof(GL_FLOAT), &_v[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * _points * sizeof(GL_FLOAT), &_n[0], GL_STATIC_DRAW);


    // Generate a buffer for the indices as well
    GLuint indexlistHandle;
    glGenBuffers(1, &indexlistHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexlistHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices * sizeof(GL_UNSIGNED_INT), &_index[0] , GL_STATIC_DRAW);


    //generate a vertex array object (VAO) for vertices and normals
    GLuint vertexArrayHandle;
    glGenVertexArrays(1, &vertexArrayHandle);
    glBindVertexArray(vertexArrayHandle);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[0]);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[1]);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //setting up the camera parameters
    mat4 viewMatrix = lookAt(vec3(0.0, 0.0, 5.0f), vec3(0.0f, 0.0, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    mat4 projectionMatrix = perspective(glm::radians(40.0f), (float) width/height, 0.1f, 20.0f);
    mat4 orthoMatrix = ortho(-1, 1, -1, 1, 0, 50);
    mat4 modelMatrix = mat4(1.0f);

    //use the index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexlistHandle);

    //renderloop
    while(!glfwWindowShouldClose(window)) {

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //use the shader program
        shaderProgram.UseProgram();
        
        glUniformMatrix4fv(viewMatrixHandle, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionMatrixHandle, 1, GL_FALSE, value_ptr(projectionMatrix));
        glUniformMatrix4fv(modelMatrixHandle, 1, GL_FALSE, value_ptr(modelMatrix));

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        vec3 lightPos = vec3(xPos / width * 2.0 - 1.0, 1.0 - yPos / height * 2.0, -3.5f);
        glUniform3fv(lightPositionHandle, 1, value_ptr(lightPos));        

        glViewport(0, 0, width, height);
        glDrawElements(GL_TRIANGLES, _indices, GL_UNSIGNED_INT, 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        shaderProgram2.UseProgram();
        glUniformMatrix4fv(viewMatrixHandle2, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionMatrixHandle2, 1, GL_FALSE, value_ptr(orthoMatrix));
        modelMatrix = scale(modelMatrix, vec3(0.5, 0.5, 0.5));
        glUniformMatrix4fv(modelMatrixHandle2, 1, GL_FALSE, value_ptr(modelMatrix));
        glViewport(width/2, height/2, width/3, height/3);
        glDrawElements(GL_TRIANGLES, _indices, GL_UNSIGNED_INT, 0);
        modelMatrix = mat4(1.0f);
        glDisable(GL_BLEND);
        //show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
