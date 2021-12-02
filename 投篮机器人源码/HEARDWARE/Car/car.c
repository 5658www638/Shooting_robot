#include "head_file.h"


extern u16 X,launch_pwm;
extern u8 dir,TRound;
extern int pwm_dianji1, pwm_dianji2, pwm_dianji3, pwm_dianji4;
extern char dirflag;
extern u16 Ball_X;

void car_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOB/Cʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOB/Cʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);
	GPIO_SetBits(GPIOF,GPIO_Pin_9);
	stop();								//��ʼ���������ֹͣ
}


void stop(void)		//ֹͣ
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);//0
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);//0  һ�ŵ��
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);//0    ���ŵ��
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);//0
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);//0  ���ŵ��
	GPIO_ResetBits(GPIOF,GPIO_Pin_5);//0     
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);//0   �ĺŵ��
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);//0 
	
	pwm_dianji1 = 0;
	pwm_dianji2 = 0;
	pwm_dianji3 = 0;
	pwm_dianji4 = 0;
}


void front(void)		//ǰƽ��
{
	GPIO_SetBits(GPIOF,GPIO_Pin_0);//1    1�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);//0

	GPIO_SetBits(GPIOF,GPIO_Pin_3);//1  2�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);//0	
    
	GPIO_SetBits(GPIOF,GPIO_Pin_4);//1
	GPIO_ResetBits(GPIOF,GPIO_Pin_5);//0   3�ŵ����ת
	
	GPIO_SetBits(GPIOF,GPIO_Pin_7);//1 
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);//0  4�ŵ����ת
}


void back(void)		//��ƽ��
{
	GPIO_SetBits(GPIOF,GPIO_Pin_1);//1    1�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);//0

	GPIO_SetBits(GPIOF,GPIO_Pin_2);//1  2�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);//0	
    
	GPIO_SetBits(GPIOF,GPIO_Pin_5);//1
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);//0   3�ŵ����ת
	
	GPIO_SetBits(GPIOF,GPIO_Pin_6);//1 
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);//0  4�ŵ����ת
}


void left(void)		//��ƽ��
{
	GPIO_SetBits(GPIOF,GPIO_Pin_1);//1    1�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);//0

	GPIO_SetBits(GPIOF,GPIO_Pin_2);//1  2�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);//0	
    
	GPIO_SetBits(GPIOF,GPIO_Pin_4);//1
	GPIO_ResetBits(GPIOF,GPIO_Pin_5);//0   3�ŵ����ת
	
	GPIO_SetBits(GPIOF,GPIO_Pin_7);//1 
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);//0  4�ŵ����ת
	
	pwm_dianji1 = 160;
	pwm_dianji2 = 160;
	pwm_dianji3 = 160;
	pwm_dianji4 = 160;
}


void right(void)	//��ƽ��
{
	GPIO_SetBits(GPIOF,GPIO_Pin_0);//1    1�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);//0

	GPIO_SetBits(GPIOF,GPIO_Pin_3);//1  2�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);//0	
    
	GPIO_SetBits(GPIOF,GPIO_Pin_5);//1
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);//0   3�ŵ����ת
	
	GPIO_SetBits(GPIOF,GPIO_Pin_6);//1 
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);//0  4�ŵ����ת
	
	pwm_dianji1 = 160;
	pwm_dianji2 = 160;
	pwm_dianji3 = 160;
	pwm_dianji4 = 160;
}


void left_front(void)
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);//1    1�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);//0

	GPIO_ResetBits(GPIOF,GPIO_Pin_3);//1  2�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);//0	
    
	GPIO_SetBits(GPIOF,GPIO_Pin_4);//1
	GPIO_ResetBits(GPIOF,GPIO_Pin_5);//0   3�ŵ����ת
	
	GPIO_SetBits(GPIOF,GPIO_Pin_7);//1 
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);//0  4�ŵ����ת
	
	pwm_dianji1 = 2000;
	pwm_dianji2 = 2000;
	pwm_dianji3 = 2000;
	pwm_dianji4 = 2000;
}


void right_front(void)
{
	GPIO_SetBits(GPIOF,GPIO_Pin_0);//1    1�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);//0

	GPIO_SetBits(GPIOF,GPIO_Pin_3);//1  2�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);//0	
    
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);//1
	GPIO_ResetBits(GPIOF,GPIO_Pin_5);//0   3�ŵ����ת
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);//1 
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);//0  4�ŵ����ת
	
	pwm_dianji1 = 2000;
	pwm_dianji2 = 2000;
	pwm_dianji3 = 2000;
	pwm_dianji4 = 2000;
}


void turnright(void)//ԭ����
{
	GPIO_SetBits(GPIOF,GPIO_Pin_1);//1    1�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);//0

	GPIO_SetBits(GPIOF,GPIO_Pin_3);//1  2�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);//0	
    
	GPIO_SetBits(GPIOF,GPIO_Pin_5);//1
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);//0   3�ŵ����ת
	
	GPIO_SetBits(GPIOF,GPIO_Pin_7);//1 
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);//0  4�ŵ����ת
	
	if(TRound == 0)
	{
		pwm_dianji1 = 450;
		pwm_dianji2 = 450;
		pwm_dianji3 = 450;
		pwm_dianji4 = 450;
	}
	else 
	{
		pwm_dianji1 = 100;
		pwm_dianji2 = 100;
		pwm_dianji3 = 100;
		pwm_dianji4 = 100;		
	}
	
}


