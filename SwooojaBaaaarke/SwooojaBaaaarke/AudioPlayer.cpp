#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(int speakerPin, int randomVoicesCount):
  randomVoicesCount(randomVoicesCount)
{
  // todo: tu będzie trzeba zczytać czas z zegara, żeby rzeczywiście było losowe
  srand(time(NULL));
  tmrpcm.speakerPin = speakerPin;
  tmrpcm.setVolume(5);
}

void AudioPlayer::PlaySong(char* songName)
{
  if (SD.exists(songName)) {
    tmrpcm.play(songName);
    while (tmrpcm.isPlaying())
    {
      delay(20);
    }
  }
}

void AudioPlayer::PlayRandomVoice()
{
  int random = (rand() % randomVoicesCount + 1);
  char songNameArray[11];
  sprintf(songNameArray, "RAND/%02d.WAV", random);

  PlaySong(songNameArray);
}

void AudioPlayer::PlayNumber(int number)
{
  char songNameArray[14];
  sprintf(songNameArray, "DIGIT/%d.WAV", number);
  PlaySong(songNameArray);
}

void AudioPlayer::PlayDistanceLeft(int popeMeters)
{
  int numbersToPlay[4] = {0};
  int i = 3;
  int multiplier = 1;
  do
  {
    int digit = popeMeters % 10;
    numbersToPlay[i] = digit * multiplier;
    
    // case when number finishes with 10 to 19
    if (i == 2 && digit == 1)
    {
      numbersToPlay[2] += numbersToPlay[3];
      numbersToPlay[3] = 0;
    }

    popeMeters /= 10;
    i--;
    multiplier *= 10;
  }
  while (popeMeters != 0);

  PlaySong(a);

  for (i = 0; i < 4; i++)
  {
    if (numbersToPlay[i] == 0)
    {
      continue;
    }

    PlayNumber(numbersToPlay[i]);
  }

  PlaySong(b);
  PlaySong(c);
}
