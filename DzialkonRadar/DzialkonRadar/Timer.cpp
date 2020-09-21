#include "Timer.h"

Timer::Timer(int rstPin, int dataPin, int clkPin)
{
  rtc = new DS1302RTC(rstPin, dataPin, clkPin);
}

void Timer::SetupClock()
{
  // Check clock oscillation
  if (rtc->haltRTC())
  {
    Serial.println("Clock stopped!");
  }
  else
  {
    Serial.println("Clock working.");
  }
  delay(500);

#ifdef SETTIME
  tmElements_t timeToSet;
  timeToSet.Day = 21;
  timeToSet.Month = 9;
  timeToSet.Year = CalendarYrToTm(2020);
  timeToSet.Hour = 10;
  timeToSet.Minute = 47;
  timeToSet.Second = 0;
  int a = rtc->write(timeToSet);
  Serial.print("Status: ");
  Serial.println(a);
#endif

  // Setup Time library
  Serial.println("RTC Sync");
  setSyncProvider(rtc->get); // the function to get the time from the RTC
  switch (timeStatus())
  {
    case timeNotSet:
      Serial.println("Time not set");
      break;
    case timeNeedsSync:
      Serial.println("Time need sync");
      break;
    case timeSet:
      Serial.print("Time set to ");
      Serial.print(day());
      Serial.print(".");
      Serial.print(month());
      Serial.print(".");
      Serial.print(year());
      Serial.print(" ");
      Serial.print(hour());
      Serial.print(":");
      Serial.print(minute());
      Serial.print(":");
      Serial.println(second());
      break;
    default:
      Serial.println("Unknown status");
  }
}

/// <summary>
/// Check specific time. Pass -1 whenever you're not interested in checking particular part of time.
/// </summary>
bool Timer::CheckTime(int hours, int minutes, int seconds)
{
  if(hours != -1 && hour() != hours)
  {
    return false;
  }

  if(minutes != -1 && minute() != minutes)
  {
    return false;
  }

  if(seconds != -1 && second() != seconds)
  {
    return false;
  }

  return true;
}
