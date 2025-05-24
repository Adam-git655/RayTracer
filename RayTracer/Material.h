#pragma once

#include "Hittable.h"

class material
{
public:
	virtual ~material() = default;

	virtual bool scatter(const ray& rayIn, const hitRecord& rec, color& attenuation, ray& scattered) const
	{
		return false;
	}
};

class lambertian : public material
{
private:
	color albedo;

public:
	lambertian(const color& albedo)
		:albedo(albedo)
	{
	}

	bool scatter(const ray& rayIn, const hitRecord& rec, color& attenuation, ray& scattered) const override
	{
		vec3 scatterDir = rec.normal + randomUnitVector();

		if (scatterDir.nearZero())
			scatterDir = rec.normal;

		scattered = ray(rec.p, scatterDir);
		attenuation = albedo;
		return true;
	}
};

class metal : public material
{
private:
	color albedo;
	double fuzz;
public:
	metal(const color& albedo, double fuzz)
		:albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1)
	{
	}

	bool scatter(const ray& rayIn, const hitRecord& rec, color& attenuation, ray& scattered) const override
	{
		vec3 reflectedVec = reflect(rayIn.direction(), rec.normal);
		reflectedVec = unitVector(reflectedVec) + (fuzz * randomUnitVector());
		scattered = ray(rec.p, reflectedVec);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};

class dielectric : public material
{
private:
	double refractiveIndex;

	static double reflectance(double cosine, double refractiveIndex)
	{
		//Schlicks approximation
		auto r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
		r0 = r0 * r0;
		return r0 + (1 - r0) * std::pow((1 - cosine), 5);
	}

public:

	dielectric(double refractiveIndex)
		: refractiveIndex(refractiveIndex)
	{
	}

	bool scatter(const ray& rayIn, const hitRecord& rec, color& attenuation, ray& scattered) const override
	{
		attenuation = color(1.0, 1.0, 1.0);
		double ri = rec.frontFace ? (1.0 / refractiveIndex) : refractiveIndex;

		vec3 unitDir = unitVector(rayIn.direction());

		double cosTheta = std::fmin(dot(-unitDir, rec.normal), 1.0);
		double sinTheta = std::sqrt(1 - cosTheta * cosTheta);

		bool cannotRefract = ri * sinTheta > 1.0;

		vec3 direction;

		if (cannotRefract || reflectance(cosTheta, ri) > randomDouble())
			direction = reflect(unitDir, rec.normal);
		else
			direction = refract(unitDir, rec.normal, ri);

		scattered = ray(rec.p, direction);
		return true;
	}
};