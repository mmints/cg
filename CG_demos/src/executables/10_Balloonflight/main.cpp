#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <CG1_Tools/CVK_ShaderSet.h>
#include <CG1_Tools/CompatibilityTools.h>

#include "Balloon.h"

using namespace glm;

const int width = 800;
const int height = 600;

int main() 
{
    glfwInit();
    CompatibilityTools::useOpenGL33CoreProfile();
    GLFWwindow* window = glfwCreateWindow(width, height, "10_Balloonflight", 0, 0);
    glfwSetWindowPos(window, 600, 50);
    glfwMakeContextCurrent(window);

    //init opengl 3 extensions
    glewInit();
    glClearColor(1, 1, 1, 1);

    //compile a shader program using CG1_Tools/CVK_ShaderSet.cpp
    const char *balloonShadernames[2] = {SHADERS_PATH "/Balloonflight/balloon.vert", SHADERS_PATH "/Balloonflight/balloon.frag"};
    CVKShaderSet balloonShaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, balloonShadernames);
    GLint balloonViewHandle = glGetUniformLocation(balloonShaderProgram.getProgramID(), "viewMatrix");
    GLint balloonProjectionHandle = glGetUniformLocation(balloonShaderProgram.getProgramID(), "projectionMatrix");
    GLint balloonModelHandle = glGetUniformLocation(balloonShaderProgram.getProgramID(), "modelMatrix");
    GLint balloonTextureID = glGetUniformLocation(balloonShaderProgram.getProgramID(), "tex");

    // create balloon
    Balloon* balloon = new Balloon();
    // model matrix terrain
    mat4 balloonModelMatrix;


    //setting up the camera parameters
    mat4 viewMatrix = lookAt(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    mat4 projectionMatrix = perspective(glm::radians(40.0f), (float) width/height, 1.0f, 20.0f);
    mat4 modelMatrix = mat4(1.0f);

    double lastTime = glfwGetTime();
    
    glEnable(GL_DEPTH_TEST);
    // renderloop
    while(!glfwWindowShouldClose(window)) {

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //use the  balloon shader program
        balloonShaderProgram.UseProgram();
        glUniformMatrix4fv(balloonViewHandle, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(balloonProjectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));
        
        // TODO: Replace position
        glm::vec3 balloonPosition = glm::vec3(0.0f ,0.0f, 0.0f);
        
        balloonModelMatrix = glm::translate(mat4(1.0f),balloonPosition);
        balloonModelMatrix = glm::scale(glm::rotate(balloonModelMatrix, 90.0f , glm::vec3(1,0,0)), glm::vec3(0.5,0.5,-0.5));
        glUniformMatrix4fv(balloonModelHandle, 1, GL_FALSE, value_ptr(balloonModelMatrix));
        glUniform1i(balloonTextureID,0);
        balloon->render();

        // show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    delete balloon;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
