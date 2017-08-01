#ifndef EXECUTABLES_11_RAYTRACER_RAY_H_
#define EXECUTABLES_11_RAYTRACER_RAY_H_

#include <glm/glm.hpp>

namespace cg
{

/**
 * A ray with an origin and direction
 *
 * p: The ray's origin
 * dir: The ray's direction. Should be normalized
 */
struct Ray
{
	glm::vec3 p;
	glm::vec3 dir;
};

} /* namespace cg */

#endif /* EXECUTABLES_11_RAYTRACER_RAY_H_ */
