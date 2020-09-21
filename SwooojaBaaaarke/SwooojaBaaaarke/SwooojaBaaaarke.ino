#include <SD.h>
#include <SPI.h>
#include <LedControl.h>
#include "AudioPlayer.h"

#define SD_PIN 49

AudioPlayer player(46, 8);

void setup() {
  Serial.begin(9600);

  while (!SetupSD()) {
    delay(1000);
  };
//
//  char songName[] = "BARKA.WAV";
//  player.PlaySong(songName);


}

void loop() {
//  player.PlayRandomVoice();
//  delay(2000);

  int random = (rand() % 2000);
  Serial.println(random);
  player.PlayDistanceLeft(random);
//  delay(1000);
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
