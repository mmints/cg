#ifndef EXECUTABLES_11_RAYTRACER_LIGHT_H_
#define EXECUTABLES_11_RAYTRACER_LIGHT_H_


#include <glm/glm.hpp>

namespace cg
{

/**
 * Light class
 *
 * pos: The light's position
 * color: The light's color
 * cutoff: The cutoff angle in case of a spotlight
 */
struct Light
{
	glm::vec4 pos;
	glm::vec3 color;
	float cutoff;
};

} /* namespace cg */

#endif /* EXECUTABLES_11_RAYTRACER_LIGHT_H_ */
