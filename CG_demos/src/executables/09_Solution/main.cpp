#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <CG1_Tools/CVK_ShaderSet.h>
#include <CG1_Tools/CompatibilityTools.h>

#include "Terrain.h"
#include "Skybox.h"
#include "Camera.h"

using namespace glm;

const int width = 800;
const int height = 600;


int main() 
{
    glfwInit();
    CompatibilityTools::useOpenGL33CoreProfile();
    GLFWwindow* window = glfwCreateWindow(width, height, "09_TerrainSky", 0, 0);
    glfwSetWindowPos(window, 600, 50);
    glfwMakeContextCurrent(window);

    //init opengl 3 extensions
    glewInit();
    glClearColor(1, 1, 1, 1);

    //compile a shader program using CG1_Tools/CVK_ShaderSet.cpp
    const char *terrainShadernames[2] = {SHADERS_PATH "/09_Solution/terrain.vert", SHADERS_PATH "/09_Solution/terrain.frag"};
    CVKShaderSet terrainShaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, terrainShadernames);
    GLuint terrainViewHandle = glGetUniformLocation(terrainShaderProgram.getProgramID(), "viewMatrix");
    GLuint terrainProjectionHandle = glGetUniformLocation(terrainShaderProgram.getProgramID(), "projectionMatrix");
    GLuint terrainModelHandle = glGetUniformLocation(terrainShaderProgram.getProgramID(), "modelMatrix");
    GLuint terrainHeightIntervalHandle = glGetUniformLocation(terrainShaderProgram.getProgramID(), "heightInterval");

    //compile a shader program using CG1_Tools/CVK_ShaderSet.cpp
    const char *skyboxShadernames[2] = {SHADERS_PATH "/09_Solution/skybox.vert", SHADERS_PATH "/09_Solution/skybox.frag"};
    CVKShaderSet skyboxShaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, skyboxShadernames);
    GLuint skyboxViewHandle = glGetUniformLocation(skyboxShaderProgram.getProgramID(), "viewMatrix");
    GLuint skyboxProjectionHandle = glGetUniformLocation(skyboxShaderProgram.getProgramID(), "projectionMatrix");

    // create a terrain
    Terrain* terrain = new Terrain(257,0.2);
    // model matrix terrain
    mat4 modelMatrix = translate(mat4(1.0f), vec3(-0.5,0.0,-0.5));

    // create skybox
    Skybox* skybox = new Skybox(15.0f);

    // setting up the camera parameters
    Camera* camera = new Camera(width,height);
    mat4 viewMatrix, projectionMatrix;

    glEnable(GL_DEPTH_TEST);
    // renderloop
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // update camera and get view and projection matrix
        camera->update(window);
        camera->getView(&viewMatrix);
        camera->getPerspective(&projectionMatrix);

        //use the skybox shader program
        skyboxShaderProgram.UseProgram();
        glUniformMatrix4fv(skyboxViewHandle, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(skyboxProjectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));
        skybox->render();

        //use the  terrain shader program
        terrainShaderProgram.UseProgram();
        glUniformMatrix4fv(terrainViewHandle, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(terrainProjectionHandle, 1, GL_FALSE, value_ptr(projectionMatrix));
        glUniformMatrix4fv(terrainModelHandle, 1, GL_FALSE, value_ptr(modelMatrix));
        glUniform2f(terrainHeightIntervalHandle,terrain->getMinHeight(), terrain->getMaxHeight());
        terrain->render();

        // show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    delete skybox;
    delete terrain;
    delete camera;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
