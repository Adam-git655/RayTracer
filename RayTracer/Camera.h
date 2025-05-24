#pragma once

#include "Hittable.h"
#include "Material.h"

class camera
{
public:
	double aspectRatio = 1.0;
	int imageWidth = 100;
	int samplesPerPixel = 10;
	int maxDepth = 10;

	double vfov = 90; // vertical field of view
	point3 lookFrom = point3(0, 0, 0);
	point3 lookAt = point3(0, 0, -1);
	vec3 upVector = vec3(0, 1, 0);

	double defocusAngle = 0; //Variation in angle of rays
	double focusDistance = 10; //Distance from the camera lookFrom point to the plane where we get a perfect focus

	void render(const hittable& world)
	{
		initialize();

		std::cout << "P3\n";
		std::cout << imageWidth << " " << imageHeight << "\n255\n";

		for (int j = 0; j < imageHeight; j++)
		{
			std::clog << "\r Scanlines remaining: " << (imageHeight - j) << " " << std::flush << "\n";
			for (int i = 0; i < imageWidth; i++)
			{
				color pixelColor(0, 0, 0);
				for (int sample = 0; sample < samplesPerPixel; sample++)
				{
					ray r = getRay(i, j);
					pixelColor += rayColor(r, maxDepth, world);
				}
				writeColor(std::cout, pixelSamplesScale * pixelColor);
			}
		}

		std::clog << "\r done. \n";

	}

private:
	int imageHeight;
	double pixelSamplesScale;
	point3 cameraCenter;
	point3 pixel00Location;
	vec3 pixelDelta_u;
	vec3 pixelDelta_v;
	vec3 u, v, w; //Basis vectors from camera frame
	vec3 defocusDisk_u; //Defocus disk horizontal radius
	vec3 defocusDisk_v; //Defocus disk vertical radius

	void initialize()
	{
		imageHeight = int(imageWidth / aspectRatio);
		imageHeight = (imageHeight < 1) ? 1 : imageHeight;

		pixelSamplesScale = 1.0 / samplesPerPixel;

		cameraCenter = lookFrom;

		auto theta = degToRad(vfov);
		auto h = std::tan(theta / 2);
		auto viewportHeight = 2 * h * focusDistance;
		auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

		w = unitVector(lookFrom - lookAt);
		u = unitVector(cross(upVector, w));
		v = cross(w, u);
		
		vec3 viewport_u = viewportWidth * u; //Vector going Left to right across horizontal edge
		vec3 viewport_v = viewportHeight * -v; //Vector going Top to down across vertical edge

		pixelDelta_u = viewport_u / imageWidth;
		pixelDelta_v = viewport_v / imageHeight;

		point3 viewportTopLeft = cameraCenter - (focusDistance * w) - viewport_v / 2 - viewport_u / 2;
		pixel00Location = viewportTopLeft + pixelDelta_u / 2 + pixelDelta_v / 2;

		//Camera defocus disk basis vectors
		auto defocusRadius = focusDistance * std::tan(degToRad(defocusAngle / 2)); // Calculate the radius of the cone created with vetex at pixel and base at disk
		defocusDisk_u = u * defocusRadius;
		defocusDisk_v = v * defocusRadius;
	}

	ray getRay(int i, int j) const
	{
		vec3 offset = sampleSquare();
		point3 pixelSampleLoc = pixel00Location +
								((i + offset.x()) * pixelDelta_u) +
								((j + offset.y()) * pixelDelta_v);
		point3 rayOrigin = (defocusAngle <= 0) ? cameraCenter : defocusDiskSample();
		vec3 rayDirection = pixelSampleLoc - rayOrigin;

		return ray(rayOrigin, rayDirection);
	}

	vec3 sampleSquare() const
	{
		return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
	}

	point3 defocusDiskSample() const
	{
		point3 p = randomInUnitDisk();
		return cameraCenter + (p[0] * defocusDisk_u) + (p[1] * defocusDisk_v);
	}

	color rayColor(const ray& r, int depth, const hittable& world)
	{
		if (depth <= 0)
			return color(0, 0, 0);

		hitRecord rec;
		if (world.hit(r, interval(0.001, infinity), rec))
		{
			ray scattered;
			color attenuation;
			if (rec.mat->scatter(r, rec, attenuation, scattered))
				return attenuation * rayColor(scattered, depth - 1, world);
			return color(0, 0, 0);
		}

		vec3 unitDir = unitVector(r.direction());
		auto a = 0.5 * (unitDir.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}

};