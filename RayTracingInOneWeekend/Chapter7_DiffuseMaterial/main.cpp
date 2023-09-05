#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <random>

const int max_depth = 50;
//generate point inside the sphere
Vec3 RandomPointInUnitSphere()
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

Vec3 RandomVec3InUnitSphere()
{
	float phi = rand() / (RAND_MAX + 1.0) * 2 * 3.14159;
	float z = 2.0 * rand() / (RAND_MAX + 1.0) - 1.0;
	float radius = sqrt(1.0 - z * z);
	return Vec3(radius * cos(phi), radius * sin(phi), z);
}

Vec3 color(const Ray& r, Hitable* world)
{
	hit_record rec;
	if (world->Hit(r, 0.0, FLT_MAX, rec))
	{
		Vec3 target = rec.p + rec.normal + RandomPointInUnitSphere();
		return 0.5 * color(Ray(rec.p, target - rec.p), world);
	}
	else
	{
		Vec3 unitDir = GetNormalVec3(r.Direction());
		float t = 0.5 * (unitDir.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

Vec3 color(const Ray& r, Hitable* world, int depth)
{
	hit_record rec;
	if (depth <= 0)
	{
		return Vec3(0, 0, 0);
	}
	if (world->Hit(r, 0.0, FLT_MAX, rec))
	{
		Vec3 target = rec.p + rec.normal + RandomVec3InUnitSphere();
		return 0.5 * color(Ray(rec.p, target - rec.p), world, depth -1);
	}
	Vec3 unitDir = GetNormalVec3(r.Direction());
	float t = 0.5 * (unitDir.y() + 1.0);
	return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

void CreateImageWithDiffuse()
{
	std::ofstream outputFile;
	outputFile.open("OutputImageWithDiffuse.ppm", std::ios::binary | std::ios::out);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, 1.0f);

	int nx = 200;
	int ny = 100;
	int ns = 100;
	outputFile << "P3\n" << nx << " " << ny << "\n255\n";
	Hitable* list[2];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
	Hitable* world = new HitableList(list, 2);
	Camera cam;
	for (int j = ny - 1;j >= 0;j--)
	{
		for (int i = 0;i < nx;i++)
		{
			Vec3 col(0, 0, 0);
			for (int s = 0;s < ns;s++)
			{
				float rand = dis(gen);
				float rand2 = dis(gen);
				float u = float(i + rand) / float(nx);
				float v = float(j + rand2) / float(ny);
				Ray r = cam.GetRay(u, v);
				Vec3 p = r.PointWithParameter_t(2.0);
				col += color(r, world);
			}
			col /= float(ns);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outputFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cout << "the ppm with diffiuse has been created,checking in ppm file" << std::endl;
	outputFile.close();
}

void CreateImageWithGramma()
{
	std::ofstream outputFile;
	outputFile.open("OutputImageWithGramma.ppm", std::ios::binary | std::ios::out);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, 1.0f);

	int nx = 200;
	int ny = 100;
	int ns = 100;
	outputFile << "P3\n" << nx << " " << ny << "\n255\n";
	Hitable* list[2];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
	Hitable* world = new HitableList(list, 2);
	Camera cam;
	for (int j = ny - 1;j >= 0;j--)
	{
		for (int i = 0;i < nx;i++)
		{
			Vec3 col(0, 0, 0);
			for (int s = 0;s < ns;s++)
			{
				float rand = dis(gen);
				float rand2 = dis(gen);
				float u = float(i + rand) / float(nx);
				float v = float(j + rand2) / float(ny);
				Ray r = cam.GetRay(u, v);
				Vec3 p = r.PointWithParameter_t(2.0);
				col += color(r, world);
			}
			col /= float(ns);
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outputFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cout << "the ppm with Gramma has been created,checking in ppm file" << std::endl;
	outputFile.close();
}

void CreateImageWithCorrection()
{
	std::ofstream outputFile;
	outputFile.open("OutputImageWithCorrection.ppm", std::ios::binary | std::ios::out);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, 1.0f);

	int nx = 200;
	int ny = 100;
	int ns = 100;
	outputFile << "P3\n" << nx << " " << ny << "\n255\n";
	Hitable* list[2];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
	Hitable* world = new HitableList(list, 2);
	Camera cam;
	for (int j = ny - 1;j >= 0;j--)
	{
		for (int i = 0;i < nx;i++)
		{
			Vec3 col(0, 0, 0);
			for (int s = 0;s < ns;s++)
			{
				float rand = dis(gen);
				float rand2 = dis(gen);
				float u = float(i + rand) / float(nx);
				float v = float(j + rand2) / float(ny);
				Ray r = cam.GetRay(u, v);
				Vec3 p = r.PointWithParameter_t(2.0);
				col += color(r, world,max_depth);
			}
			col /= float(ns);
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outputFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cout << "the ppm with Correction has been created,checking in ppm file" << std::endl;
	outputFile.close();
}

int main()
{
	CreateImageWithDiffuse();
	CreateImageWithGramma();
	CreateImageWithCorrection();
}