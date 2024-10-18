/*
 * Test05-FND.c
 *
 * Created: 2024-10-16 오후 3:12:29
 * Author : user
 */ 
#define F_CPU 16000000
#define FND_TYPE_CATHOD
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define CDDR	DDRB
#define CPORT	PORTB
#define IDDR	DDRA
#define IPORT	PORTA
unsigned char img[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67 };  // 0123456789
char data[5];// = { 1,2,3,4 };  // 1234
volatile int Mode = 0; // 0:Ready, 1:up-Count, 2:Stop, ...

int digit(int num)	// num 변수를 1000,100,10,1 자릿수 추출하여 data[] 배열에 저장
{
	if(num > 9999) return 0;	// 인수 유효성 Check
	data[3] = num % 10;			// 1
	data[2] = (num / 10) % 10;	// 10
	data[1] = (num / 100) % 10;	// 100
	data[0] = num / 1000;		// 1000
	return 1;
}
int i;
int tcnt = 0, dp = 1;
ISR(TIMER2_OVF_vect)	// FND refresh
{
	if(++tcnt > 2)
	{
		tcnt = 0;
		for(i = 0; i < 4; i++)
		{
#ifdef FND_TYPE_CATHOD
			if(i == dp) // 점 찍을 자리
			{				
				CPORT = ~_BV(i); IPORT = img[data[i]] | 0x80; _delay_ms(5);				
			}
			else
			{
				CPORT = ~_BV(i); IPORT = img[data[i]]; _delay_ms(5);				
			}
#else
			if(i == dp)
			{
				CPORT = _BV(i);	IPORT = ~(img[data[i]] | 0x80); _delay_ms(5);				
			}
			else
			{
				CPORT = _BV(i);	IPORT = ~img[data[i]]; _delay_ms(5);
			}
#endif
		}
		_delay_ms(5);
	}
}
volatile int tick = 0;
int sTick = 0;
ISR(TIMER0_COMP_vect)
{
	tick++;
	TCNT0 = 0;
}
ISR(INT0_vect)
{
	switch(++Mode)
	{
		case 0:
		case 1:			//  Start up-count
			tick = 0; 
			break;
		case 2:			//  Stop
			sTick=  tick;
			break;
		default:		//  Mode > 2
			tick = sTick = 0;
			Mode = 0;
	}
}
int main(void)
{	
	// Timer0: 100ms stop-watch,  timer2: FND refresh
	TIMSK |= 0x02; // OCIE0
	TIMSK |= 0x40; // 0b 01xx xxxx  TOIE2
	TCCR0 |= 0x07; // 분주비 110:256, 111:1024
	TCCR2 |= 0x04; // 분주비 101:1024, 100:256 : (1/16M) * 256 * 1024 = 0.016(sec)
	OCR0 = 42;    // (1/16M) * 84 * 1024 = 0.005376 == 0.01 (~= 10ms)
	
	// Ext-Intr : Mode change 0:Ready, 1:upCount, 2:Stop, ...
	EIMSK |= 0x01;	// D0 pin, EINT0
	EICRA |= 0x03;

	CDDR |= 0x0F;	// 하위 4bit를 출력으로 설정
	IDDR |= 0xFF;	// 8bit 전체를 출력으로 설정
    /* Replace with your application code */
	
	//CPORT = 0x0F;	// 모든 자리수 선택
	//IPORT = ~0xFF;	// 전체 세그먼트 ON ---> [8.]
	
	sei();
	int num = 0;
	digit(num);
	StandBy();
    while (1) 
    {
		switch(Mode)
		{
			case 0:	// Ready
				digit(0);
				break;
			case 1:	// Up-Count
				digit(tick);
				break;
			case 2:	// Stop
				digit(sTick);
				break;
			default:
				break;
		}
		/*for(num = 0; num < 10000; num++)
		{
			digit(num);			
			_delay_ms(100);
		}*/
    }
}

