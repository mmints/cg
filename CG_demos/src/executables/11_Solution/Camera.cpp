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

	glm::vec3 right = glm::normalize(glm::cross(m_dir,m_up));
	glm::vec3 up = glm::cross(right,m_dir);



	float s = std::tan(m_fov/2.f);
	float sp = s/m_aspect;


	glm::vec3 leftbottom = m_pos + m_dir - s*right - sp*up;

	glm::vec3 p = leftbottom + 2.f*s*u*right + 2.f*sp*v*up;
	return Ray{m_pos, glm::normalize(p-m_pos)};

}

} /* namespace cg */
