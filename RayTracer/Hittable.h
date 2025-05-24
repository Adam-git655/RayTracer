#pragma once

class material;

struct hitRecord
{
public:
	point3 p;
	vec3 normal;
	std::shared_ptr<material> mat;
	double t;
	bool frontFace;

	void setFaceNormal(const ray& ray, const vec3& outwardNormal)
	{
		frontFace = dot(ray.direction(), outwardNormal) < 0.0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class hittable
{
public:
	virtual ~hittable() = default;

	virtual bool hit(const ray& ray, interval ray_t, hitRecord& hitRec) const = 0;
};
