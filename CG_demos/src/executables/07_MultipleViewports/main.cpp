#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <iostream>

#include <CG1_Tools/CVK_ShaderSet.h>
#include <CG1_Tools/CompatibilityTools.h>

using namespace glm;

const int width = 600;
const int height = 400;

int main() 
{
    glfwInit();
    CompatibilityTools::useOpenGL33CoreProfile();
    GLFWwindow* window = glfwCreateWindow(width, height, "07_MultipleViewports", 0, 0);
    glfwSetWindowPos( window, 600, 50);
    glfwMakeContextCurrent(window);


    //init opengl 3 extensions
    glewInit();
    glClearColor(1, 1, 1, 1);


    //compile a shader program using CG1_Tools/CVK_ShaderSet.cpp
    const char *shadernames[2] = {SHADERS_PATH "/Position/position.vert", SHADERS_PATH "/Position/position.frag"};
    CVKShaderSet shaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames);
    GLuint modelMatrixHandle = glGetUniformLocation(shaderProgram.getProgramID(), "modelMatrix");
    mat4 modelMatrix = mat4(1.0);
    glUniformMatrix4fv(modelMatrixHandle, 1, GL_FALSE, value_ptr(modelMatrix));


    //generate a vertex buffer object (VBO)
    GLuint vertexBufferHandle;
    glGenBuffers(1, &vertexBufferHandle);


    //bind it and store geometry into the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    const float size = 0.2;
    
	GLfloat vertices[] = {
	        // Front face
	        -size,-size,size, size,-size,size, size,size,size,
	        size,size,size, -size,size,size, -size,-size,size,
	        // Right face
	        size,-size,size, size,-size,-size, size,size,-size,
	        size,size,-size, size,size,size, size,-size,size,
	        // Back face
	        -size,-size,-size, size,-size,-size, size,size,-size,
	        size,size,-size, -size,size,-size, -size,-size,-size,
	        // Left face
	        -size,-size,size, -size,-size,-size, -size,size,-size,
	        -size,size,-size, -size,size,size, -size,-size,size,
	        // Bottom face
	        -size,-size,size, size,-size,size, size,-size,-size,
	        size,-size,-size, -size,-size,-size, -size,-size,size,
	        // Top Face
	        -size,size,size, size,size,size, size,size,-size,
	        size,size,-size, -size,size,-size, -size,size,size,
	};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //generate a vertex array object (VAO)
    GLuint vertexArrayHandle;
    glGenVertexArrays(1, &vertexArrayHandle);


    //specify the vertex data of the bound VBO and store it in the bound VAO
    glBindVertexArray(vertexArrayHandle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //unbind the VBO, we don't need it anymore
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //use the shader program
    shaderProgram.UseProgram();

    //renderloop
    while(!glfwWindowShouldClose(window))
    {

    	glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        //show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
