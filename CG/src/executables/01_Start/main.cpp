#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <CG1_Tools/ShaderTools.h>
#include <CG1_Tools/CompatibilityTools.h>

const int width = 800;
const int height = 600;

GLFWwindow* window;

GLfloat vertices[]  =
{ 
    -0.5, -0.5, 
     0.5, -0.5,
     0.0,  0.5,
};

int main() 
{
    //Init Window
    glfwInit();
    CompatibilityTools::useOpenGL33CoreProfile();

    window = glfwCreateWindow(width, height, "01_Start", NULL, NULL);
    glfwSetWindowPos( window, 600, 50);
    glfwMakeContextCurrent(window);

    glewInit();

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    ShaderTools::createColorShaderProgram(1.0, 0.0, 0.0);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertexarray;
    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    while( !glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays( GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}