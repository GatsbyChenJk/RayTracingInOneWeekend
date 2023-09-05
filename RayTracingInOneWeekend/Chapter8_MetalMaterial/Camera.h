#pragma once
#ifndef CAMERAH
#define CAMERAH

#include "Ray.h"

class Camera
{
public:
	Vec3 LowerLeftCorner;
	Vec3 Hor;
	Vec3 Ver;
	Vec3 Origin;

public:
	Camera()
	{
		LowerLeftCorner = Vec3(-2.0, -1.0, -1.0);
		Hor = Vec3(4.0, 0.0, 0.0);
		Ver = Vec3(0.0, 2.0, 0.0);
		Origin = Vec3(0.0, 0.0, 0.0);
	}

	Ray GetRay(float u, float v)
	{
		return Ray(Origin, LowerLeftCorner + u * Hor + v * Ver - Origin);
	}
};

#endif