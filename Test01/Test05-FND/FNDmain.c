/*
 * Test05-FND.c
 *
 * Created: 2024-10-16 오후 3:12:29
 * Author : user
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/delay.h>

#define CDDR	DDRB
#define CPORT	PORTB
#define IDDR	DDRA
#define IPORT	PORTA
unsigned char img[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67 };  // 0123456789
char data[] = { 1,2,3,4 };  // 1234
int main(void)
{	
	StandBy();
	CDDR |= 0x0F;	// 하위 4bit를 출력으로 설정
	IDDR |= 0xFF;	// 8bit 전체를 출력으로 설정
    /* Replace with your application code */
	
	CPORT = 0x0F;	// 모든 자리수 선택
	IPORT = ~0xFF;	// 전체 세그먼트 ON ---> [8.]
    while (1) 
    {
		for(int i = 0; i < 4; i++)
		{
			CPORT = _BV(i);//1 << i; 
			//for(int j = 0; j < 4; j++)
			{
				IPORT = ~img[data[i]];			
				_delay_ms(5);
			}			
		}			
    }
}

