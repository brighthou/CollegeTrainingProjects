/**
 * PNP三极管驱动四位共阳极数码管显示DS18B20数字温度传感器指示温度
 *
 * 电路使用面包板电路
 * 
 * MCU选型: STC89C52RC
 * 
 * 开发环境: Keil UV2
 *
 * @description 通电后，温度传感器复位，初始化后读取温度码，经转换后在数码管上显示
 * @author Hou Liang <me@houliang.me>
 * @date 2019-7-2
 * @version 1.3
 */

#include<reg52.h>

#define DataPort P0
#define SelectPort P2

sbit DS=P1^3;

bit ReadTempFlag;

unsigned char code DataCode[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x60,0x90};
unsigned char code SelectCode[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
unsigned char TempData[8];

void Display(unsigned char FirstBit,unsigned char Num);
void Init_Timer0(void);

void DelayUs2x(unsigned char t)
{   
 while(--t);
}

void DelayMs(unsigned char t)
{
	while(t--)
	{
		DelayUs2x(245);
		DelayUs2x(245);
	}
}

bit Init_DS18B20(void)
{
	bit dat=0;
	DS = 1;
	DelayUs2x(5);
	DS = 0;
	DelayUs2x(200);
	DelayUs2x(200);
	DS = 1;
	DelayUs2x(50);
	dat=DS;
	DelayUs2x(25);
	return dat;
}

unsigned char ReadChar(void)
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{
		DS = 0; 
		dat>>=1;
		DS = 1; 
		if(DS)
		dat|=0x80;
		DelayUs2x(25);
	}
	return(dat);
}

void WriteChar(unsigned char dat)
{
	unsigned char i=0;
	for (i=8; i>0; i--)
	{
		DS = 0;
		DS = dat&0x01;
		DelayUs2x(25);
		DS = 1;
		dat>>=1;
	}
	DelayUs2x(25);
}

unsigned int ReadTemperature(void)
{
	unsigned char a=0;
	unsigned int b=0;
	unsigned int t=0;
	Init_DS18B20();
	WriteChar(0xCC);
	WriteChar(0x44);
	DelayMs(10);
	Init_DS18B20();
	WriteChar(0xCC);
	WriteChar(0xBE);
	a=ReadChar();   
	b=ReadChar();   
	b<<=8;
	t=a+b;
	return(t);
}

void main (void)
{                  
	unsigned int TempH,TempL,temp;
	Init_Timer0();
	while (1)
	{
		if(ReadTempFlag==1)
		{
			ReadTempFlag=0;
			temp=ReadTemperature();
			if(temp&0x8000)
			{
				TempData[0]=0x40;
				temp=~temp;
				temp +=1;
			}
		else
			TempData[0]=0;
	
		TempH=temp>>4;
		TempL=temp&0x0F;
		TempL=TempL*6/10;
			
		if(TempH/100==0)
			TempData[0]=0;
		else
			TempData[0]=DataCode[TempH/100];
		if((TempH/100==0)&&((TempH%100)/10==0))
			TempData[1]=0;
		else
			TempData[1]=DataCode[(TempH%100)/10];
		TempData[2]=DataCode[(TempH%100)%10]|0x80;
		TempData[3]=DataCode[TempL];
		}	
	}
}

void Display(unsigned char FirstBit,unsigned char Num)
{
	static unsigned char i=0;
	DataPort=0;
	
	SelectPort=SelectCode[i+FirstBit];
	DataPort=TempData[i];
	
	i++;
	if(i==Num)
		i=0;
}

void Init_Timer0(void)
{
	TMOD |= 0x01;
	EA=1;
	ET0=1;
	TR0=1;
}

void Timer0_isr(void) interrupt 1 
{
	static unsigned int num;
	TH0=(65536-2000)/256;
	TL0=(65536-2000)%256;
	
	Display(0,4);
	num++;
	if(num==300)
	{
		num=0;
		ReadTempFlag=1;
	}
}
