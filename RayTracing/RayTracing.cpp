// RayTracing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <complex.h>
#include <immintrin.h>
#include <iostream>
#include <vector>

#include "HittableCollection.h"
#include "Sphere.h"
#include "Camera.h"
#include "MetalMaterial.h"
#include "Dielectric.h"

int main()
{
    //World
    HittableCollection world;

    shared_ptr<Material> groundMat = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.Add(make_shared<Sphere>(Position(0, -1000, 0), 1000, groundMat));

    for (int a = -7; a < 7; a++) {
        for (int b = -7; b < 7; b++) {
            double chooseMat = RandomDouble();
            Position center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

            if ((center - Position(4, 0.2, 0)).Length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (chooseMat < 0.8) {
                    // diffuse
                    auto albedo = Color::Random() * Color::Random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.Add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (chooseMat < 0.95) {
                    // metal
                    auto albedo = Color::Random(0.5, 1);
                    auto fuzz = RandomDouble(0, 0.5);
                    sphere_material = make_shared<MetalMaterial>(albedo, fuzz);
                    world.Add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.Add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    double R = cos(pi / 4);

    shared_ptr<Material> firstMat = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    world.Add(make_shared<Sphere>(Position(0, 1, 0), 1.0, firstMat));
    shared_ptr<Material> secondMat = make_shared<Lambertian>(Color(0.1,0.2,0.5));
    world.Add(make_shared<Sphere>(Position(-4, 1, 0), 1.0, secondMat));
    shared_ptr<Material> thirdMat = make_shared<Dielectric>(1.5);
    world.Add(make_shared<Sphere>(Position(4, 1, 0), 1.0, thirdMat));

    Camera camera(500,16.0 / 9.0, 100,10, 20,
        Position(13,2,3),Position(0,0,0), Vector3(0,1,0)
    , 0.6,10);
    camera.Render(world);
    return 0;

}

;