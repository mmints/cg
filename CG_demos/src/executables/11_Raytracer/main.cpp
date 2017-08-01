#include <string>
#include <vector>
#include <limits.h>
#include <iostream>

#include "Object.h"
#include "Light.h"
#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"

#include "stb_image_write.h"

using namespace cg;

// HD+		: 1600 x 900
// Full-HD	: 1920 x 1080
// 4K		: 3840 x 2160
// 8K		: 7680 x 4320

const int width = 1920;
const int height = 1080;

const int maxLevel = 5;

glm::vec3 background(0.5, 0.5, 1);

std::vector<uint8_t> data;
std::vector<Geometry*> geometries;
std::vector<Material*> materials;
std::vector<Object*> objects;
std::vector<Light*> lights;

void initData()
{

	// reserve data for image
	data.resize(width * height * 3);
}

void fillObjects()
{
	Material * red = new Material;
	red->diffColor = glm::vec3(1.f, 0.f, 0.f);
	Material * green = new Material;
	green->diffColor = glm::vec3(0.f, 1.f, 0.f);
	Material * blue = new Material;
	blue->diffColor = glm::vec3(0.f, 0.f, 1.f);

	materials.push_back(red);
	materials.push_back(green);
	materials.push_back(blue);

	Geometry * sphere1 = new Sphere(glm::vec3(0.f, 1.f, 0.f));

	geometries.push_back(sphere1);

	Object * o1 = new Object
	{ sphere1, red };
	objects.push_back(o1);

	Geometry * sphere2 = new Sphere(glm::vec3(0, 2, 4), 2);

	geometries.push_back(sphere2);

	Object * o2 = new Object
	{ sphere2, blue };
	objects.push_back(o2);

	Geometry * plane1 = new Plane(glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));
	geometries.push_back(plane1);

	Object * o3 = new Object
	{ plane1, green };
	objects.push_back(o3);

	Geometry * plane2 = new Plane(glm::vec3(-6, 0, 0), glm::vec3(1, 0, 0));
	geometries.push_back(plane2);

	Material * matMirror = new Material();
	matMirror->type = MaterialType::MIRROR;
	matMirror->specColor = glm::vec3(0.6, 0.6, 0.6);
	materials.push_back(matMirror);

	Object * o4 = new Object
	{ plane2, matMirror };
	objects.push_back(o4);

	Geometry * sphere3 = new Sphere(glm::vec3(0, 1.5, -3), 1.5);

	geometries.push_back(sphere3);

	Object * o5 = new Object
	{ sphere3, matMirror };
	objects.push_back(o5);

}

void fillLights()
{
	Light * l1 = new Light
	{ glm::vec4(5, 5, 5, 1), glm::vec3(1, 1, 1), -1 };

	lights.push_back(l1);

	Light * l2 = new Light
	{ glm::vec4(-5, 10, -5, 1), glm::vec3(1, 1, 1), -1 };

	lights.push_back(l2);
}

/**
 * Deletes all objects
 */
void cleanUp()
{

	for (auto & o : objects)
	{
		delete o;
	}

	for (auto & m : materials)
	{
		delete m;
	}

	for (auto & g : geometries)
	{
		delete g;
	}

	for (auto & l : lights)
	{
		delete l;
	}
}

/**
 * Writes pixel data
 */
void putPixel(int x, int y, const glm::vec3 & color)
{
	// flip y since image coordinates start at the top right
	y = height - 1 - y;
	int index = (y * width + x) * 3;

	glm::vec3 clcol = glm::clamp(color * 255.f, 0.f, 255.f);
	data[index] = clcol.x;
	data[index + 1] = clcol.y;
	data[index + 2] = clcol.z;
}

/**
 * Writes the image to disc
 * @param filename The filename
 */
void saveImage(const std::string & filename)
{
	if (stbi_write_png(filename.c_str(), width, height, 3, data.data(), 0) == 0)
	{
		std::cout << "Some error happened" << std::endl;
	}

}

/**
 * Checks, whether the ray intersects an object.
 * Gives information about the closest object
 * @param r The ray
 * @param t Out-parameter. The t-value with which the ray intersects the closest object
 * @param index Out-parameter. The closest intersected object
 * @returns True, if any object was hit, false otherwise
 */
bool intersect(const Ray & r, float & t, int & index)
{

	t = std::numeric_limits<float>::infinity();
	index = -1;
	for (size_t i = 0; i < objects.size(); i++)
	{
		float ttest;
		if (objects[i]->geom->intersect(r, ttest) && ttest < t)
		{

			t = ttest;
			index = i;
		}
	}

	return index >= 0;
}

/**
 * Checks, whether anything was hit in the t-interval [t,maxT]. The closest hit is not required for this test
 * @param r The ray
 * @param maxT The maximum t-value of interest
 * @returns True, if any object was hit, false otherwise
 */
bool hits(const Ray & r, float maxT)
{

	for (size_t i = 0; i < objects.size(); i++)
	{
		float ttest;
		if (objects[i]->geom->intersect(r, ttest) && ttest < maxT)
		{

			return true;
		}
	}

	return false;
}

/**
 * Basic shading
 */
glm::vec3 shade(const Ray & r, const glm::vec3 & p, const glm::vec3 & n,
		Material * mat)
{
	glm::vec3 color(0, 0, 0);
	if (mat->type == MaterialType::DIFFUSE_SPECULAR)
	{
		for (auto & light : lights)
		{
			float length = glm::length(glm::vec3(light->pos) - p);
			glm::vec3 l = glm::normalize(glm::vec3(light->pos) - p);

			Ray lightray
			{ p + n * 0.01f, l };

			if (hits(lightray, length))
			{
				continue;
			}
			color += light->color * mat->diffColor * mat->kd
					* glm::max(0.f, glm::dot(l, n));

			glm::vec3 v = glm::normalize(r.p - p);
			glm::vec3 r = glm::reflect(-l, n);

			float dotvr = glm::max(0.f, glm::dot(v, r));

			color += light->color * mat->specColor * mat->ks
					* glm::pow(dotvr, mat->specExponent);

		}
	}
	else if (mat->type == MaterialType::MIRROR)
	{
		// No direct illumination only perfect reflection
	}

	return color;
}

glm::vec3 trace(const Ray & r, int level)
{

	if (level >= maxLevel)
	{
		return glm::vec3(0, 0, 0);
	}

	int index;
	float t;

	if (intersect(r, t, index))
	{
		Object * o = objects[index];
		glm::vec3 p = r.p + t * r.dir;
		glm::vec3 n = o->geom->calcNormal(p);

		Material * mat = o->mat;

		glm::vec3 color = shade(r, p, n, mat);
		if (mat->type == MaterialType::MIRROR)
		{
			glm::vec3 rdir = glm::reflect(r.dir, n);

			Ray rayReflect
			{ p + 0.01f * n, rdir };

			return color + mat->specColor * trace(rayReflect, level + 1);
		}
		else
		{
			return color;
		}
	}
	else
	{
		return background;
	}

	return glm::vec3(0, 0, 0);

}

int main()
{

	initData();

	fillObjects();
	fillLights();

	Camera cam = Camera();
	cam.setAspect(float(width) / float(height));
	cam.setPosition(glm::vec3(10, 4, 0));
	cam.lookAt(glm::vec3(0, 0, 0));

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{

			Ray r = cam.createRay((x + 0.5f) / width, (y + 0.5f) / height);
			putPixel(x, y, trace(r, 0));
		}

	}

	saveImage("rendering.png");

	cleanUp();

	return 0;
}

