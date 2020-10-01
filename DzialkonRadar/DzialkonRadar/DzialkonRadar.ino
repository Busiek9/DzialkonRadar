//#define CALLIBRATE // uncomment this to start Compass calibration
//#define SETTIME // uncomment this to manualy set time on Timer, see Timer.cpp line 22

#include "RadarMap.h"
#include "Gps.h"
#include "Compass.h"
#include "Timer.h"
#include "Pins.h"

//#ifdef CALLIBRATE
//#include "MySD.h"
//#endif

RadarMap* radarMap;
Gps* myGps;
Compass* myCompass;
const float PopeConstant = 21.37f;

Timer timer(DataPin, ClkPin, CsPin);

void setup() {
  Serial.begin(9600);
  radarMap = new RadarMap(DataPin, ClkPin, CsPin, 4, 50.0f);
  myGps = new Gps();
  myCompass = new Compass();
  timer.SetupClock();
}

void loop() {
  myGps->UpdateData();
  float distance = myGps->DistanceBetween();
  float gpsAngle = myGps->Angle();
  float compassAngle = myCompass->Angle();
  radarMap->SetSegmentPoints(distance, gpsAngle, compassAngle);

  int popeMeters = (int)(distance / PopeConstant);

  if (timer.CheckTime(21, 37, 0))
  {
    // play barka
    // player.PlaySong("BARKA.WAV");
    Serial.println("Swooooja baaaaaaarkeeeee!");
  }

  if (timer.CheckTime(-1, -1, 0))
  {
    // player.PlayDistanceLeft(popeMeters)
    Serial.println("pozostalo x papierzo metrow");
  }

  if (timer.CheckTime(-1, -1, 30))
  {
    // player.PlayRandomVoice();
    Serial.println("randomowy tekst Witka");
  }

  delay(1000);
}
