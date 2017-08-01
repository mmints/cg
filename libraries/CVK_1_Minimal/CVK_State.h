#ifndef __CVK_STATE_H
#define __CVK_STATE_H

#include "CVK_Defs.h"
#include "CVK_Camera.h"

namespace CVK
{

// forward declaration
class ShaderMinimal;

class State 
{
public:
	static State* getInstance();

	void setShader( CVK::ShaderMinimal* shader);
	CVK::ShaderMinimal* getShader();

	void setCamera( CVK::Camera* camera);
	CVK::Camera* getCamera( );

	void setBackgroundColor(glm::vec3 color);
	glm::vec3 getBackgroundColor();
	
private:
	State();
	~State();

	CVK::ShaderMinimal* m_shader;
	CVK::Camera* m_camera;
	glm::vec3 m_BackgroundColor;
	
	static State* g_instance;
};

};

#endif /* __CVK_STATE_H */

