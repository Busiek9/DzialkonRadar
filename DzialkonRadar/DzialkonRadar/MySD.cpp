#include "MySD.h"

MySD::MySD(int sdPin) :
	sdPin(sdPin)
{
	while (!SD.begin(sdPin))
	{
		delay(900);
	}
}

File MySD::OpenFile(char* fileName)
{
	return SD.open(fileName, FILE_WRITE);
}

void MySD::CloseFile(File file)
{
	file.close();
}
