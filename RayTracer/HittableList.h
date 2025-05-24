#pragma once

#include "Hittable.h"

#include <vector>

class hittableList : public hittable
{
public:
	std::vector<std::shared_ptr<hittable>> objects;

	hittableList()
	{
	}

	hittableList(std::shared_ptr<hittable> object)
	{
		add(object);
	}

	void add(std::shared_ptr<hittable> object)
	{
		objects.push_back(object);
	}

	void clear()
	{
		objects.clear();
	}

	bool hit(const ray& ray, interval ray_t, hitRecord& hitRec) const override
	{
		hitRecord tempRec;
		bool hitAnything = false;
		auto closestSoFar = ray_t.max;

		for (const auto& object : objects)
		{
			if (object->hit(ray, interval(ray_t.min, closestSoFar), tempRec))
			{
				hitAnything = true;
				closestSoFar = tempRec.t;
				hitRec = tempRec;
			}
		}

		return hitAnything;
	}

};
