#ifndef __CG1_TOOLS_CVK_SHADERSET_H
#define __CG1_TOOLS_CVK_SHADERSET_H

#include "CVK_Defs.h"

class CVKShaderSet
{
public:
	CVKShaderSet();
	CVKShaderSet( GLuint shader_mask, const char** ShaderNames);
	~CVKShaderSet();

	void GenerateShaderProgramm( GLuint shader_mask, const char** ShaderNames);
	void UseProgram();
	GLuint getProgramID();

private: 
	void checkShader(GLuint shaderID);
	void checkProgram(GLuint programID);
	void loadShaderSource(GLint shaderID, const char* fileName);

	GLuint m_shader_mask;

protected:
	GLuint m_ProgramID;
};
#endif /*__CG1_TOOLS_CVK_SHADERSET_H*/
