#pragma once
#ifndef HITABLELISTH
#define HITABLELISTH

#include "Hitable.h"

class HitableList : public Hitable
{
public:
	Hitable** list;
	int size;

	HitableList(){}
	HitableList(Hitable** l, int n) :list(l), size(n) {}
	virtual bool Hit(
		const Ray& r,
		float t_min,
		float t_max,
		hit_record& rec
	) const;
};

bool HitableList::Hit(
	const Ray& r,
	float t_min,
	float t_max,
	hit_record& rec
) const
{
	hit_record tempRec;
	bool isHitAnything = false;
	double closet_so_far = t_max;
	for (int i = 0;i < size;i++)
	{
		if (list[i]->Hit(r, t_min, closet_so_far, tempRec))
		{
			isHitAnything = true;
			closet_so_far = tempRec.t;
			rec = tempRec;
		}
	}
	return isHitAnything;
}
#endif