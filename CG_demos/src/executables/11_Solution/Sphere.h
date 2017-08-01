#ifndef EXECUTABLES_11_RAYTRACER_SPHERE_H_
#define EXECUTABLES_11_RAYTRACER_SPHERE_H_

#include "Geometry.h"

namespace cg
{

/**
 * Sphere geometry
 * @brief Sphere geometry
 */
class Sphere: public Geometry
{
public:

	/**
	 * Constructs a basic sphere at the origin with radius 1
	 */
	Sphere();
	/**
	 * Constructs a sphere at the given center point with radius 1
	 * @param center The sphere's center-point
	 */
	Sphere(const glm::vec3 & center);

	/**
	 * Constructs a sphere with the given parameters
	 * @paramm center The sphere's center-point
	 * @param r The sphere's radius
	 */
	Sphere(const glm::vec3 & center, float r);

	virtual ~Sphere();


	virtual bool intersect(const cg::Ray & r, float & t) override;

	virtual glm::vec3 calcNormal(const glm::vec3 & p) override;
private:

	glm::vec3 m_center;
	float m_r;
};

} /* namespace cg */

#endif /* EXECUTABLES_11_RAYTRACER_SPHERE_H_ */
