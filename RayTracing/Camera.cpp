#include "Camera.h"

using namespace std;

void Camera::Initialize()
{
	height = static_cast<int>(width / aspectRatio);
	if (height < 1) height = 1;

	center = Position(0, 0, 0);
	double focalLength = 1;
	double viewPortHeight = 2;
	double viewPortWidth = viewPortHeight * (static_cast<double>(width) / height);

	Vector3 viewPortX = Vector3(viewPortWidth, 0, 0);
	Vector3 viewPortY = Vector3(0, -viewPortHeight, 0); //We invert Y

	//Delta Vector between pixels
	pixelDeltaX = viewPortX / width;
	pixelDeltaY = viewPortY / height;

	//Position of the top left pixel
	Vector3 viewportOrgin = center - Vector3(0, 0, focalLength) - viewPortX / 2 - viewPortY / 2;

	originPixelLocation = viewportOrgin + 0.5 * (pixelDeltaX + pixelDeltaY);
}

void Camera::Render(const Hittable& rWorld)
{
	Initialize();
	cout << "P3\n" << width << ' ' << height << "\n255\n";
	for(int y = 0; y < height; y++)
	{
		clog << "Progress : " << (y * 100 / height) << " %\n" << flush;
		for(int x = 0; x < width; x++)
		{
			Color pixel(0, 0, 0);
			for (int sample = 0; sample < sampleCount; sample ++)
			{
				Ray ray = GetRay(x, y);
				pixel += RayColor(ray,maxBounces, rWorld);
			}
			Position pixelCenter = originPixelLocation + (x * pixelDeltaX) + (y * pixelDeltaY);
			Vector3 direction = pixelCenter - center;
			Ray ray(center, direction);
			//Color pixel = RayColor(ray, rWorld);
			WriteColor(cout,pixel, sampleCount);
		}
	}
	clog << "Done! You can open your file now :)\n";
}



Color Camera::RayColor(const Ray& rRay,int bouncesLeft, const Hittable& rWorld) const
{
	HitInfo hitInfo;
	if (bouncesLeft <= 0) return Color(0, 0, 0);
	if (rWorld.Hit(rRay, Interval(0.001, infinity), hitInfo))
	{
		Ray scattered;
		Color attenuation;
		if (hitInfo.material->Scatter(rRay, hitInfo, attenuation, scattered))
		{
			return attenuation * RayColor(scattered, bouncesLeft - 1, rWorld);
		}
		return Color(0, 0, 0);
	}
	Vector3 unitDirection = Unit(rRay.GetDirection());
	double blue = 0.5 * (unitDirection.y + 1.0);
	return (1.0 - blue) * Color(1.0, 1.0, 1.0) + blue * Color(0.5, 0.7, 1.0);
}

Ray Camera::GetRay(int x, int y) const
{
	// Get a randomly sampled camera ray for the pixel location i,j.

	Vector3 pixelCenter = originPixelLocation + (x * pixelDeltaX) + (y * pixelDeltaY);
	Vector3 pixelSample = pixelCenter + PixelSampleSquared();

	Position rayOrigin = center;
	Vector3 rayDirection = pixelSample - rayOrigin;

	return Ray(rayOrigin, rayDirection);
}

Vector3 Camera::PixelSampleSquared() const
{
	//returnsq a random point in the square around a pixel at the origin
	double pX = -0.5 + RandomDouble();
	double pY = -0.5 + RandomDouble();
	return (pX * pixelDeltaX) + (pY * pixelDeltaY);
}
