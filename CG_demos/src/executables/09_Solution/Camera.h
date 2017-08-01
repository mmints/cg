#ifndef _CAMERA_H
#define _CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

class Camera
{
public:

	/**
	* Constructor
	*/
	Camera(int width, int height);

	/**
	* Destructor
	*/
	~Camera();

	/**
	* Update the position and view.
	*/
	void update(GLFWwindow* window);

	/**
	* Returns the view matrix.
	*/
	void getView(glm::mat4 *view);

	/**
	* Returns the model matrix.
	*/
	void getPerspective(glm::mat4 *perspective);

	/**
	* Sets the near and far value.
	*/
	void setNearFar( float near, float far);

private:

	float m_fov; // field of view
	float m_znear, m_zfar; // near and far value
	int m_width, m_height;	 // window width and height

	glm::mat4 m_viewmatrix; // view matrix
	glm::mat4 m_perspective; // perspective matrix

	glm::vec3 m_camerapos; // position
	glm::vec3 m_direction; // view direction
	glm::vec3 m_up; // up vector

	int m_oldX, m_oldY; // last mouse coordinates
	float m_speed, m_sensitivity; // speed and sensitivity
	float m_theta, m_phi; // angles
};

#endif
