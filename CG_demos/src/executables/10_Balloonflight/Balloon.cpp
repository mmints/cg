#include "Balloon.h"
#include "BalloonGeo.h"

#include <CG1_Tools/TextureTools.h>

#define BUFFER_OFFSET(x)((char *)NULL+(x))

Balloon::Balloon()
{
		m_faceCount = faces_count[0];

	    glGenVertexArrays(1, &m_vaoHandle);
	    glBindVertexArray(m_vaoHandle);

	    //we generate multiple buffers at a time
	    glGenBuffers(4, m_vboHandles);

	    //bind the first buffer and store geometry into the VBO
	    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[0]);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(struct vertex_struct) * vertex_count[0], vertices, GL_STATIC_DRAW);

	    glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(struct vertex_struct), BUFFER_OFFSET(0));

	    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[1]);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(struct vertex_struct) * vertex_count[0], vertices, GL_STATIC_DRAW);

	    glEnableVertexAttribArray(1);
	    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(struct vertex_struct), BUFFER_OFFSET(3 * sizeof (float)));

	    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandles[2]);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(struct vertex_struct) * vertex_count[0], vertices, GL_STATIC_DRAW);

	    glEnableVertexAttribArray(2);
	    glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, sizeof(struct vertex_struct), BUFFER_OFFSET(6 * sizeof(float)));

	    // uses the last buffer as the source for indices
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboHandles[3]);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (unsigned short) * m_faceCount * 3, indexes, GL_STATIC_DRAW);

	    //unbind the VBO, we don't need it anymore
	    glBindBuffer(GL_ARRAY_BUFFER, 0);

	    // load texture
	    m_textureHandle = TextureTools::loadTexture(RESOURCES_PATH "/balloonTexture.png", true);
}

Balloon::~Balloon()
{
	glDeleteVertexArrays(1, &m_vaoHandle);
	glDeleteBuffers(3, &m_vboHandles[0]);
	glDeleteTextures(1, &m_textureHandle);
}


void Balloon::render()
{    
	glBindVertexArray(m_vaoHandle);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureHandle);
	glDrawElements(GL_TRIANGLES, m_faceCount * 3, GL_UNSIGNED_SHORT,BUFFER_OFFSET(0));
}

