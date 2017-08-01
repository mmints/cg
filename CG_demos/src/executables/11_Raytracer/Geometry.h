#ifndef EXECUTABLES_11_RAYTRACER_GEOMETRY_H_
#define EXECUTABLES_11_RAYTRACER_GEOMETRY_H_

#include <glm/glm.hpp>

#include "Ray.h"

namespace cg
{

/**
 * Abstract Geometry base class. Other geometries should derive from it
 * @brief Abstract geometry base class
 *
 */
struct Geometry
{
	virtual ~Geometry()
	{
	}

	/**
	 * Intersect method. Will intersect the given ray with the geometry
	 * @param r The ray
	 * @param t Out-parameter. If an intersection occurred, this should store the ray's parameter for that point
	 * @return True, if an intersection occurred, false otherwise
	 *
	 */
	virtual bool intersect(const Ray & r, float & t) = 0;

	/**
	 * Method for calculating the normal at a given point
	 * @param p The point at which the normal should be calculated
	 * @return The normalized normal at the point p
	 */
	virtual glm::vec3 calcNormal(const glm::vec3 & p) = 0;
};

} /* namespace cg */

#endif /* EXECUTABLES_11_RAYTRACER_GEOMETRY_H_ */
