#define F_CPU 16000000UL  // 16 MHz
#include <avr/io.h>  // AVR 기본 헤더
#include <util/delay.h>
//  SW : PG3, Input
// LED : PG4, Output
char *PT = &PORTF;
char *DD = &DDRF;
int Check()
{
	char v = *PT & 0x08;	// v = G그룹 3번 bit의 값
	if(v == 0)
	{
		*PT |= 0x01;
		 return 1;	// Pushed !!!
	}
	*PT &= ~0x01;
	return 0;
}
int main(void)
{
	//DDRF |= 0x80;
	*DD |= 0x11;   // xxxx xxxx ==> xxx1 xxxx: 1=출력
	*DD &= ~0x08;  // xxxx xxxx ==> xxxx 0xxx: 0=입력
    
	char mode = 0;  // mode = 0 : disable,  mode = 1 : active
	//char v = 1;
	while(1)	// loop until SW press
	{
		if(Check() == 1) { mode = 1; break; }
	}
	while (1) 
    {
		if(Check() == 1) // pushed
		{
			if(mode == 0)	mode = 1;
			else			mode = 0;
			_delay_ms(200);
		}
		if(mode == 1)
		{
			*PT |= 0x10;  // 해당 bit ON
			_delay_ms(100);
			*PT &= ~0x10; // 해당 bit OFF
		}
		_delay_ms(100);
    }
}

