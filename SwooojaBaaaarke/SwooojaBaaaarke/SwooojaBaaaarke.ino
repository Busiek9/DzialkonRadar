#include <TimeLib.h>
#include <Time.h>
#include <DS1302RTC.h>
#include <TMRpcm.h>
#include <SD.h>
#include <SPI.h>
#include <LedControl.h>

#define SPEAKER_PIN 46

// SPI pins
#define SD_PIN 49
//#define RTC_PIN 26

//DS1302RTC rtc(RTC_PIN, 24, 22);
TMRpcm tmrpcm;

void setup() {
  Serial.begin(9600);

  while (!SetupSD()) {
    delay(1000);
  };

  //	if (SD.exists("BARKA1.WAV")) {
  //		Serial.println("BARKA1.WAV exists");
  //	}
  //	else {
  //		Serial.println("BARKA1.WAV does not exist");
  //		return;
  //	}

  SetupSpeaker();

  char songName[] = "BARKA.WAV";
  PlaySong(songName);

  //SetupClock();
}

void loop() {
}

void SpeakerCheck()
{
  Serial.println("Speaker check");
  for (int i = 40; i < 10000; i++)
  {
    tone(SPEAKER_PIN, i, 10);
  }
}

void PlaySong(char* songName)
{
  if (SD.exists(songName)) {
    tmrpcm.play(songName);
    while (tmrpcm.isPlaying())
    {
      delay(300);
    }
  }
  else {
    Serial.print(songName);
    Serial.println(" does not exist");
    //return;
  }
}

bool SetupSD()
{
  if (!SD.begin(SD_PIN)) {
    Serial.println("SD fail");
    return false;
  }

  Serial.println("SD initialized");
  return true;
}

void SetupSpeaker()
{
  tmrpcm.speakerPin = SPEAKER_PIN;
  tmrpcm.setVolume(5);

  //SpeakerCheck();
}

//void SetupClock()
//{
//	// Check clock oscillation
//	if (rtc.haltRTC())
//		Serial.println("Clock stopped!");
//	else
//		Serial.println("Clock working.");
//
//	// Check write-protection
//	if (rtc.writeEN())
//		Serial.println("Write allowed.");
//	else
//		Serial.println("Write protected.");
//
//	delay(500);
//
//
//
//	bool needToSetTime = false;
//	if (needToSetTime)
//	{
//		tmElements_t timeToSet;
//		timeToSet.Day = 8;
//		timeToSet.Month = 8;
//		timeToSet.Year = CalendarYrToTm(2020);
//		timeToSet.Hour = 16;
//		timeToSet.Minute = 04;
//		timeToSet.Second = 0;
//		rtc.write(timeToSet);
//	}
//
//	// Setup Time library
//	Serial.println("RTC Sync");
//	setSyncProvider(rtc.get); // the function to get the time from the RTC
//	switch (timeStatus())
//	{
//	case timeNotSet:
//		Serial.println("Time not set");
//		break;
//	case timeNeedsSync:
//		Serial.println("Time need sync");
//		break;
//	case timeSet:
//		Serial.println("Time set to ");
//		Serial.print(day());
//		Serial.print(".");
//		Serial.print(month());
//		Serial.print(".");
//		Serial.print(year());
//		Serial.print(" ");
//		Serial.print(hour());
//		Serial.print(":");
//		Serial.print(minute());
//		Serial.print(":");
//		Serial.println(second());
//		break;
//	default:
//		Serial.println("Unknown status");
//	}
//
//	delay(500);
//}

bool CheckTime()
{

}
