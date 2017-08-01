#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <CG1_Tools/CVK_ShaderSet.h>
#include <CG1_Tools/CompatibilityTools.h>

#include "Terrain.h"

using namespace glm;

const int width = 800;
const int height = 600;

int main() 
{
    glfwInit();
    CompatibilityTools::useOpenGL33CoreProfile();
    GLFWwindow* window = glfwCreateWindow(width, height, "06_Terrain", 0, 0);
    glfwSetWindowPos(window, 600, 50);
    glfwMakeContextCurrent(window);


    //init opengl 3 extensions
    glewInit();
    glClearColor(0.7, 0.8, 1, 1);

    //compile a shader program using CG1_Tools/CVK_ShaderSet.cpp
    const char *shadernames[2] = {SHADERS_PATH "/Terrain/terrain.vert", SHADERS_PATH "/Terrain/terrain.frag"};
    CVKShaderSet shaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames);

    GLuint viewHandle = glGetUniformLocation(shaderProgram.getProgramID(), "uniformView");
    GLuint projectionHandle = glGetUniformLocation(shaderProgram.getProgramID(), "uniformProjection");
    GLuint modelHandle = glGetUniformLocation(shaderProgram.getProgramID(), "uniformModel");

    GLuint heightIntervalHandle = glGetUniformLocation(shaderProgram.getProgramID(), "uniformHeightInterval");

    //use the shader program
    shaderProgram.UseProgram();

    // create a terrain
    Terrain terrain(257,0.4);

    mat4 viewMatrix = lookAt(vec3(-0.8, 0.4, 0.5f), vec3(0.8f, 0.5, -0.5f), vec3(0.0f, 1.0f, 0.0f));
    mat4 projectionMatrix = perspective(40.0f, (float) width/height, 0.1f, 50.0f);
    mat4 modelMatrix = mat4(1.0f);
    modelMatrix = translate(modelMatrix, vec3(-0.5,0.0,-0.5));


    //renderloop
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUniformMatrix4fv(viewHandle, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));
        glUniformMatrix4fv(modelHandle, 1, GL_FALSE, value_ptr(modelMatrix));

        glUniform2f(heightIntervalHandle,terrain.getMinHeight(), terrain.getMaxHeight());

        terrain.render();

        //show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
