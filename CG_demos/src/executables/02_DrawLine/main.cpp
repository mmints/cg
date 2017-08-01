#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <CG1_Tools/ShaderTools.h>
#include <CG1_Tools/CompatibilityTools.h>

// Inkludiere glm
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// Inkludiere Mathematik
#include <cmath>

#include <iostream>

#define WIDTH 800
#define HEIGHT 600

GLFWwindow* window;

void OpenGLInit()
{
	GLuint vertexbuffer, vertexarray;

	glGenVertexArrays(1, &vertexarray);
	glBindVertexArray(vertexarray);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}



void putPixel(int x, int y)
{
	float p[2];

	p[0] = -1 + x * 2.0f / (WIDTH);
	p[1] = -1 + y * 2.0f / (HEIGHT);
	glBufferData(GL_ARRAY_BUFFER, sizeof(p), &p, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_POINTS, 0, 1);
}



// Andere Varianten möglich
int determineOctant(const glm::ivec2 & d)
{
	bool upper = d.y >= 0;

	glm::vec2 df(d);

	// normalisiere Vektor für skalarprodukt
	df = glm::normalize(df);

	// Skalarprodukt mit x-Achse = cos(alpha)
	float cosalpha = glm::dot(df, glm::vec2(1.f, 0.f));

	// Acos liefert werde in [0,pi]
	float alpha = std::acos(cosalpha);

	// oberer Halbraum
	if (upper)
	{
		// <= 45° -> Oktant0
		if (alpha <= glm::pi<float>() * 0.25f)
		{
			return 0;
		} // <= 90° -> Oktant1
		else if (alpha <= glm::pi<float>() * 0.5f)
		{
			return 1;
		} // <= 135° -> Oktant2
		else if (alpha <= glm::pi<float>() * 0.75f)
		{
			return 2;
		}
		else
		{
			return 3;
		}
	} // unterer Halbraum
	else
	{
		// <= 45° -> Oktant7
		if (alpha <= glm::pi<float>() * 0.25f)
		{
			return 7;
		} // <= 90° -> Oktant6
		else if (alpha <= glm::pi<float>() * 0.5f)
		{
			return 6;
		} // <= 135° -> Oktant5
		else if (alpha <= glm::pi<float>() * 0.75f)
		{
			return 5;
		}
		else
		{
			return 4;
		}
	}

}

glm::ivec2 toOctant0(const glm::ivec2 & a, int octant)
{

	// Verdrehe Koordinaten und spiegle, sodass sie in Oktant 0 liegen
	if (octant == 0)
	{
		return a;
	}
	else if (octant == 1)
	{
		return glm::ivec2(a.y, a.x);

	}
	else if (octant == 2)
	{
		return glm::ivec2(a.y, -a.x);

	}
	else if (octant == 3)
	{
		return glm::ivec2(-a.x, a.y);

	}
	else if (octant == 4)
	{
		return glm::ivec2(-a.x, -a.y);

	}
	else if (octant == 5)
	{
		return glm::ivec2(-a.y, -a.x);

	}
	else if (octant == 6)
	{
		return glm::ivec2(-a.y, a.x);

	}
	else
	{
		return glm::ivec2(a.x, -a.y);

	}
}



glm::ivec2 fromOctant0(const glm::ivec2 & a, int octant)
{
	// Verdrehe Koordinaten zurück
	if (octant == 0)
	{
		return a;
	}
	else if (octant == 1)
	{
		return glm::ivec2(a.y, a.x);

	}
	else if (octant == 2)
	{
		return glm::ivec2(-a.y, a.x);

	}
	else if (octant == 3)
	{
		return glm::ivec2(-a.x, a.y);

	}
	else if (octant == 4)
	{
		return glm::ivec2(-a.x, -a.y);

	}
	else if (octant == 5)
	{
		return glm::ivec2(-a.y, -a.x);

	}
	else if (octant == 6)
	{
		return glm::ivec2(a.y, -a.x);

	}
	else
	{
		return glm::ivec2(a.x, -a.y);

	}

}

// Algorithmus aus Vorlesung
void drawLine(glm::ivec2 a, glm::ivec2 b)
{

	glm::ivec2 d = b - a;
	// bestimme Oktant von Linie
	int octant = determineOctant(d);

	// Transformiere Punkte in den 0. Oktant, in welchem der DDA nur gilt
	a = toOctant0(a, octant);
	b = toOctant0(b, octant);
	glm::vec2 p;

	float m = float(b.y - a.y) / (b.x - a.x);
	p.y = a.y;

	for (p.x = a.x; p.x < b.x; p.x++)
	{
		// Transformiere Linienpunkt zurück in den ursprünglichen Oktanten
		glm::ivec2 pr = fromOctant0(glm::ivec2(p), octant);

		putPixel(pr.x, pr.y);

		p.y = p.y + m;

	}

}

int main()
{
	glfwInit();
	CompatibilityTools::useOpenGL33CoreProfile();

	window = glfwCreateWindow(WIDTH, HEIGHT, "02_Draw_Line", 0, 0);
	glfwSetWindowPos(window, 600, 50);
	glfwMakeContextCurrent(window);

	glewInit();
	OpenGLInit();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	ShaderTools::createColorShaderProgram(1.0, 0.0, 0.0);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// Linien aus allen 8 Oktanten
		drawLine(glm::ivec2(300, 300), glm::ivec2(500, 400));
		drawLine(glm::ivec2(300, 300), glm::ivec2(400, 500));

		drawLine(glm::ivec2(300, 300), glm::ivec2(200, 500));
		drawLine(glm::ivec2(300, 300), glm::ivec2(100, 400));

		drawLine(glm::ivec2(300, 300), glm::ivec2(100, 200));
		drawLine(glm::ivec2(300, 300), glm::ivec2(200, 100));

		drawLine(glm::ivec2(300, 300), glm::ivec2(400, 100));
		drawLine(glm::ivec2(300, 300), glm::ivec2(500, 200));

		// Achsen
		drawLine(glm::ivec2(300, 300), glm::ivec2(500, 300));
		drawLine(glm::ivec2(300, 300), glm::ivec2(100, 300));
		drawLine(glm::ivec2(300, 300), glm::ivec2(300, 500));
		drawLine(glm::ivec2(300, 300), glm::ivec2(300, 100));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

