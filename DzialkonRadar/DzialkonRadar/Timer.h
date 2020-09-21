#pragma once
#include <DS1302RTC.h>
#include <Time.h>
#include <TimeLib.h>

class Timer
{
  private:
    DS1302RTC* rtc;

  public:
    Timer(int rstPin, int dataPin, int clkPin);
    void SetupClock();
    bool CheckTime(int hour, int minute, int second);
};
