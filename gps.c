#include <reg51.h>
#include <lcd.h>

#define gpsArraySize 50
#define latitudeArraySize 10
#define longitudeArraySize 10

int index;
int latitudeValue;
int longitudeValue;

void gpsIntialize(void);
	
unsigned char gpsArray[gpsArraySize];
unsigned char latitudeArray[latitudeArraySize];
unsigned char longitudeArray[longitudeArraySize];

void main(void)
{
	lcdStart();
	while(1)
	{
		gpsIntialize();
	}
}


void gpsIntialize(void)
{
	serialInitialize();
	check:
	while(RI==0);
	RI=0;
	
	if(SBUF!='$') // Checking if the first character is $
	{
		goto check;
	}
	longitudeValue=17,latitudeValue=29; // intializing longitude and latitude values
	
	for(index=0;index<gpsArraySize;index++) //Storing the recieved datain gpsArray array
	{
		while(RI==0);
		RI=0;
		gpsArray[index]=SBUF;
	}
	
	if(gpsArray[0]=='G' && gpsArray[1]=='P' && gpsArray[2]=='G' && gpsArray[3]=='G' && gpsArray[4]=='A')
	{
		for(index=0;index<longitudeArraySize-1;index++)
		{
			longitudeArray[index]=gpsArray[longitudeValue];
			longitudeValue++;
		}
		longitudeArray[index]='\0';
			
		for(index=0;index<latitudeArraySize-1;index++)
		{
			latitudeArray[index]=gpsArray[latitudeValue];
			latitudeValue++;
		}
		latitudeArray[index]='\0';

		delayMs(1);
			
		lcdClear();
		lcdCursorPosition(0,0);
		lcdString("Lon: ");
		lcdString(longitudeArray);
		lcdCursorPosition(1,0);
		lcdString("Lat: ");
		lcdString(latitudeArray);
	}
}