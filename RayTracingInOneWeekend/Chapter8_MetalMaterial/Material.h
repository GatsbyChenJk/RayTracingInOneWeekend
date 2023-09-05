#pragma once
#include "Ray.h"
#include "Hitable.h"
#include <random>
class Material
{
public:
	virtual bool scatter(const Ray& RIn, const hit_record& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

inline Vec3 RandomPointInUnitSphere()
{
	Vec3 p;
	do
	{
		float randNums[3];
		for (auto& randNum : randNums)
		{
			randNum = rand() / (RAND_MAX + 1.0);
		}
		p = 2.0 * Vec3(randNums[0], randNums[1], randNums[2]) - Vec3(1, 1, 1);
	} while (p.length2() >= 1.0);
	return p;
}

class Lambertian : public Material
{
public:
	Vec3 albedo;
public:
	Lambertian(const Vec3& a) : albedo(a){}
	virtual bool scatter(const Ray& RIn, const hit_record& rec, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 target = rec.p + rec.normal + RandomPointInUnitSphere();
		scattered = Ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
};



inline Vec3 GetReflectDir(const Vec3& v, const Vec3& n)
{
	return v - 2 * dot(v, n) * n;
}

class Metal : public Material
{
public:
	Vec3 albedo;
	float fuzz = 0;
public:
	Metal(const Vec3& a) : albedo(a) {}
	Metal(const Vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f;else fuzz = 1; }
	virtual bool scatter(const Ray& RIn, const hit_record& rec, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 reflected = GetReflectDir(GetNormalVec3(RIn.Direction()), rec.normal);
		if (fuzz == 0)
			scattered = Ray(rec.p, reflected);
		else
			scattered = Ray(rec.p, reflected + fuzz * RandomPointInUnitSphere());
		attenuation = albedo;
		return (dot(scattered.Direction(), rec.normal) > 0);
	}
};

inline bool GetRefractDir(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted)
{
	Vec3 unitV = GetNormalVec3(v);
	float theta = dot(unitV, n);
	//total internal reflection 
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - theta * theta);
	if (discriminant > 0)
	{
		//the direction of the refracted light
		refracted = ni_over_nt * (unitV - n * theta) - n * sqrt(discriminant);
		return true;
	}
	else
		return false;
}

inline float schlick(float cosine, float ref_idx)
{
	float r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 *= r0;
	return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
}

class Dielectric : public Material
{
public:
	float ref_idx;
public:
	Dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(const Ray& RIn, const hit_record& rec, Vec3& attenuation, Ray& scattered) const
	{

		std::random_device rdvice;
		std::mt19937 gener(rdvice());
		std::uniform_real_distribution<float> distri(0.0f, 0.999f);

		Vec3 outward_normal;
		Vec3 reflected = GetReflectDir(RIn.Direction(), rec.normal);
		float ni_over_nt;
		attenuation = Vec3(1.0, 1.0, 1.0);
		Vec3 refracted;
		//correction parameter
		float reflect_prob;
		float cosine;

		if (dot(RIn.Direction(), rec.normal) > 0)
		{
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(RIn.Direction(), rec.normal) / RIn.Direction().length();
			//cosine *= sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
		}
		else
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(RIn.Direction(), rec.normal) / RIn.Direction().length();
		}
		if (GetRefractDir(RIn.Direction(), outward_normal, ni_over_nt, refracted))
		{
			//scattered = Ray(rec.p, refracted);
			reflect_prob = schlick(cosine, ref_idx);
		}
		else
		{
			//scattered = Ray(rec.p, reflected);
			reflect_prob = 1.0;
		}
		if (distri(gener) < reflect_prob)
		{
			scattered = Ray(rec.p, reflected);
		}
		else
		{
			scattered = Ray(rec.p, refracted);
		}

		return true;
	}
};

