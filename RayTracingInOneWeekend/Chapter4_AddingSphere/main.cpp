#include "Ray.h"
#include "Vec3.h"
#include <iostream>
#include <fstream>

bool isHitSphere(const Vec3& center, float radius, const Ray& r)
{
	// sphere equation:
	//t*t*dot(B,B) + 2*t*t*dot(B,A-C) + dot(A-C,A-C)-R*R = 0
	Vec3 oc = r.Origin() - center;
	float factor_a = dot(r.Direction(), r.Direction());
	float factor_b = 2.0 * dot(oc, r.Direction());
	float factor_c = dot(oc, oc) - radius * radius;
	//delta = b*b - 4ac
	float delta = factor_b * factor_b - 4 * factor_a * factor_c;
	return (delta > 0);
}

Vec3 color(const Ray& r)
{
	//if hit sphere color turn to red
	if (isHitSphere(Vec3(0, 0, -1), 0.5, r))
		return Vec3(1, 0, 0);

	Vec3 unitDir = GetNormalVec3(r.Direction());
	//clamp t in [0,1]
	float t = 0.5 * (unitDir.y() + 1.0);
	//interpolation
	return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main()
{
	std::ofstream outputFile;
	outputFile.open("OutputImageWithSphere.ppm", std::ios::binary | std::ios::out);

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
	std::cout << "the ppm with sphere has been created,checking in ppm file" << std::endl;
	outputFile.close();
}



