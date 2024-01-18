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

    double R = cos(pi / 4);

    shared_ptr<Material> groundMat = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    shared_ptr<Material> centerMat = make_shared<Lambertian>(Color(0.1,0.2,0.5));
    shared_ptr<Material> leftMat = make_shared<Dielectric>(1.5);
    shared_ptr<Material> rightMat = make_shared<MetalMaterial>(Color(0.8,0.6,0.2),0.0);

    world.Add(make_shared<Sphere>(Position(0, -100.5, -1), 100, groundMat));
    world.Add(make_shared<Sphere>(Position(0, 0, -1), 0.5, centerMat));
    world.Add(make_shared<Sphere>(Position(-1.0, 0, -1), 0.5, leftMat));
    world.Add(make_shared<Sphere>(Position(-1.0, 0.0, -1.0), -0.4, leftMat));
    world.Add(make_shared<Sphere>(Position(1.0, 0, -1), 0.5, rightMat));

    Camera camera(400,16.0 / 9.0, 100,50, 20,
        Position(-2,2,1),Position(0,0,-1), Vector3(0,1,0)
    , 10,3.4);
    camera.Render(world);
    return 0;

}

;