#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <CG1_Tools/ShaderTools.h>
#include <CG1_Tools/CompatibilityTools.h>

#include <vector>

const int width = 800;
const int height = 600;


std::vector<glm::vec2> polygon; // Polygon
glm::vec2 quad[] = { //Clipping-Quad
    glm::vec2(-0.5,-0.5),
    glm::vec2(0.5,-0.5),
    glm::vec2(0.5,0.5),
    glm::vec2(-0.5, 0.5)
};

GLuint vertexbuffer[2]; // Buffer-IDs
GLuint vertexarray;

// Polygon an Kante (clipStart, clipEnd) clippen, Originalpunkte ueberschreiben
void clipEdge(glm::vec2 &clipStart, glm::vec2 &clipEnd)
{
    //Output-Polygon
    std::vector<glm::vec2> output;
    
    /* aktuelle Punkte des Polygons an der Kante (clipStart, clipEnd) clippen
     und in output eintragen */
    
    // Update des Polygons mit neuen Eckpunkten
    polygon = output;

}

// Polygon am Clipping Quad clippen
void clipPolygon()
{
    if(polygon.size() >= 3)
    {
        /* Fuer jede Polygonkante die Funktion clipEdge aufrufen */
    }
    
}


// Zeichne das aktuelle Polygon als Linienzug
static void drawPolygon()
{
    if(polygon.size() >= 3)
    {
        /* Das Polygon als Linienzug zeichnen */
    }
}

// Zeichne den Clipping-Quad als Linienzug
static void drawClippingQuad()
{
    // Buffer mit der entsprechenden binden
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
    // Anweisung setzen, wie der aktive Buffer zu interpretieren ist
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    // Gesamten Buffer rendern
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void initBuffers()
{
    // 2 Buffer IDs holen (fuer den Clipping-Quad und das Polygon)
    glGenBuffers(2, &vertexbuffer[0]);
    // Buffer mit der ersten ID binden
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
    // Array mit Eckpunkten dem gerade aktive Buffer zuordnen
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), &quad[0], GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);
    
}

int main() 
{
    glfwInit();
    CompatibilityTools::useOpenGL33CoreProfile();

    GLFWwindow* window = glfwCreateWindow(width, height, "03_PolygonClipping", NULL, NULL);
    glfwSetWindowPos( window, 600, 50);
    glfwMakeContextCurrent(window);

    glewInit();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    ShaderTools::createColorShaderProgram(1.0, 0.0, 0.0);
    
    initBuffers();
    
    // Beispiel Polygon
    polygon.push_back(glm::vec2(0.0, 0.0));
    polygon.push_back(glm::vec2( 0.8, 0.0));
    polygon.push_back(glm::vec2(0.0,  0.8));
    // Clip Polygon am Clipping-Quad
    clipPolygon();
    
    while( !glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        drawPolygon();
        drawClippingQuad();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(2,vertexbuffer);
    glDeleteVertexArrays(1, &vertexarray);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
