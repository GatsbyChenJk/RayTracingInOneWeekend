#include "Vec3.h"
#include <iostream>
#include <fstream>

int main()
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

	outputFile.close();
	return 0;
}