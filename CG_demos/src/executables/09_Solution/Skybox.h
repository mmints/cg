#ifndef _SKYBOX_H
#define _SKYBOX_H

#include <GL/glew.h>
#include <glm/ext.hpp>

class Skybox {

public:

	/**
	* Constructor
	*/
	Skybox(const float size);

	/**
	* Destructor
	*/
	~Skybox();

	/**
	* Render the skybox.
	*/
	void render();

private:

    GLuint m_vaoHandle; // vao
    GLuint m_vboHandles[2]; // vbo handels (vertices and uv coordinates)
    GLuint m_textureHandle; // texture handle

};

#endif
