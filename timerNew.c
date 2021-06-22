// Generate Clock pulse of 1kHz using timer in 8051
#include<reg51.h>

// fslave = 1kHz
// tslave = 1/fslave = 1ms ----- means Ton = 0.5ms
// fsource = 11.0592 mHz
// prescaling = 12
// ftimer = fsource/prescaling = 11.0592/12 = 921.6 kHz
// Ttimer = 1/921.6 kHz = 1.085 microSec
// No. of Pulses = Ton/Ttimer = 461 pulses

sbit led = P1^0; // setting led pin port

void timerDelay()
{
	TR1 = 1; // Timer run on
	// for 16 bit (FFFF-461 = FE32)
	// setting FE to TH and 32 to 32
	TH1 = 0xFE;	
	TL1 = 0x32;

	// Running the loop continously till the overflow flag is set to 1 
	// and breaks loop once overflow flag is set to 1 by the carry bit
	while(TF1 == 0)
	{
	}
	
	TR1 = 0; // Timer off
	TF1 = 0;	// Overflow flag is set to 0 for next iteration
}

void main()
{
	// setting TMOD...0x00 - Mode0, 0x01 - Mode1, 0x10 - Mode2, 0x11 - Mode3
	TMOD = 0x01;		// Setting 16 bit (ie., TMOD = Mode1)
	while(1)
	{
		led =~led;
		timerDelay();
	}
}
