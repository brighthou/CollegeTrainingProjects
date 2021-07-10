#include <reg52.h>
#include <intrins.h>
#include <math.h>
#define uchar unsigned char
#define uint  unsigned int

/*LM298N真值表

	IN1		IN2		ENA		OUT1	IN3		IN4		ENB		OUT2
	X		X		0		STOP	X		X		0		STOP
	1		0		1		CLW		1		0		1		CLW
	0		1		1		ANT		0		1		1		ANT
	0		0		0		STOP	0		0		0		STOP
	1		1		0		STOP	1		1		0		STOP

*/

//定义左右电机
sbit IN1=P0^0;
sbit IN2=P0^1;

sbit IN3=P0^2;
sbit IN4=P0^3;

//定义红外传感器
sbit IR1=P1^5;


//延时5秒//@11.0592MHz
void Delay5000ms()
{
	unsigned char i, j, k;

	_nop_();
	i = 36;
	j = 5;
	k = 211;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//延时3秒//@11.0592MHz
void Delay3000ms()
{
	unsigned char i, j, k;

	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//控制电机动作
void stop()
{
	IN1=0;
	IN2=0;
	IN3=0;
	IN4=0;
}

//假定
void gofront()
{
	IN1=1;
	IN2=0;
	IN3=1;
	IN4=0;
}

void goback()
{
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=1;
}

void turnleft()
{
	IN1=1;
	IN2=0;
	IN3=0;
	IN4=1;
}

void turnright()
{
	IN1=0;
	IN2=1;
	IN3=1;
	IN4=0;
}

void main()
{
	while(1)
	{
		stop();
		gofront();
		Delay5000ms();
		stop();
		turnleft();
		Delay3000ms();
		stop();
		gofront();
		Delay5000ms();
		stop();
		turnright();
		Delay3000ms();
	}
}
