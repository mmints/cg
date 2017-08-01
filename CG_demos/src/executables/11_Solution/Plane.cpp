#include "Plane.h"

namespace cg
{

Plane::Plane() :
		m_p(0.f,0.f,0.f),m_n(0.f,1.f,0.f)
{


}

Plane::Plane(const glm::vec3& p, const glm::vec3& n) :
		m_p(p),m_n(glm::normalize(n))
{
}


Plane::~Plane()
{

}

bool Plane::intersect(const cg::Ray& r, float& t)
{
	float denom = glm::dot(r.dir, m_n);

	if (std::abs(denom) < 0.00001f)
	{
		return false;
	}

	t = glm::dot(m_p-r.p,m_n)/denom;

	return t >= 0.f;
}


glm::vec3 Plane::calcNormal(const glm::vec3& p)
{
	return m_n;
}

} /* namespace cg */
