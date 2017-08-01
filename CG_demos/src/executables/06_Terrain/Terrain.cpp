#include "Terrain.h"

Terrain::Terrain(int resolution, float interval)
{
	// set member values
	m_interval = interval;
    m_resolution = resolution;

   // initialize the height field
   m_height.resize(resolution*resolution);
   for (int i = 0; i < resolution*resolution; i++)
   {
        m_height[i] = 0.0f;
    }

    // initialize the four corners
   	setHeight(0, 0, random(interval));
  	setHeight(0, resolution-1, random(interval));
  	setHeight(resolution-1, resolution-1, random(interval));
  	setHeight(resolution-1, 0, random(interval));
  	
  	// generate the height field
	generate(0, 0, resolution-1, resolution-1, interval);

	// compute min/max height
	computeMinMaxHeight();

	/*
	 * Fill m_vertices !!!
	 *
	 *
	 *
	 *
	 *
	 *
	 *
	 *
	 */

    //generate a vertex buffer object (VBO)
    GLuint vertexBufferHandle;
	glGenBuffers(1, &vertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

    //generate a vertex array object (VAO)
    GLuint vertexArrayHandle;
    glGenVertexArrays(1, &vertexArrayHandle);

    //specify the vertex data of the bound VBO and store it in the bound VAO
    glBindVertexArray(vertexArrayHandle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


    //unbind the VBO, we don't need it anymore
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

Terrain::~Terrain()
{
}


void Terrain::render()
{
	/*
	 * Render the terrain as triangle strip.
	 */

}

void Terrain::generate(int x1, int z1, int x2, int z2, float interval)
{
	/*
	 * Perform a diamond and square step of "diamond-square" algorithm
	 *
	 *
	 *
	 *
	 *
	 *
	 */
}

void Terrain::computeMinMaxHeight()
{
	// compute min/max height
	m_minHeight = m_interval*2.0;
	m_maxHeight = 0.0;
	for ( int z = 0; z < m_resolution; z++)
	{
		for ( int x = 0; x < m_resolution; x++)
		{
			if ( getHeight(x,z) < m_minHeight)
				m_minHeight = getHeight(x,z);
			if ( getHeight(x,z) > m_maxHeight)
				m_maxHeight = getHeight(x,z);
		}
	}
}

float Terrain::getMinHeight()
{
	return m_minHeight;
}

float Terrain::getMaxHeight()
{
	return m_maxHeight;
}

void Terrain::setHeight(int x, int z, float height)
{
    if (getHeight(x, z) > 0.0f)
    	return;

    m_height[z*m_resolution+x] = height;
}

float Terrain::getHeight(int x, int z)
{

    return m_height[z*m_resolution+x];
}

float Terrain::random(float interval)
{
	return  ((float)rand() / (float)RAND_MAX) * interval;
}