void crossright(void)//ԭ����
{
	GPIO_SetBits(GPIOF,GPIO_Pin_1);//1    1�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);//0

	GPIO_ResetBits(GPIOF,GPIO_Pin_3);//1  2�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);//0	
    
	GPIO_SetBits(GPIOF,GPIO_Pin_5);//1
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);//0   3�ŵ����ת
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);//1 
	GPIO_ResetBits(GPIOF,GPIO_Pin_6);//0  4�ŵ����ת
	
		pwm_dianji1 = 1000;
		pwm_dianji2 = 1000;
		pwm_dianji3 = 1000;
		pwm_dianji4 = 1000;

}





void turnleft(void)//ԭ����
{
	GPIO_SetBits(GPIOF,GPIO_Pin_0);//1    1�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);//0

	GPIO_SetBits(GPIOF,GPIO_Pin_2);//1  2�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);//0	+

	GPIO_SetBits(GPIOF,GPIO_Pin_4);//1
	GPIO_ResetBits(GPIOF,GPIO_Pin_5);//0   3�ŵ����ת
	
	GPIO_SetBits(GPIOF,GPIO_Pin_6);//1 
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);//0  4�ŵ����ת
	
	if(TRound == 0)
	{
		pwm_dianji1 = 450;
		pwm_dianji2 = 450;
		pwm_dianji3 = 450;
		pwm_dianji4 = 450;
	}
	else 
	{
		pwm_dianji1 = 100;
		pwm_dianji2 = 100;
		pwm_dianji3 = 100;
		pwm_dianji4 = 100;		
	}
	
}


void crossleft(void)//ԭ����
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);//1    1�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);//0

	GPIO_SetBits(GPIOF,GPIO_Pin_2);//1  2�ŵ����ת
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);//0	+

	GPIO_ResetBits(GPIOF,GPIO_Pin_4);//1
	GPIO_ResetBits(GPIOF,GPIO_Pin_5);//0   3�ŵ����ת
	
	GPIO_SetBits(GPIOF,GPIO_Pin_6);//1 
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);//0  4�ŵ����ת

		pwm_dianji1 = 1000;
		pwm_dianji2 = 1000;
		pwm_dianji3 = 1000;
		pwm_dianji4 = 1000;	
}


void car_no_adjust(void)	//��PID
{
	pwm_dianji1 = 160;
	pwm_dianji2 = 160;
	pwm_dianji3 = 160;
	pwm_dianji4 = 160;
}

void avoid_speed(void)	//��PID
{
	pwm_dianji1 = 2000;
	pwm_dianji2 = 2000;
	pwm_dianji3 = 2000;
	pwm_dianji4 = 2000;
}


void car_adjust(void)		//��������ֱ�ߣ�PID�㷨
{
	u16 Target = Ball_X;		//Target������ͷ������м䴹�ߣ����ڶ���
	int PWM, PWM1,PWM2;
	
	PWM = PID_Realize(X, Target);		
	
	if(dirflag == 0)
	{
		PWM1 = 450 + PWM;		//�����10��35�ǰ��ճ�����ֱ�ߵ�ʱ�����ı�ƫ��ƫ���ٵ��ġ�
		PWM2 = 450 - PWM - 55;		//��4 ��55
	}
		
	else if(dirflag == 1)
	{
		PWM1 = 160 - PWM;
		PWM2 = 160 + PWM + 55;
	}
	
	else if(dirflag == 6)
	{
		PWM1 = 120 + PWM;
		PWM2 = 120 - PWM + 55;
	}
	
	else if(dirflag == 2)
	{
		PWM1 = 1500 - PWM;		//�����10��35�ǰ��ճ�����ֱ�ߵ�ʱ�����ı�ƫ��ƫ���ٵ��ġ�
		PWM2 = 1500 + PWM + 200;		//��4 ��55
	}
		
	else if(dirflag == 3)
	{
		PWM1 = 200 + 15 * PWM;
		PWM2 = 200 - 20 * PWM - 55;
	}
	
	else if(dirflag == 4)
	{
		PWM1 = 300;		//�����10��35�ǰ��ճ�����ֱ�ߵ�ʱ�����ı�ƫ��ƫ���ٵ��ġ�
		PWM2 = 300;		//��4 ��55
	}
		
	else if(dirflag == 5)
	{
		PWM1 = 200;
		PWM2 = 200;
	}
//////////////////////////////////////////////////////////////////
//////////////////�޶����PWM/////////////////////////////////////
	if(PWM1 > 2000)
		PWM1 = 2000;
	else if(PWM1 <= 0)
		PWM1 = 0;
	if(PWM2 > 2000)
		PWM2 = 2000;
	else if(PWM2 <= 0)
		PWM2 = 0;
	
	pwm_dianji1 = PWM1;
	pwm_dianji3 = PWM1;
	pwm_dianji2 = PWM2;
	pwm_dianji4 = PWM2;
}


void Launch(int i)
{
	if(i <= 0)
		i = 0;
	else if(i >= 2000)
		i = 2000;
	else launch_pwm = i; 
}


