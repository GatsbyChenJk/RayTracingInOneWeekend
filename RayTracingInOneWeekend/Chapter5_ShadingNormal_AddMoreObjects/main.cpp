#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Hitable.h"
#include "HitableList.h"
#include <iostream>
#include <fstream>
#include <math.h>

float SphereHitPoint(const Vec3& center, float radius, const Ray& r)
{
	// sphere equation:
	//t*t*dot(B,B) + 2*t*t*dot(B,A-C) + dot(A-C,A-C)-R*R = 0
	Vec3 oc = r.Origin() - center;
	float factor_a = dot(r.Direction(), r.Direction());
	float factor_b = 2.0 * dot(oc, r.Direction());
	float factor_c = dot(oc, oc) - radius * radius;
	//delta = b*b - 4ac
	float delta = factor_b * factor_b - 4 * factor_a * factor_c;
	
	return delta < 0 ? -1.0 : (-factor_b - sqrt(delta)) / (2.0 * factor_a);
}

Vec3 color(const Ray& r)
{
	float t = SphereHitPoint(Vec3(0, 0, -1), 0.5, r);
	//calculate normal vector 
	if (t > 0.0)
	{
		Vec3 NormalDir = GetNormalVec3(r.PointWithParameter_t(t) - Vec3(0, 0, -1));
		return 0.5 * Vec3(NormalDir.x() + 1, NormalDir.y() + 1, NormalDir.z() + 1);
	}
	Vec3 unitDir = GetNormalVec3(r.Direction());
	//clamp t in [0,1]
	t = 0.5 * (unitDir.y() + 1.0);
	//interpolation
	return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

Vec3 color(const Ray& r, Hitable* world)
{
	hit_record rec;
	if (world->Hit(r, 0.0, 1000.0f, rec))
	{
		return 0.5 * Vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else
	{
		Vec3 unitDir = GetNormalVec3(r.Direction());
		float t = 0.5 * (unitDir.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

void CreateSingleSphereWithNormal()
{
	std::ofstream outputFile;
	outputFile.open("OutputImageWithSphereNormal.ppm", std::ios::binary | std::ios::out);

	int nx = 200;
	int ny = 100;
	outputFile << "P3\n" << nx << " " << ny << "\n255\n";

	Vec3 LowerLeftCorner(-2.0, -1.0, -1.0);
	Vec3 Hor(4.0, 0.0, 0.0);
	Vec3 Ver(0.0, 2.0, 0.0);
	Vec3 Origin(0.0, 0.0, 0.0);
	for (int j = ny - 1;j >= 0;j--)
	{
		for (int i = 0;i < nx;i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			Ray r(Origin, LowerLeftCorner + u * Hor + v * Ver);
			Vec3 col = color(r);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outputFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cout << "the ppm with sphere and normal has been created,checking in ppm file" << std::endl;
	outputFile.close();
}

void CreateMultibleObjectsWithNormal()
{
	std::ofstream outputFile;
	outputFile.open("OutputImageWithMoreSphereNormal.ppm", std::ios::binary | std::ios::out);

	int nx = 200;
	int ny = 100;
	outputFile << "P3\n" << nx << " " << ny << "\n255\n";

	Vec3 LowerLeftCorner(-2.0, -1.0, -1.0);
	Vec3 Hor(4.0, 0.0, 0.0);
	Vec3 Ver(0.0, 2.0, 0.0);
	Vec3 Origin(0.0, 0.0, 0.0);

	Hitable* list[2];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
	list[1] = new Sphere(Vec3(0, - 100.5, -1), 100);
	Hitable* world = new HitableList(list, 2);

	for (int j = ny - 1;j >= 0;j--)
	{
		for (int i = 0;i < nx;i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			Ray r(Origin, LowerLeftCorner + u * Hor + v * Ver);
			
			Vec3 p = r.PointWithParameter_t(2.0);
			Vec3 col = color(r, world);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outputFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cout << "the ppm with more sphere and normal has been created,checking in ppm file" << std::endl;
	outputFile.close();
}

int main()
{
	CreateSingleSphereWithNormal();
	CreateMultibleObjectsWithNormal();
}

