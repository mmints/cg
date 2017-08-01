#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <CG1_Tools/CVK_ShaderSet.h>
#include <CG1_Tools/CompatibilityTools.h>

const int width = 800;
const int height = 600;

GLFWwindow* window;

int main() 
{
    glfwInit();
    CompatibilityTools::useOpenGL33CoreProfile();
    window = glfwCreateWindow(width, height, "04_SimpleShader", 0, 0);
    glfwSetWindowPos( window, 600, 50);
    glfwMakeContextCurrent(window);


    //init opengl 3 extensions
    glewInit();
    glClearColor(1, 1, 1, 1);


    //compile a shader program using CG1_Tools/CVK_ShaderSet.cpp
    const char *shadernames[2] = {SHADERS_PATH "/04_Solution/minimal.vert", SHADERS_PATH "/04_Solution/minimal.frag"};
    CVKShaderSet shaderProgram(VERTEX_SHADER_BIT | FRAGMENT_SHADER_BIT, shadernames);
    GLuint mousePositionHandle = glGetUniformLocation(shaderProgram.getProgramID(), "mousePosition");


    //generate a vertex buffer object (VBO)
    GLuint vertexBufferHandle;
    glGenBuffers(1, &vertexBufferHandle);


    //bind it and store geometry into the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    GLfloat vertices[]  = { -0.4, -0.4,  -0.4, 0.4,  0.4, -0.4,  0.4, 0.4 };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    //generate a vertex array object (VAO)
    GLuint vertexArrayHandle;
    glGenVertexArrays(1, &vertexArrayHandle);


    //specify the vertex data of the bound VBO and store it in the bound VAO
    glBindVertexArray(vertexArrayHandle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


    //unbind the VBO, we don't need it anymore
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //use the shader program
    shaderProgram.UseProgram();


    //renderloop
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //use the shader program
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        glUniform2f(mousePositionHandle, xPos, yPos);

        //draw
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        //show what's been drawn
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
