#include "MySD.h"

MySD::MySD(int sdPin) :
	sdPin(sdPin)
{
	digitalWrite(7, HIGH);
	//pinMode(sdPin, OUTPUT);
	//digitalWrite(sdPin, LOW);
	while (!SD.begin(sdPin))
	{
		digitalWrite(13, HIGH);
		delay(100);
		digitalWrite(13, LOW);
		//Serial.println(":((((");

		delay(900);
	}

	digitalWrite(13, HIGH);
	//digitalWrite(sdPin, HIGH);

	//PrintDirectory("/");
	//ToogleSPIDevice(SD_PIN, false);
}

File MySD::OpenFile(char* fileName)
{
	//digitalWrite(sdPin, LOW);
	return SD.open(fileName, FILE_WRITE);
}

void MySD::CloseFile(File file)
{
	file.close();
	//digitalWrite(sdPin, HIGH);
	digitalWrite(7, LOW);
}