// RayTracing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <complex.h>
#include <immintrin.h>
#include <iostream>
#include <vector>

#include "Color.h"
#include "Hitable.h"
#include "HittableCollection.h"
#include "Sphere.h"
#include "Utility.h"


Color RayColor(const Ray& rRay, const Hittable& rWorld)
{
    HitInfo hitInfo;
    if (rWorld.Hit(rRay, Interval(0, infinity), hitInfo))
        return 0.5 * (hitInfo.normal + Color(1, 1, 1));
    Vector3 unitDirection = Unit(rRay.GetDirection());
    double blue = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - blue) * Color(1.0, 1.0, 1.0) + blue * Color(0, 0, 1.0);

}




int main()
{
    double resolution = 16.0 / 9.0;
    int width = 400, height = static_cast<int>(width / resolution);
    if (height < 1) height = 1;

    //Viewport
    double viewportHeight = 2;
    double viewportWidth = viewportHeight * (static_cast<double>(width) / height);
    double focallength = 1;
    Position cameraCenter = Position(0, 0, 0);

    Vector3 viewportX = Vector3(viewportWidth, 0, 0);
    Vector3 viewportY = Vector3(0, -viewportHeight, 0); // We invert Y

    //Delta vector between Pixels
 
    Vector3 pixelDeltaX = viewportX / width;
    Vector3 pixelDeltaY = viewportY / height;

    //Position of the top left pixel
    Vector3 viewportOrigin = cameraCenter - Vector3(0, 0, focallength)
        - viewportX / 2 - viewportY / 2;

    Vector3 originPixelLocation = viewportOrigin + 0.5 * (pixelDeltaX + pixelDeltaY);

    //World
    HittableCollection world;
    world.Add(make_shared<Sphere>(Position(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(Position(0, -100.5, 0), 100));




    //Image
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    for (int y = 0; y < height; y++)
    {
        std::clog<<"Progress : " << (y * 100 / height) << " %\n" << std::flush;
        for (int x = 0; x < width; x++)
        {
            Vector3 pixelCenter = originPixelLocation + (x * pixelDeltaX) + (y * pixelDeltaY);
            Vector3 rayDirection = pixelCenter - cameraCenter;
            Ray ray(cameraCenter, rayDirection);
            Color pixelColor = RayColor(ray,world);
            WriteColor(std::cout, pixelColor);
        }
    }
    std::clog << "Done! You can open your fine now :) \n";
}

;