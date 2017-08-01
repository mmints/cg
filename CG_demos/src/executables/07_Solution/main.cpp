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
    const char *shadernames[2] = {SHADERS_PATH "/07_Solution/position.vert", SHADERS_PATH "/07_Solution/position.frag"};
    CVKShaderSet shaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames);

    GLint projectionMatrixHandle = glGetUniformLocation(shaderProgram.getProgramID(), "projectionMatrix");
    GLint viewMatrixHandle = glGetUniformLocation(shaderProgram.getProgramID(), "viewMatrix");
    GLint modelMatrixHandle = glGetUniformLocation(shaderProgram.getProgramID(), "modelMatrix");


    //generate a vertex buffer object (VBO)
    GLuint vertexBufferHandle;
    glGenBuffers(1, &vertexBufferHandle);


    //bind it and store geometry into the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    const float size = 1.0;
    
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

    //setting up the camera parameters
    mat4 viewMatrix, modelMatrix;
    mat4 projectionMatrix = perspective(glm::radians(60.0f),  width/ (float) height, 0.01f, 50.0f);
    glUniformMatrix4fv(projectionMatrixHandle, 1, GL_FALSE, value_ptr(projectionMatrix));

    //renderloop
    float trans = 0.0f;
    float angle = 0.0f;

    while(!glfwWindowShouldClose(window))
    {

    	glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // modelmatrix (left)
       // trans+=0.1;
        modelMatrix = glm::translate(mat4(1.0f),vec3(0,sin(trans),0));
        glUniformMatrix4fv(modelMatrixHandle, 1, GL_FALSE, value_ptr(modelMatrix));

        // viewmatrix (left)
        viewMatrix = lookAt(vec3(4.0, 4.0, -6.0f), vec3(0.0f, 0.0, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(viewMatrixHandle, 1, GL_FALSE, value_ptr(viewMatrix));

        glViewport(0,height/2,width/2, height/2);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glViewport(0,0,width/2, height/2);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // modelmatrix (right)
        angle += 0.001f;
        modelMatrix = glm::rotate(mat4(1.0),angle, vec3(0,1,0));
        modelMatrix = glm::translate(modelMatrix,vec3(0,sin(trans),0));
        glUniformMatrix4fv(modelMatrixHandle, 1, GL_FALSE, value_ptr(modelMatrix));

        // viewmatrix (right)
        viewMatrix = lookAt(vec3(-4.0, -4.0, 6.0f), vec3(0.0f, 0.0, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(viewMatrixHandle, 1, GL_FALSE, value_ptr(viewMatrix));

        glViewport(width/2,height/2,width/2, height/2);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glViewport(width/2,0,width/2, height/2);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
