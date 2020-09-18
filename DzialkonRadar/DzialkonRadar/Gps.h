#pragma once
#include <TinyGPS.h>

class Gps
{
private:
	const int gpsUpdateDelay = 1000;

	const float destLat, destLong;
	float curentLat, curentLong;
	TinyGPS gps;
	HardwareSerial& ss;

public:
	static const float invalidDistance;
	Gps();
	void UpdateData();
	float DistanceBetween();
	float Angle();
};

