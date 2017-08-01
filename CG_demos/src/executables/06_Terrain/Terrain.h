#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cstdlib>

class Terrain {

public:

    /**
    * Constructor
    */
    Terrain(int resolution, float interval);

    /**
    * Destructor
    */
    ~Terrain();

    /**
    * Render the terrain.
    */
    void render();

    /**
    * Returns the minimum height value.
    */
    float getMinHeight();

    /**
    * Returns the maximum height value.
    */
    float getMaxHeight();

private:

    /*
     * Performs a diamond and square step of "diamond-square" algorithm
     */
    void generate(int x1, int z1, int x2, int z2, float interval);

    /*
     * Calculates the minimum and maximum height value.
     */
    void computeMinMaxHeight();

    /**
    * Set value to the height matrix's element.
    */
    void setHeight(int x, int z, float height);

    /**
    * Get value to the height matrix's element.
    */
    float getHeight(int x, int z);

    /**
    * Returns random float between 0 and interval.
    */
    float random(float interval);
    
    int m_resolution; // size of height matrix (should be 2^N+1)
    float m_interval; // height interval [0.0, interval]
    std::vector<float> m_height; // height matrix
    float m_minHeight; // minimum height
    float m_maxHeight; // maximum height
    std::vector< glm::vec3> m_vertices; // vertices

};


#endif

