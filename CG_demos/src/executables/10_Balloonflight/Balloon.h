#ifndef _BALLOON_H
#define _BALLOON_H

#include <GL/glew.h>
#include <glm/ext.hpp>

class Balloon {
public:
    Balloon();
    ~Balloon();
    
    void render();
    
private:

    GLuint m_vaoHandle;
    GLuint m_vboHandles[3];
    GLuint m_textureHandle;
    int m_faceCount;
};

#endif
