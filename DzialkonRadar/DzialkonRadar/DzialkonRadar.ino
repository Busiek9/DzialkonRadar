//#define CALLIBRATE

#include "RadarMap.h"
#include "Gps.h"
#include "Compass.h"

//#include <TinyGPS.h>
//#include <SD.h>

#ifdef CALLIBRATE
#include "MySD.h"
#endif

RadarMap* radarMap;
Gps* myGps;
Compass* myCompass;
const float popeConstant = 21.37f;

//#include <TimeLib.h>
//#include <Time.h>
//#include <DS1302RTC.h>
//#define RTC_PIN 26
//DS1302RTC rtc(RTC_PIN, 24, 22);

void setup() {
  Serial.begin(9600);
  radarMap = new RadarMap(51, 52, 53, 4, 50.0f);
  myGps = new Gps();
  myCompass = new Compass();
  CallibrationStart();
  //SetupClock();
}

void loop() {
  myGps->UpdateData();
  float distance = myGps->DistanceBetween();
  float gpsAngle = myGps->Angle();
  float compassAngle = myCompass->Angle();
  radarMap->SetSegmentPoints(distance, gpsAngle, compassAngle);

  int popeMeters = (int)(distance / popeContant);
}

void CallibrationStart()
{
#ifdef CALLIBRATE
  MySD mySD(49);
  File file = mySD.OpenFile("comp.txt");
  file.println();
  file.println("---- CALIBRATION BEGINS ----");
  file.println();
  mySD.CloseFile(file);
#endif // CALLIBRATE
}

//void SetupClock()
//{
//  // Check clock oscillation
//  if (rtc.haltRTC())
//    Serial.println("Clock stopped!");
//  else
//    Serial.println("Clock working.");
//
//  // Check write-protection
//  if (rtc.writeEN())
//    Serial.println("Write allowed.");
//  else
//    Serial.println("Write protected.");
//
//  delay(500);
//
//
//
//  bool needToSetTime = false;
//  if (needToSetTime)
//  {
//    tmElements_t timeToSet;
//    timeToSet.Day = 8;
//    timeToSet.Month = 8;
//    timeToSet.Year = CalendarYrToTm(2020);
//    timeToSet.Hour = 16;
//    timeToSet.Minute = 04;
//    timeToSet.Second = 0;
//    rtc.write(timeToSet);
//  }
//
//  // Setup Time library
//  Serial.println("RTC Sync");
//  setSyncProvider(rtc.get); // the function to get the time from the RTC
//  switch (timeStatus())
//  {
//  case timeNotSet:
//    Serial.println("Time not set");
//    break;
//  case timeNeedsSync:
//    Serial.println("Time need sync");
//    break;
//  case timeSet:
//    Serial.println("Time set to ");
//    Serial.print(day());
//    Serial.print(".");
//    Serial.print(month());
//    Serial.print(".");
//    Serial.print(year());
//    Serial.print(" ");
//    Serial.print(hour());
//    Serial.print(":");
//    Serial.print(minute());
//    Serial.print(":");
//    Serial.println(second());
//    break;
//  default:
//    Serial.println("Unknown status");
//  }
//
//  delay(500);
//}

bool CheckTime()
{

}
