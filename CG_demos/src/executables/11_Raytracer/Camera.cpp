#include "Camera.h"
#include <cmath>


namespace cg
{

Camera::Camera() :
		m_pos(0.f,0.f,0.f), m_dir(1.f,0.f,0.f), m_up(0.f,1.f,0.f), m_fov(glm::radians(70.f)), m_aspect(
				1.f)
{

}

Camera::~Camera()
{

}

glm::vec3 Camera::position()
{
	return m_pos;
}

glm::vec3 Camera::direction()
{
	return m_dir;
}

glm::vec3 Camera::up()
{
	return m_up;
}

float Camera::fov()
{
	return m_fov;
}

float Camera::aspect()
{
	return m_aspect;
}

void Camera::setPosition(const glm::vec3& pos)
{
	m_pos = pos;
}

void Camera::setDirection(const glm::vec3& dir)
{
	m_dir = glm::normalize(dir);
}

void Camera::setUp(const glm::vec3& up)
{
	m_up = up;
}

void Camera::setFov(float fov)
{
	m_fov = fov;
}

void Camera::setAspect(float aspect)
{
	m_aspect = aspect;
}

void Camera::lookAt(const glm::vec3& point)
{
	m_dir = glm::normalize(point - m_pos);
}

Ray Camera::createRay(float u, float v)
{

	// TODO
	return Ray{glm::vec3(0,0,0), glm::vec3(1,0,0)};

}

} /* namespace cg */
