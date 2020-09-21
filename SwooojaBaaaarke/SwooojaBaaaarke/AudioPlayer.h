#pragma once
#include <TMRpcm.h>
#include <time.h>

class AudioPlayer
{
  private:
    char a[14] = "NAV/pozos.WAV";
    char b[14] = "NAV/papie.WAV";
    char c[14] = "NAV/metro.WAV";
  
    TMRpcm tmrpcm;
    int randomVoicesCount;
    void PlayNumber(int number);
  public:
    AudioPlayer(int speakerPin, int randomVoicesCount);
    void PlaySong(char* songName);
    void PlayRandomVoice();
    void PlayDistanceLeft(int popeMeters);
};
