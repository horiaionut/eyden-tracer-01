// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 * @param color Color of the primitive
	 */
	CPrimSphere(Vec3f color, Vec3f center, float radius)
		: CPrim(color)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---

		Vec3f v = ray.org - m_center;
		
		float a = ray.dir.dot(ray.dir);
		float b = 2 * ray.dir.dot(v);
		float c = v.dot(v) - m_radius * m_radius;
		float d = b * b - 4 * a * c;

		if(d < 0)	
			return false;

		float t = (-b + sqrt(d)) / a;
		
		if(t < Epsilon || t > ray.t)
			return false;

		ray.t = t;
		return true;
	}
	
	
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

