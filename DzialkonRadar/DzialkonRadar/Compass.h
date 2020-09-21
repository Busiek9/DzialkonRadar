#pragma once

#include <Wire.h>
#include <MechaQMC5883.h>

#ifdef CALLIBRATE
#include "MySD.h"
#endif

class Compass
{
  private:
    MechaQMC5883 qmc;

    float Azimuth(int x, int y);
  public:
    Compass();
    float Angle();
};
