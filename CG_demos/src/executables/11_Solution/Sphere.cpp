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
	glm::vec3 L = m_center - r.p;

	float tca = glm::dot(r.dir,L);

	if(tca < 0.f)
	{

		return false;
	}


	float d2 = glm::dot(L,L) - tca*tca;

	if(d2 > m_r*m_r)
		return false;

	float thc = std::sqrt(m_r*m_r - d2);

	t = tca - thc;


	if(t < 0.f)
	{
		t = tca + thc;
	}

	return t >= 0.f;
}

glm::vec3 Sphere::calcNormal(const glm::vec3& p)
{
	return glm::normalize(p - m_center);
}

} /* namespace cg */
