#include "dataStructure.h"
using namespace Math;
class capture
{
	unsigned short pX, pY;
	fVec deadZone;

public:
	capture()
	{

	}
	void setup(unsigned short pX, unsigned short pY, fVec deadZone = fVec(0, 0))
	{
		this->pX = pX;
		this->pY = pY;
		if (deadZone.x != 0 && deadZone.y != 0)
			this->deadZone = deadZone;
		else
		{
			this->deadZone.x = analogRead(pX) - 512;
			this->deadZone.y = analogRead(pY) - 512;
		}
		this->deadZone *= -1;
	}
	fVec getData()
	{
		fVec rawData = fVec(analogRead(pX), analogRead(pY));
		rawData += deadZone;
		rawData = ((rawData - 512) / 512.0);
		/*
		if(rawData.magnitude() > 0.20f)
		rawData.normalize();
		else
		rawData = fVec(0, 0);
		*/
		//Serial.println(String(rawData.x) + " - " + String(rawData.y));
		//Serial.print(String(rawData.x) + " - " + String(rawData.y));
		//Serial.println("\t##" + String(deadZone.x) + " - " + String(deadZone.y));
		return rawData;
	}
};
