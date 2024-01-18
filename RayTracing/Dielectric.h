#pragma once
#include "Material.h"
class Dielectric :
    public Material
{
public:
    Dielectric(double refractionIndex) : mRefractiopnIndex(refractionIndex){}

    bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;
    static double Reflectance(double cosine, double reflectionIndex);

private:
    double mRefractiopnIndex;
};

