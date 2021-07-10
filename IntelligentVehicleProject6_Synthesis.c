#include <reg52.h>
#include <math.h>
#include <intrins.h>
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

//模式选择
sbit TRAC=P2^5;
sbit SUPS=P2^6;
sbit ALL=P2^7;

//定义红外传感器
sbit IR1=P1^7;
sbit IR2=P1^5;
sbit IR3=P1^6;
sbit IR4=P1^4;

//超声波传感器引脚定义
sbit TRIG=P2^1;
sbit ECHO=P2^0;
//sbit LED=P0^7;

//定义距离变量
float S;
uchar n;

//延时函数组
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay100us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 43;
	while (--i);
}

void Delay30us()		//@11.0592MHz
{
	unsigned char i;

	i = 11;
	while (--i);
}

void Delay70us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 29;
	while (--i);
}

void DelayUs2x(uchar t)
{   
	while(--t);
}

void DelayMs(uchar t)
{
	while(t--)
	{
	    //大致延时1mS	
		DelayUs2x(245);
	    DelayUs2x(245);
	}
}

//定时器0初始化
void TIM0init(void)
{
  TMOD|= 0x01;
  TH0=0x00;    
  TL0=0x00; 
  ET0=1;
  EA=1;
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
	if(IR1==0&&IR2==0)
	{
		if(IR3==0&&IR4==0)
			gofront();
		else if(IR3==1||IR4==1)
			turnright();
		else
			gofront();
	}
	else if(IR1==1||IR2==1)
	{
		if(IR3==0&&IR4==0)
			turnleft();
		else if(IR3==1||IR4==1)
			gofront();
		else
			gofront();
	}
	else
		gofront();
}

//超声波工作函数
void supersonic()
{
	//提供一个宽度大于20us的高电平脉冲
	TRIG=1;
	DelayUs2x(10);
	TRIG=0;
	
	//接收超声波反射信号
	while(!ECHO);
	TR1=1;
	while(ECHO);
	TR1=0;
	
	//计算距离
	S=TH1*256+TL1;
	S=S/58;
	
	//判断距离阈值，n=0时无障碍，n=1时有障碍
	if(S>=150)
		n=1;
    if(S<150)
		n=0;
	
	//定时器清零
	TH1=0;
	TL1=0;
}

main()
{
	TIM0init();
	while(1)
	{
		if(TRAC==0&&SUPS==1&&ALL==1)
		{
			traction();
			Delay100us();
		}
		else if(TRAC==1&&SUPS==0&&ALL==1)
		{
			supersonic();
			DelayMs(20);
			if(n==1)
			{
				gofront();
				Delay100us();
			}
			else
			{
				turnleft();
				Delay1000ms();
			}
		}
		else if (TRAC==1&&SUPS==1&&ALL==0)
		{
			traction();
			supersonic();
			DelayMs(20);
			if(n==1)
			{
				gofront();
				Delay100us();
			}
			else
			{
				turnleft();
				Delay1000ms();
			}
		}
		else
			stop();
	}
}
