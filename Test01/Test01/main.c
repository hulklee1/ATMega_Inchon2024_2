#include <avr/io.h>  // AVR 기본 헤더
// LED Port : PG4
int main(void)
{
    /* Replace with your application code */
	//printf("Hello World!");
	DDRG |= 0x10;  // xxxx xxxx ==> xxx1 xxxx: 1=출력  0=입력 
    while (1) 
    {
		PORTG |= 0x10;
    }
}

