#pragma once
#include "Ray.h"


class HitInfo;

class Material
{
public:
	~Material() = default;

	virtual bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const = 0;

};

class Lambertian : public Material
{
public:
	Lambertian(const Color& baseColor) : albedo(baseColor) {}

	bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered)
		const override;

private:
	Color albedo;
};