#include "Dielectric.h"

#include "Hitable.h"

bool Dielectric::Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double refractionRatio = hitInfo.frontFace ? (1.0 / mRefractiopnIndex) : mRefractiopnIndex;

    Vector3 unitDirection = Unit(rayIn.GetDirection());
    double cosTheta = fmin(Dot(-unitDirection, hitInfo.normal), 1.0);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0;
    Vector3 direction;

    if (cannotRefract || Reflectance(cosTheta,refractionRatio) > RandomDouble() )
        direction = Reflect(unitDirection, hitInfo.normal);
    else
        direction = Refract(unitDirection, hitInfo.normal, refractionRatio);

    scattered = Ray(hitInfo.coordinates, direction);
    return true;
}

double Dielectric::Reflectance(double cosine,double reflectionIndex)
{
    double r0 = (1 - reflectionIndex) / (1 + reflectionIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}