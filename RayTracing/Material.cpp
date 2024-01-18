#include  "Material.h"
#include "Hitable.h"

bool Lambertian::Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const
{
	Vector3 scatterDirection = hitInfo.normal + RandomUnitVector();

	//Catch invalid direction
	if (scatterDirection.nearZero())
		scatterDirection = hitInfo.normal;

	scattered = Ray(hitInfo.coordinates, scatterDirection);
	attenuation = albedo;
	return true;
}
