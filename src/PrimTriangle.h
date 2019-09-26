// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 * @param color Color of the primitive
	 */
	CPrimTriangle(Vec3f color, Vec3f a, Vec3f b, Vec3f c)
		: CPrim(color)
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool Intersect(Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---
		Vec3f nab = (m_b - ray.org).cross(m_a - ray.org);
		Vec3f nbc = (m_c - ray.org).cross(m_b - ray.org);
		Vec3f nca = (m_a - ray.org).cross(m_c - ray.org);
		
		float sum = nab.dot(ray.dir) + nbc.dot(ray.dir) + nca.dot(ray.dir);
		float l1  = nab.dot(ray.dir) / sum;
		float l2  = nbc.dot(ray.dir) / sum;
		float l3  = nca.dot(ray.dir) / sum;

		if(l1 < 0 || l2 < 0 || l3 < 0) 
			return false;

		Vec3f normal = (m_b - m_a).cross(m_c - m_a);

		float d1 = - normal.dot(ray.org - m_a);
		float d2 = normal.dot(ray.dir);
		float t;

		if(d2 == 0) return false;
		else		t = d1 / d2; 

		if(t < Epsilon || t > ray.t)
			return false;

		ray.t = t;
		return true;
	}

	
private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};
