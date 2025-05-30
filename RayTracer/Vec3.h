#pragma once

class vec3
{
public:
	double e[3];

	vec3() 
		:e{0, 0, 0} 
	{
	}

	vec3(double e0, double e1, double e2)
		:e{ e0, e1, e2 }
	{
	}

	double x() const
	{
		return e[0];
	}
	double y() const
	{
		return e[1];
	}
	double z() const
	{
		return e[2];
	}

	vec3 operator -() const
	{
		return vec3(-e[0], -e[1], -e[2]);
	}
	double operator[](int i) const
	{
		return e[i];
	}
	double& operator[](int i)
	{
		return e[i];
	}

	vec3& operator+=(const vec3& v)
	{
		e[0] += v[0];
		e[1] += v[1];
		e[2] += v[2];
		return *this;
	}

	vec3& operator*=(double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(double t)
	{
		return *this *= 1 / t;
	}

	double length() const
	{
		return std::sqrt(lengthSquared());
	}

	double lengthSquared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	bool nearZero() const
	{
		auto s = 1e-8;
		return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
	}

	static vec3 random()
	{
		return vec3(randomDouble(), randomDouble(), randomDouble());
	}

	static vec3 random(double min, double max)
	{
		return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}
};

//alias
using point3 = vec3;

//vector utility functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
inline vec3 operator*(double t, const vec3& v)
{
	return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}
inline vec3 operator*(const vec3& v, double t)
{
	return t * v;
}
inline vec3 operator/(const vec3& v, double t)
{
	return v * (1 / t);
}

inline double dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0] +
		   u.e[1] * v.e[1] +
		   u.e[2] * v.e[2];
}
inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unitVector(const vec3& v)
{
	return v / v.length();
}

inline vec3 randomInUnitDisk()
{
	while (true)
	{
		point3 p = point3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
		if (p.lengthSquared() < 1)
			return p;
	}
}

inline vec3 randomUnitVector()
{
	while (true)
	{
		point3 p = vec3::random(-1, 1);
		double lengthSquared = p.lengthSquared();
		if (1e-160 < lengthSquared && lengthSquared <= 1)
			return p / sqrt(lengthSquared);
	}
}

inline vec3 randomVectorOnHemisphere(const vec3& normal)
{
	vec3 VectorOnUnitSphere = randomUnitVector();
	if (dot(VectorOnUnitSphere, normal) > 0.0)
		return VectorOnUnitSphere;
	else
		return -VectorOnUnitSphere;
}

inline vec3 reflect(const vec3& v, const vec3& normal)
{
	return v - 2 * dot(v, normal) * normal;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etaOverEtaPrime)
{
	auto cosTheta = std::fmin(dot(-uv, n), 1.0);
	vec3 rOutPerpendicular = etaOverEtaPrime * (uv + cosTheta * n);
	vec3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerpendicular.lengthSquared())) * n;
	return rOutPerpendicular + rOutParallel;
}