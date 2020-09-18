#include "Gps.h"

const float Gps::invalidDistance = -1.0f;

Gps::Gps() :
	// działka Pitera
	//destLat(51.589655f),
	//destLong(19.223912f)
	destLat(51.798631f),
	destLong(19.457566f),
	ss(Serial1)
{
	ss.begin(9600);
}

float Gps::DistanceBetween()
{
	if (curentLat == TinyGPS::GPS_INVALID_F_ANGLE && curentLong == TinyGPS::GPS_INVALID_F_ANGLE)
	{
		return Gps::invalidDistance;
	}
	return TinyGPS::distance_between(curentLat, curentLong, destLat, destLong);
}

float Gps::Angle()
{
	return TinyGPS::course_to(curentLat, curentLong, destLat, destLong);
}

void Gps::UpdateData()
{
	unsigned long start = millis();
	do
	{
		while (ss.available()) {
			byte gpsData = ss.read();
			gps.encode(gpsData);

		}
	} while (millis() - start < gpsUpdateDelay);

	gps.f_get_position(&curentLat, &curentLong);
}