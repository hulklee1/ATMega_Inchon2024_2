/*
 * MyLib.c
 *
 * Created: 2024-10-11 오후 2:38:20
 *  Author: user
 */ 
#include <avr/io.h>

int TestBit(char pin, char mask)	// PINx 레지스터의 값의 mask bit가 0인지 1인지 판별
{
	if((pin & mask) != 0) return 1;
	return 0;
}

void StandBy()	// PG4 pin으로 프로그램 시작 스위치 연결
{
	DDRG &= ~0x10;	// PG4 : 입력으로 설정
	PORTG |= 0x10;	// PG4 : Pull-Up

	while(!TestBit(PING, 0x10));
	while(TestBit(PING, 0x10));
	/*
	while(1); //  PINg0의 초기값이 1(open)임을 가정,	무한 loop until Pin == 1	
	{		
		if(TestBit(PING, 0x10)) break;
	}		
	while(1)
	{	
		if(!TestBit(PING, 0x10)) break;
		//if((PING & 0x10) == 0) break;
	}	*/
}