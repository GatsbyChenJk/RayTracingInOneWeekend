#include "Vec3.h"
#include "Ray.h"
#include <iostream>
#include <fstream>

Vec3 color(const Ray& r)
{
	Vec3 unitDir = GetNormalVec3(r.Direction());
	//clamp t in [0,1]
	float t = 0.5 * (unitDir.y() + 1.0);
	//interpolation
	return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}
//blend green with other color with RGB
Vec3 color(const Ray& r, const Vec3& BlendColor)
{
	Vec3 unitDir = GetNormalVec3(r.Direction());
	float t = 0.5 * (unitDir.y() + 1.0);
	return (1.0 - t) * Vec3(0.0, 1.0, 0.0) + t * BlendColor;
}

void CreateImageWithVec3()
{
	std::ofstream outputFile;
	outputFile.open("OutputImageWithVec3.ppm", std::ios::binary | std::ios::out);

	int nx = 200;
	int ny = 100;
	outputFile << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0;i < nx;i++)
		{
			Vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			outputFile << ir << " " << ig << " " << ib << "\n";
		}
	}

	std::cout << "the HelloWorld in Ray Tacing has been created,checking in ppm file" << std::endl;
	outputFile.close();
}

void CreateImageWithRay()
{
	std::ofstream outputFile;
	outputFile.open("OutputImageWithRay.ppm", std::ios::binary | std::ios::out);

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
	std::cout << "the ppm with ray has been created,checking in ppm file" << std::endl;
	outputFile.close();
}

void CreateImageWithRayAndCustomColor(const Vec3& Color)
{
	std::ofstream outputFile;
	outputFile.open("OutputImageWithRayAndCustomColor.ppm", std::ios::binary | std::ios::out);


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
			Vec3 col = color(r,Color);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outputFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	std::cout << "the ppm with ray and custom color has been created,checking in ppm file" << std::endl;
	outputFile.close();
}

int main()
{
	std::cout << "Press 1 to use Vec,Press 2 to use Ray" << std::endl;
	int op;
	float col[3];
	std::cin >> op;	
	switch (op)
	{
	case 1: CreateImageWithVec3();
		break;
	case 2: CreateImageWithRay();
		break;
	case 3:
		std::cout << "press R factor:\n";
		std::cin >> col[0];
		
		std::cout << "press G factor:\n";
		std::cin >> col[1];

		std::cout << "press B factor:\n";
		std::cin >> col[2];

		CreateImageWithRayAndCustomColor(Vec3(col[0],col[1],col[2]));
		break;
	default:
		std::cout << "wrong operation" << std::endl;
		break;
	}

	//delete col;
	return 0;
}