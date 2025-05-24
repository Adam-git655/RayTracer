#pragma once

#include "Hittable.h"

class sphere : public hittable
{
private:
	point3 center;
	double radius;
	std::shared_ptr<material> mat;
public:
	sphere(const point3& center, double radius, std::shared_ptr<material> mat)
		: center(center), radius(std::fmax(0.0, radius)), mat(mat)
	{
	}

	bool hit(const ray& ray, interval ray_t, hitRecord& hitRec) const override
	{
		vec3 oc = center - ray.origin();
		auto a = ray.direction().lengthSquared();
		auto h = dot(ray.direction(), oc);
		auto c = oc.lengthSquared() - radius * radius;
		auto discriminant = h * h - a * c;

		if (discriminant < 0)
			return false;

		auto sqrtDiscriminant = std::sqrt(discriminant);

		auto root = (h - sqrtDiscriminant) / a;
		if (!ray_t.surrounds(root))
		{
			root = (h + sqrtDiscriminant) / a;

			if (!ray_t.surrounds(root))
				return false;
		}

		hitRec.t = root;
		hitRec.p = ray.at(hitRec.t);
		vec3 outwardNormal = (center - hitRec.p) / radius;
		hitRec.setFaceNormal(ray, outwardNormal);
		hitRec.mat = mat;

		return true;
	}
	
};