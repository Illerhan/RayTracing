#pragma once

#include "Hitable.h"

class Camera
{
public:
	Camera() = default;
	Camera(double imageWidth, double ratio, int samplePerPixel = 10, int bounces = 10, 
		double vFov = 90, Position lookFrom = Position(0,0,-1),
		Position lookHat = Position(0,0,0), Vector3 vUp = Vector3(0,1,0),
		double defocusAngle = 0, double focusDistance = 10 )
	: aspectRatio(ratio), width(imageWidth), mVFov(vFov), sampleCount(samplePerPixel), maxBounces(bounces),
	mLookFrom(lookFrom), mLookHat(lookHat), mVUp(vUp), mDefocusAngle(defocusAngle), mFocusDistance(focusDistance) {}
	void Render(const Hittable& rWorld);
private:
	int height;
	double aspectRatio, width, mVFov, mDefocusAngle, mFocusDistance;
	int sampleCount;
	int maxBounces;
	Position center, originPixelLocation, mLookFrom, mLookHat;
	Vector3 pixelDeltaX, pixelDeltaY, mVUp;
	Vector3 u, v, w;
	Vector3 defocusDiskX;
	Vector3 defocusDiskY;

	void Initialize();
	Color RayColor(const Ray& rRay,int bouncesLeft, const Hittable& rWorld) const;
	Ray GetRay(int x, int y) const;
	Vector3 PixelSampleSquared() const;
	Position DefocusDiskSample() const;
};

