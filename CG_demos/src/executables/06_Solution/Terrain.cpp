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

	for ( int z = 0; z < m_resolution-1; z++)
	{
		if(!(z % 2))
		{
			for ( int x = 0; x < m_resolution; x++)
			{
				m_vertices.push_back(glm::vec3((float)x/m_resolution, getHeight(x,z),(float)z/m_resolution));
				m_vertices.push_back(glm::vec3((float)x/m_resolution, getHeight(x,z+1),(float)(z+1.0)/m_resolution));

			}
		}else
		{
			for ( int x =  m_resolution-1; x >=0; x--)
			{
				m_vertices.push_back(glm::vec3((float)x/m_resolution, getHeight(x,z),(float)z/m_resolution));
				m_vertices.push_back(glm::vec3((float)x/m_resolution, getHeight(x,z+1),(float)(z+1.0)/m_resolution));


			}
		}
	}


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
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vertices.size());

}

void Terrain::generate(int x1, int z1, int x2, int z2, float interval)
{
	if ((x2 - x1 < 2) && (z2 - z1 < 2)) // stop recursion
	    return;

	/* calculate the value of the squareÕs center point
	 * arithmetic mean of the height at the four corners + random value
	 */
    float centerHeight = ((getHeight(x1,z1) + getHeight(x1,z2) +
                          getHeight(x2,z1) + getHeight(x2,z2)) / 4.0f) +
                          random(interval);
	int midX = (x1 + x2) / 2;
	int midZ = (z1 + z2) / 2;
    setHeight(midX, midZ, centerHeight);

    /* diamond step */
    float edgeHeight = ((getHeight(x1,z1) + getHeight(x1,z2)) / 2.0f) + random(interval);
    setHeight(x1, midZ, edgeHeight);
    edgeHeight = ((getHeight(x2,z1) + getHeight(x2,z2)) / 2.0f) + random(interval);
    setHeight(x2, midZ, edgeHeight);
    edgeHeight = ((getHeight(x1,z1) + getHeight(x2,z1)) / 2.0f) + random(interval);
    setHeight(midX, z1, edgeHeight);
    edgeHeight = ((getHeight(x1,z2) + getHeight(x2,z2)) / 2.0f) + random(interval);
    setHeight(midX, z2, edgeHeight);
    
    /* square step */
	interval /= 2.0f;
	generate(x1, z1, midX, midZ, interval);
	generate(midX, z1, x2, midZ, interval);
	generate(x1, midZ, midX, z2, interval);
	generate(midX, midZ, x2, z2, interval);
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




