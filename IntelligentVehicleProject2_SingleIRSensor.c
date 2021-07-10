#include <reg52.h>
#include <intrins.h>

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

void Delay100us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 43;
	while (--i);
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

//循迹
void traction()
{
	if(IR1==1/*&&IR2==0*/)
		gofront();
	else if(IR1==0/*&&IR2==0*/)
		turnright();
	/*else if(IR1==0&&IR2==1)
		turnleft();
	else
		stop();*/
}

void main()
{
	while(1)
	{
		traction();
		Delay100us();
	}
}
