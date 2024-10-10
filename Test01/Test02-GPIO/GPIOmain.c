/*
 * Test02-GPIO.c
 *
 * Created: 2024-10-10 오전 9:36:04
 * Author : user
 */ 
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL  // 16 MHz

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define SW1	 PORTG4	// (1<<0)
#define SW2	 PORTD0
#define SW3	 PORTD1
#define LED1 PORTG1 

volatile int ival = 1000;
ISR(INT0_vect)	// 점점 느리게
{	
	
}

ISR(INT1_vect)	// 점점 빠르게
{
	
}

void StandBy()	// PG4 pin으로 프로그램 시작 스위치 연결
{
	DDRG &= ~0x10;	// PG4 : 입력으로 설정
	PORTG |= 0x10;	// PG4 : Pull-Up

	while((PING & 0x10) == 0);	// PINg0의 초기값이 1(open)임을 가정,	무한 loop until Pin == 1	
	//while(1) // 
	//{		
		//if((PING & 0x10) == 1) break;
	//}		
	while(1)
	{	
		if((PING & 0x10) == 0) break;
	}	
}

int main(void)
{
    /* Replace with your application code */
	DDRG &= ~0x0C;	// 0b 0000 1100 => 0b 1111 0011 입력 마스크
	DDRG |= 0x03;	// 0b xxxx xx11		:  출력 마스크
	
	PORTG |= _BV(LED1);   //(1<<LED1); // 0x10;	// 시작되면 LED ON, G0~G3 현상태 유지(Pull-Down)
	StandBy();
	PORTG &= ~_BV(LED1);		
	
	// Mask Register : EIMSK
	
	// Create register	: EICRA
	
	sei();
    while (1) 
    {
		//if((PING & _BV(SW2)) == 0) ival +=500;		//  G1, slower
		//else if((PING & _BV(SW3)) == 0)  //  G2, faster
		//{
			//ival -=500;
			//if(ival < 10) ival = 100;
		//}

		PORTG |= _BV(LED1);		// LED ON
		_delay_ms(ival);			// 1/1000 sec delay
		PORTG &= ~_BV(LED1);	// LED OFF
		_delay_ms(ival);
    }
}

