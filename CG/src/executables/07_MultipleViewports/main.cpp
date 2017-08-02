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

const int width_half = width/2;
const int height_half = height/2;

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
    GLuint viewMatrixHandle = glGetUniformLocation(shaderProgram.getProgramID(), "viewMatrix");
    GLuint projectMatrixHandle = glGetUniformLocation(shaderProgram.getProgramID(), "projectMatrix");
    
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
    
    double sinus = 0;
    float alfa = 0;
    
    //renderloop
    while(!glfwWindowShouldClose(window))
    {
        sinus += 0.1;
        alfa += 0.01;
        
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mat4 modelMatrix = mat4(1.0);
        mat4 viewMatrix = lookAt(vec3(4.0, 4.0, 6.0f), vec3(0.0, 0.0, 0.0), vec3(0.0f, 1.0f, 0.0f));
        mat4 projectMatrix = perspective(radians(60.0f), width / (float)height, 0.1f, 50.0f);
        
        glUniformMatrix4fv(viewMatrixHandle, 1, GL_FALSE, value_ptr(viewMatrix));
        glUniformMatrix4fv(projectMatrixHandle, 1, GL_FALSE, value_ptr(projectMatrix));
        
        //left
        modelMatrix = translate(modelMatrix, vec3(0, sin(sinus), 0));
        glUniformMatrix4fv(modelMatrixHandle, 1, GL_FALSE, value_ptr(modelMatrix));
        glViewport(0, 0, width_half, height_half);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glViewport(0, height_half, width_half, height_half);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //right
        modelMatrix = rotate(modelMatrix, alfa, vec3(0, 1, 0));
        glUniformMatrix4fv(modelMatrixHandle, 1, GL_FALSE, value_ptr(modelMatrix));
        glViewport(width_half, 0, width_half, height_half);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glViewport(width_half, height_half, width_half, height_half);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        //show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
