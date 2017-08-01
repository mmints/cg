#include "CVK_State.h"
#include "CVK_ShaderMinimal.h"

CVK::State* CVK::State::g_instance = NULL;

CVK::State::State()
{
	m_camera = 0;
	m_shader = 0;
	m_BackgroundColor = SkyBlue;
}

CVK::State::~State()
{
}

CVK::State* CVK::State::getInstance()
{
	if( g_instance == NULL)
	{	
		g_instance = new CVK::State();
	}
	return g_instance;
}

void CVK::State::setShader( CVK::ShaderMinimal* shader)
{
	m_shader = shader;
	shader->useProgram();
}

CVK::ShaderMinimal* CVK::State::getShader()
{
	return m_shader;
}

void CVK::State::setCamera( CVK::Camera* camera)
{
	m_camera = camera;
}

CVK::Camera* CVK::State::getCamera( )
{
	return m_camera;
}

void CVK::State::setBackgroundColor(glm::vec3 color)
{
	m_BackgroundColor = color;
}

glm::vec3 CVK::State::getBackgroundColor()
{
	return m_BackgroundColor;
}
