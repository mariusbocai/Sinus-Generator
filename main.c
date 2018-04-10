#include"LPC214x.h"

int counter;
const int arraya[62] = {1,3,10,22,39,60,86,116,150,187,228,271,316,364,412,512,562,612,660,708,753,796,837,874,908,938,964,985,1002,1014,1021,1023,1021,1014,1002,985,964,938,908,874,837,796,753,708,660,612,562,512,412,364,316,271,228,187,150,116,86,60,39,22,10,3};

__irq void isr_timer(void)
{
	counter++;
	if(counter == 62) counter=0;
	DACR = (arraya[counter]<<6);
	T0IR = 0x1;				 //to reset interrupt flag
	VICVectAddr = 0x0;
}

int main(void)
{
	counter = 0;
	VICIntSelect = 0x00;	//TIMER0 interrupt is IRQ!!! (top priority)
	VICVectAddr0 = (unsigned)isr_timer;
	VICVectCntl0 = 0x24;
	VICIntEnable = 0x10;	//enable TIMER0 interrupt
	//setting TIMER0
	T0CTCR = 0x00;	  //timer mode selected
	T0MCR = 0x3;   //interrupt on match, timer is reset, NOT STOPPED!
	T0PR = 0x1;		//prescaler set to divide PCLK by 2
	T0MR0 = 0x10;	 //Match0 set to value 3A
	T0TCR = 0x1;	//enable timer!!!
	//set up DAC
	PINSEL1 = 0x80000;	//P0.25 is Aout
	for(;;)
	{
		counter = counter;
	}
}
