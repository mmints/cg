#include "Sphere.h"

namespace cg
{

Sphere::Sphere() :
		m_center(0.f, 0.f, 0.f), m_r(1.f)
{
	// TODO Auto-generated constructor stub

}

Sphere::Sphere(const glm::vec3& center) :
		m_center(center), m_r(1.f)
{
}

Sphere::Sphere(const glm::vec3& center, float r) :
		m_center(center), m_r(r)
{
}

Sphere::~Sphere()
{

}

bool Sphere::intersect(const cg::Ray & r, float& t)
{
	// TODO
	return false;
}

glm::vec3 Sphere::calcNormal(const glm::vec3& p)
{
	return glm::normalize(p - m_center);
}

} /* namespace cg */
