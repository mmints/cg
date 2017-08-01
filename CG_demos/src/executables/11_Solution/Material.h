#ifndef EXECUTABLES_11_RAYTRACER_MATERIAL_H_
#define EXECUTABLES_11_RAYTRACER_MATERIAL_H_

#include <glm/glm.hpp>

namespace cg
{
/**
 * Different types of material
 *
 * DIFFUSE_SPECULAR: Both diffuse and specular illumination
 * MIRROR: Only perfect specular reflection
 */
enum class MaterialType
{
	DIFFUSE_SPECULAR, MIRROR
};

/**
 * Material class
 * diffColor: The diffuse reflectance color
 * kd: The diffuse reflactance factor in [0,1]
 * specColor: The specular reflectance color
 * ks: The specular reflectance factor in [0,1]
 * type: The material's type
 *
 */
struct Material
{
	glm::vec3 diffColor;
	float kd;
	glm::vec3 specColor;
	float ks;
	float specExponent;
	MaterialType type;

	/**
	 * Will initialize default values
	 */
	Material();
};

} /* namespace cg */


#endif /* EXECUTABLES_11_RAYTRACER_MATERIAL_H_ */
