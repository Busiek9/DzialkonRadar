#pragma once
#include <SD.h>
#include <SPI.h>

class MySD
{
  private:
    int sdPin;
  public:
    MySD(int sdPin);
    File OpenFile(char* fileName);
    void CloseFile(File file);
};
