#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <random>

Vec3 color(const Ray& r, Hitable* world, int depth)
{
	hit_record rec;
	if (world->Hit(r, 0.001, FLT_MAX, rec))
	{
		Ray scattered;
		Vec3 attenuation;
		if (depth < 50 && rec.Mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return Vec3(0, 0, 0);
		}
	}
	else
	{
		Vec3 unitDir = GetNormalVec3(r.Direction());
		float t = 0.5 * (unitDir.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

Vec3 GrammaCorrection(const Vec3& col)
{
	return Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
}

void ShowProgress(int num, int sum)
{
	std::cout << (sum - num) * 100 / sum << "%" << std::endl;
}

int main()
{
	std::ofstream outputFile;
	outputFile.open("OutputImageWithMetal.ppm", std::ios::binary | std::ios::out);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, 1.0f);

	int nx = 200;
	int ny = 100;
	int ns = 100;
	outputFile << "P3\n" << nx << " " << ny << "\n255\n";
	Hitable* list[5];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5,new Lambertian(Vec3(0.1,0.2,0.5)));
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100,new Lambertian(Vec3(0.8,0.8,0.0)));
	list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2),0));
	list[3] = new Sphere(Vec3(-1, 0, -1), 0.51, new Dielectric(1.5));
	list[4] = new Sphere(Vec3(-1, 0, -1), -0.45, new Dielectric(1.5));
	Hitable* world = new HitableList(list, 5);
	Camera cam;
	for (int j = ny - 1;j >= 0;j--)
	{
		ShowProgress(j, ny);
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
				col += color(r, world,0);
			}
			col /= float(ns);
			GrammaCorrection(col);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outputFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cout << "the ppm with different materials has been created,checking in ppm file" << std::endl;
	outputFile.close();
}