#include "RadarMap.h"
#include <Arduino.h>

RadarMap::RadarMap(int dataPin, int clkPin, int csPin, int numDevices, float initialDistance) :
	lc(LedControl(dataPin, clkPin, csPin, numDevices))
{
	RadarMap::numDevices = numDevices;
	RadarMap::initialDistance = initialDistance;

	for (int i = 0; i < numDevices; i++)
	{
		lc.shutdown(i, false);
		lc.setIntensity(i, 3);
		lc.clearDisplay(i);
	}
}

void RadarMap::SetPoint(int x, int y, byte quarter)
{
	if (quarter == 4)
	{
		SetWholeScreen();
	}
	else if (quarter == 0)
	{
		lc.setLed(quarter, y, maxIndex - x, true);
	}
	else if (quarter == 1)
	{
		lc.setLed(quarter, y + maxIndex, maxIndex - x, true);
	}
	else if (quarter == 2)
	{
		lc.setLed(quarter, -y, maxIndex + x, true);
	}
	else if (quarter == 3)
	{
		lc.setLed(quarter, maxIndex - y, maxIndex + x, true);
	}
}

void RadarMap::SetSegmentPoints(int x, int y)
{
	ClearScreen();

	int quarter = CalculateQuarter(x, y);

	int xMin = min(0, x), xMax = max(0, x);
	int yMin = min(0, y), yMax = max(0, y);

	double a = y / (double)x;

	if (abs(x) > abs(y))
	{
		for (int i = xMin; i < xMax + 1; i++)
		{
			int nearestY = yMin;
			double calculatedY = i * a;
			double delta = abs(calculatedY - nearestY);
			for (int j = yMin + 1; j < yMax + 1; j++)
			{
				double currentDelta = abs(calculatedY - j);

				if (currentDelta < delta)
				{
					delta = currentDelta;
					nearestY = j;
				}
			}

			SetPoint(i, nearestY, quarter);
		}
	}
	else
	{
		for (int i = yMin; i < yMax + 1; i++)
		{
			int nearestX = xMin;
			double calculatedX = i / a;
			double delta = abs(calculatedX - nearestX);
			for (int j = xMin + 1; j < xMax + 1; j++)
			{
				double currentDelta = abs(calculatedX - j);

				if (currentDelta < delta)
				{
					delta = currentDelta;
					nearestX = j;
				}
			}

			SetPoint(nearestX, i, quarter);
		}
	}

	//return quarter;
}

void RadarMap::SetSegmentPoints(float distance, float gpsAngle, float compassAngle)
{
	if (distance == Gps::invalidDistance)
	{
		ClearScreen();
		SetInvalidScreen();
		return;
	}

	float angle = gpsAngle + compassAngle;

	//Serial.print("Initial distance: ");
	//Serial.print(initialDistance);
	//Serial.print(", distance: ");
	//Serial.print(distance);
	//Serial.print(", angle: ");
	//Serial.println(angle);

	if (distance > initialDistance)
	{
		distance = initialDistance;
	}
	if (distance < distanceDelta)
	{
		Serial.println("Destination reached!");
		SetSegmentPoints(0, 0);
		return;
	}

	float x, y;

	ComputeCoordinates(x, y, angle, distance);

	//Serial.print("Calculated point (");
	//Serial.print(x);
	//Serial.print(",");
	//Serial.print(y);
	//Serial.println(")");

	// this is needed to always show some small path, until desired distanceDelta is accuired
	RoundCoordinates(x, y);

	//Serial.print("Calculated point ceil (");
	//Serial.print(x);
	//Serial.print(",");
	//Serial.print(y);
	//Serial.println(")");

	SetSegmentPoints(x, y);
}

void RadarMap::ComputeCoordinates(float& x, float& y, float angle, float distance)
{
	float angleInRadians = radians(angle);
	x = distance * sin(angleInRadians);
	y = distance * cos(angleInRadians);
	NormalizeCoordinates(x, y);
}

/// <summary>
/// Normalize point to fit (-7,-7) to (7,7) range
/// </summary>
void RadarMap::NormalizeCoordinates(float& x, float& y)
{
	x = maxIndex * (x / initialDistance);
	y = maxIndex * (y / initialDistance);
}

void RadarMap::RoundCoordinates(float& x, float& y)
{
	if (abs(x) < 0.5f && abs(y) < 0.5f)
	{
		if (abs(x) >= abs(y))
		{
			x < 0 ? x -= 1 : x += 1;
			y = 0;
		}
		else
		{
			y < 0 ? y -= 1 : y += 1;
			x = 0;
		}
	}

	x = round(x);
	y = round(y);
}

byte RadarMap::CalculateQuarter(int x, int y)
{
	if (x == 0 && y == 0)
	{
		// destination point reached, light all leds on all displays
		return 4;
	}

	if (x >= 0 && y >= 0)
	{
		return 0;
	}

	if (x > 0 && y < 0)
	{
		return 1;
	}

	if (x <= 0 && y <= 0)
	{
		return 2;
	}

	if (x < 0 && y > 0)
	{
		return 3;
	}

	return 0xFF;
}

void RadarMap::ClearScreen()
{
	for (int i = 0; i < numDevices; i++)
	{
		lc.clearDisplay(i);
	}
}

void RadarMap::SetWholeScreen()
{
	for (int i = 0; i < numDevices; i++)
	{
		for (int j = 0; j < size; j++)
		{
			lc.setRow(i, j, 0xFF);
		}
	}
}

void RadarMap::SetInvalidScreen()
{
	for (int i = 0; i < numDevices; i++)
	{
		for (int j = 0; j < size; j++)
		{
			lc.setLed(i, j, j, true);
			lc.setLed(i, size - j - 1, j, true);
		}
	}
}