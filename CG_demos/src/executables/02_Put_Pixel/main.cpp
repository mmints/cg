#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <CG1_Tools/ShaderTools.h>
#include <CG1_Tools/CompatibilityTools.h>

#define WIDTH 800
#define HEIGHT 600

GLFWwindow* window;

void OpenGL_Init()
{
	GLuint vertexbuffer, vertexarray;
    
    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);
    
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void put_pixel( int x, int y) 
{
	float p[2];

	p[0] = -1 + x * 2.0f / (WIDTH);
	p[1] = -1 + y * 2.0f / (HEIGHT);
	glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_POINTS, 0, 1); 
}

int main() 
{
  glfwInit();
  CompatibilityTools::useOpenGL33CoreProfile();
    
  window = glfwCreateWindow(WIDTH, HEIGHT, "02_Put_Pixel", 0, 0);
  glfwSetWindowPos( window, 600, 50);
  glfwMakeContextCurrent(window);

  glewInit();
  OpenGL_Init();

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  ShaderTools::createColorShaderProgram(1.0, 0.0, 0.0);

  while( !glfwWindowShouldClose( window))
  {
	  glClear(GL_COLOR_BUFFER_BIT);

	  put_pixel( 400, 300);
    
	  glfwSwapBuffers( window);
	  glfwPollEvents();
  }
  glfwDestroyWindow( window);
  glfwTerminate();
  return 0;
}

