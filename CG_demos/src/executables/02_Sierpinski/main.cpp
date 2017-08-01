#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <CG1_Tools/ShaderTools.h>
#include <CG1_Tools/CompatibilityTools.h>

// Inkludiere glm
#include <glm/glm.hpp>

// Inkludiere Header für random
#include <cstdlib>

// Inkludiere Header für Zeit Funktion -> Seed für Zufallswerte
#include <time.h>

// Inkludiere Header für vector
#include <vector>

#define WIDTH 800
#define HEIGHT 600

GLFWwindow* window;

// Punkte wie in Aufgabe
// Integer Koordinaten -> ivec statt vec
std::vector<glm::ivec2> points = { glm::ivec2(0, 0), glm::ivec2(WIDTH, 0),
		glm::ivec2(WIDTH / 2, HEIGHT) };

// Aktueller Punkt
glm::ivec2 p = points[0];

// Anzahl von Punkten
const int N = 100000;

void OpenGLInit() {
	GLuint vertexbuffer, vertexarray;

	glGenVertexArrays(1, &vertexarray);
	glBindVertexArray(vertexarray);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void putPixel(int x, int y) {
	float p[2];

	p[0] = -1 + x * 2.0f / (WIDTH);
	p[1] = -1 + y * 2.0f / (HEIGHT);
	glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_POINTS, 0, 1);
}

// Methode, um den nächsten Punkt zu setzen
void nextPoint() {

	// Zufallszahl
	// Einfach rand() % 3 erzeugt Bias in Zufallszahlen
	double r = ((double) rand() / (RAND_MAX));
	glm::ivec2 pi;

	// Teste bereiche und setze Punkt entsprechend
	if (r < 1. / 3.) {
		pi = points[0];
	} else if (r < 2. / 3.) {
		pi = points[1];
	} else {
		pi = points[2];
	}

	p = (p + pi) / 2;

	putPixel(p.x, p.y);
}

int main() {

	// Initialisiere seed
	srand(time(NULL));

	glfwInit();
	CompatibilityTools::useOpenGL33CoreProfile();

	window = glfwCreateWindow(WIDTH, HEIGHT, "02_Sierpinski", 0, 0);
	glfwSetWindowPos(window, 600, 50);
	glfwMakeContextCurrent(window);

	glewInit();
	OpenGLInit();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	ShaderTools::createColorShaderProgram(1.0, 0.0, 0.0);
	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);

		// Zeichne Punkte
		for(int i = 0; i < N; i++)
		{
			nextPoint();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

