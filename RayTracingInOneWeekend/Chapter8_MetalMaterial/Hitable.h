#pragma once
#ifndef HITABLEH
#define HITABLEH

#include "Ray.h"

class Material;

struct hit_record
{
	float t;
	Vec3 p;
	Vec3 normal;
	Material* Mat_ptr;
};

class Hitable
{
public:
	virtual bool Hit(
		const Ray& r,
		float t_min,
		float t_max,
		hit_record& rec
	) const = 0;
};

#endif
