#include "Material.h"

namespace cg
{

Material::Material() :
		diffColor(1.f, 1.f, 1.f), kd(0.9f), specColor(1.f, 1.f, 1.f), ks(0.9f), specExponent(
				10.f), type(MaterialType::DIFFUSE_SPECULAR)
{

}

} /* namespace cg */

