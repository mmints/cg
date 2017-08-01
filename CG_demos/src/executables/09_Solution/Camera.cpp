#include "Camera.h"

Camera::Camera( int width, int height)
{
	m_camerapos = glm::vec3(0.0f, 0.3f, 0.0f);
	m_direction = glm::vec3( 0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_width = width;
	m_height = height;

	m_fov = glm::radians(60.0f);
	m_znear = 0.00001f;
	m_zfar = 100.0f;

	m_speed = 0.0f;
	m_sensitivity = 0.01f;
	m_theta = glm::pi<float>() / 2.0f;
	m_phi = -glm::pi<float>() / 2.0f;

	m_viewmatrix = glm::lookAt( m_camerapos, m_camerapos + m_direction, m_up);   
	m_perspective = glm::perspective( m_fov, m_width / (float) m_height, m_znear, m_zfar);    
 
	m_oldX = width/2;
	m_oldY = height/2;
}

Camera::~Camera()
{
}

void Camera::update( GLFWwindow* window)
{
	double x, y;

	glfwGetCursorPos( window, &x, &y);  
	if (glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{	
		float changeX = (x - m_oldX) * m_sensitivity;
		float changeY = (y - m_oldY) * m_sensitivity;

		m_theta -= changeY;
		if (m_theta < 0.01f) m_theta = 0.01f;
		else if (m_theta > glm::pi<float>() - 0.01f) m_theta = glm::pi<float>() - 0.01f;

		m_phi += changeX;	
		if (m_phi < 0) m_phi += 2*glm::pi<float>();
		else if (m_phi > 2*glm::pi<float>()) m_phi -= 2*glm::pi<float>();

		m_oldX = x;
		m_oldY = y;

		m_direction.x = sin(m_theta) * cos(m_phi);
		m_direction.y = cos(m_theta);
		m_direction.z = sin(m_theta) * sin(m_phi);

	}
	else
	{
		m_oldX = x;
		m_oldY = y;
	}

	if (glfwGetKey( window, GLFW_KEY_UP) == GLFW_PRESS)            
		m_speed += 0.00001f;
	if (glfwGetKey( window, GLFW_KEY_DOWN) == GLFW_PRESS) 
		m_speed -= 0.00001f;
	if (glfwGetKey(window, ' ') == GLFW_PRESS)            
		m_speed = 0.0f;

	m_camerapos += m_speed * m_direction;
	m_viewmatrix = glm::lookAt( m_camerapos, m_camerapos + m_direction, m_up);  
}

void Camera::getView( glm::mat4 *view)
{
	*view = m_viewmatrix;
}

void Camera::getPerspective( glm::mat4 *perspective)
{
	*perspective = m_perspective;
}

void Camera::setNearFar( float near, float far)
{
	m_znear = near;
	m_zfar = far;
	m_perspective = glm::perspective( m_fov, m_width / (float) m_height, m_znear, m_zfar);
}
