#include "Compass.h"

Compass::Compass()
{
	Wire.begin();
	qmc.init();
}

float Compass::Angle()
{
	int x, y, z;
	float azimuth;
	qmc.read(&x, &y, &z);

//#ifdef CALLIBRATE
//	MySD* mySD = new MySD(49);
//	File file = mySD->OpenFile("comp.txt");
//	file.print(x);
//	file.print("\t");
//	file.print(y);
//	file.print("\t");
//	file.print(z);
//	file.print("\t");
//	file.println(azimuth);
//	mySD->CloseFile(file);
//#endif // CALLIBRATE

	x = map(x, -1393, -191, -1000, 1000);
	y = map(y, 1525, 2376, -1000, 1000);

	azimuth = Azimuth(x, y);

	return azimuth;
}

float Compass::Azimuth(int x, int y) {
	float azimuth = atan2(x, y);
	if (azimuth < 0)
	{
		azimuth += 2 * PI;
	}

	return degrees(azimuth);
}
