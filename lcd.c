#include <reg51.h>
#include <lcd.h>
sfr lcdBus = 0xA0;
sbit RS = P3^6;
sbit EN = P3^7;

void lcdCommand(char com)
{
	RS=0;
	lcdBus=com;
	EN=1;
	delayMs(1);
	EN=0;
	delayMs(1);
}

void lcdData(char dat)
{
	RS=1;
	lcdBus=dat;
	EN=1;
	delayMs(1);
	EN=0;
	delayMs(1);
}

void lcdIntialize(void)
{
	lcdCommand(0x38); // 8bit mode
	lcdCommand(0x0C); // Display on, cursor blinking
	lcdCommand(0x01); // Clear display
	lcdCommand(0x80); // Force cursor to the begining of first line
}
void lcdString(char *str)
{
	while(*str!='\0')
	{
		lcdData(*str++);
	}
}
void lcdClear(void)
{
	lcdCommand(0x01);
}
void delayMs(unsigned int x)
{
// unsigned int a,b;
// for(a=0;a<x;a++)
// {
//		for(b=0;b<1257;b++);  // for 1ms delay 
// }
 
	int i;
	for(i=0;i<x;i++)
	{
		TMOD=0x01; // 0000 0001
		TH0=0xFE;
		TL0=0x67;
		TCON=0x10; // 0001 0000
		while(TF0==0);
		TR0=0;
		TF0=0;
	}

} 

void lcdCursorPosition(unsigned int row, unsigned int pos)
{
	if(row==0)
	{
		pos=0x80+pos;
		lcdCommand(pos);
	}
	if(row==1)
	{
		pos=0xC0+pos;
		lcdCommand(pos);
	}
}

void lcdStart(void)
{
	int m;  
	lcdIntialize();
	lcdString("Please Wait...");
	delayMs(2000);
	lcdClear();
	lcdCursorPosition(0,0);
	lcdString("Waiting for GPS");
	delayMs(2000);
	lcdClear();
	lcdCursorPosition(0,0);
	lcdString("Accuring Signal");
	lcdCursorPosition(1,0);
	for(m=0;m<16;m++)
	{
		lcdString(".");
		delayMs(1000);
	}
	lcdClear();
	lcdCursorPosition(0,0);
	lcdString("GPS Intialized");
	delayMs(2000);
	lcdClear();
}
void serialInitialize(void)
{
	SCON=0x50;
	TMOD=0x20;
	TH1=0xFD;
	TR1=1;
}