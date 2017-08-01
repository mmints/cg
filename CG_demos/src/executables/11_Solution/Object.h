#ifndef EXECUTABLES_11_RAYTRACER_OBJECT_H_
#define EXECUTABLES_11_RAYTRACER_OBJECT_H_

#include "Geometry.h"
#include "Material.h"

namespace cg
{

/**
 * Object in the scene defined by an underlying geometry and a material
 *
 */
struct Object
{
	Geometry * geom;
	Material * mat;

};

} /* namespace cg */

#endif /* EXECUTABLES_11_RAYTRACER_OBJECT_H_ */
