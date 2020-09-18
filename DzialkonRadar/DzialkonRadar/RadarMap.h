#pragma once
#include <LedControl.h>
#include "Gps.h"

class RadarMap
{
private:
	/// <summary>
	/// Distance tolerance in meters to find the destination point.
	/// </summary>
	const int distanceDelta = 10;
	const int size = 8;
	const int maxIndex = size - 1;

	int numDevices;
	float initialDistance;
	LedControl lc;

	void SetPoint(int x, int y, byte quarter);
	byte CalculateQuarter(int x, int y);
	void SetWholeScreen();
	void ClearScreen();
	void ComputeCoordinates(float& x, float& y, float angle, float distance);
	void NormalizeCoordinates(float& x, float& y);
	void RoundCoordinates(float& x, float& y);
	void SetSegmentPoints(int x, int y);

public:
	RadarMap(int dataPin, int clkPin, int csPin, int numDevices = 1, float initialDistance = 1000.0f);
	void SetSegmentPoints(float distance, float gpsAngle, float compassAngle);
	void SetInvalidScreen();
};

