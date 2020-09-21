//#define CALLIBRATE
//#define SETTIME

#include "RadarMap.h"
#include "Gps.h"
#include "Compass.h"
#include "Timer.h"

#ifdef CALLIBRATE
#include "MySD.h"
#endif

RadarMap* radarMap;
Gps* myGps;
Compass* myCompass;
const float popeConstant = 21.37f;

Timer timer(26, 24, 22);

void setup() {
  Serial.begin(9600);
  //  radarMap = new RadarMap(51, 52, 53, 4, 50.0f);
  //  myGps = new Gps();
  //  myCompass = new Compass();
  //  CallibrationStart();
  timer.SetupClock();
}

void loop() {
  //  myGps->UpdateData();
  //  float distance = myGps->DistanceBetween();
  //  float gpsAngle = myGps->Angle();
  //  float compassAngle = myCompass->Angle();
  //  radarMap->SetSegmentPoints(distance, gpsAngle, compassAngle);
  //
  //  int popeMeters = (int)(distance / popeContant);

  if(timer.CheckTime(21, 37, 0))
  {
    // play barka
    // player.PlaySong("BARKA.WAV");
    Serial.println("Swooooja baaaaaaarkeeeee!");
  }

  if(timer.CheckTime(-1, -1, 0))
  {
    // player.PlayDistanceLeft(popeMeters)
    Serial.println("pozostalo x papierzo metrow");
  }

  if(timer.CheckTime(-1, -1, 30))
  {
    // player.PlayRandomVoice();
    Serial.println("randomowy tekst Witka");
  }

  delay(1000);
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
