#pragma once

#include "Vec3.h"

using color = vec3;

inline double linearToGamma(double linearComponenent)
{
	if (linearComponenent > 0)
		return std::sqrt(linearComponenent);

	return 0;
}

void writeColor(std::ostream& out, const color& pixelColor)
{
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	r = linearToGamma(r);
	g = linearToGamma(g);
	b = linearToGamma(b);

	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	out << rbyte << " " << gbyte << " " << bbyte << "\n";
}