#ifndef EXECUTABLES_11_RAYTRACER_PLANE_H_
#define EXECUTABLES_11_RAYTRACER_PLANE_H_

#include "Geometry.h"

namespace cg
{

/**
 * Plane geometry
 * @brief Plane geometry
 */
class Plane: public Geometry
{
public:
	/**
	 * Constructs a default plane at the origin with normal (0,1,0)
	 */
	Plane();

	/**
	 * Constructs a plane with a given point and normal vector
	 * @param p A point in the plane
	 * @param n The plane's normal
	 */
	Plane(const glm::vec3 & p, const glm::vec3 & n);

	virtual ~Plane();


	virtual bool intersect(const cg::Ray & r, float & t) override;

	virtual glm::vec3 calcNormal(const glm::vec3 & p) override;

private:

	glm::vec3 m_n;
	glm::vec3 m_p;
};

} /* namespace cg */

#endif /* EXECUTABLES_11_RAYTRACER_PLANE_H_ */
