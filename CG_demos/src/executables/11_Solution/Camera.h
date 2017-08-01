#ifndef EXECUTABLES_11_RAYTRACER_CAMERA_H_
#define EXECUTABLES_11_RAYTRACER_CAMERA_H_

#include "Ray.h"

namespace cg
{

/**
 * Basic camera class
 * @brief Basic camera class
 */
class Camera
{
public:
	/**
	 * Sets initial values. Position at the origin, direction along the x-axis and a fov of 70°
	 */
	Camera();
	virtual ~Camera();

	/**
	 * Getter for position
	 * @return The position
	 */
	glm::vec3 position();
	/**
	 * Getter for direction
	 * @return The direction
	 */
	glm::vec3 direction();
	/**
	 * Getter for up-vector
	 * @return The up-vector
	 */
	glm::vec3 up();

	/**
	 * Getter for field of vision (fov)
	 * @return The field of vision
	 */
	float fov();

	/**
	 * Getter for aspect ratio
	 * @return The aspect ratio
	 */
	float aspect();

	/**
	 * Setter for position
	 * @param pos The new position
	 */
	void setPosition(const glm::vec3 & pos);
	/**
	 * Setter for direction. Will be renormalized
	 * @param dir The new direction
	 */
	void setDirection(const glm::vec3 & dir);
	/**
	 * Setter for up-vector
	 * @param up The new up-vector
	 */
	void setUp(const glm::vec3 & up);

	/**
	 * Setter for field of vision (fov)
	 * @param fov The new fov
	 */
	void setFov(float fov);
	/**
	 * Setter for aspect ratio
	 * @param pos The new aspect ratio
	 */
	void setAspect(float aspect);

	/**
	 * Computes a new direction based on the current position and the point given
	 * @param point The point to be looked at
	 */
	void lookAt(const glm::vec3 & point);

	/**
	 * Creates a ray from the camera's center to the point on the virtual screen given by (u,v)-coordinates
	 * @param u The first parameter in [0,1]
	 * @param v The second parameter in [0,1]
	 */
	Ray createRay(float u, float v);

private:

	glm::vec3 m_pos;
	glm::vec3 m_dir;
	glm::vec3 m_up;

	float m_fov;
	float m_aspect;

};

} /* namespace cg */

#endif /* EXECUTABLES_11_RAYTRACER_CAMERA_H_ */
