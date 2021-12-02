#include "head_file.h"

extern int X, Y, H1, H2, H3, H4;
#define dianji1 PCout(6)
#define dianji2 PCout(7)
#define dianji3 PCout(8)
#define dianji4 PCout(9)                  //�ĸ�������,��������ż������

int pwm_dianji1=0, pwm_dianji2=0, pwm_dianji3=0, pwm_dianji4=0;
u16 ServoPitch, ServoYaw,
	ServoArm ,ServoHand,
	launch_pwm=360;		
//���ߵ��������ͷ�������������ͷ������,����װ�õ��

u16 timer=0;


void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
		
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_All;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
		
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		timer++;
		
		if(timer == 2000)
			timer = 0;
		
		if(timer < pwm_dianji1)
			dianji1 = 1;				
		else if(timer >= pwm_dianji1)
			dianji1 = 0;		
		
		if(timer < pwm_dianji2)
			dianji2 = 1;
		else if(timer >= pwm_dianji2)
			dianji2 = 0;
		
		if(timer < pwm_dianji3)
			dianji3 = 1;
		else if(timer >= pwm_dianji3)
			dianji3 = 0;
		
		if(timer < pwm_dianji4)
			dianji4 = 1;
		else if(timer >= pwm_dianji4)
			dianji4 = 0;	
		
		if(timer < ServoPitch)		
			PCout(4) = 1;
		else if(timer > ServoPitch)
			PCout(4) = 0;
		
		if(timer < ServoYaw)		
			PCout(5) = 1;
		else if(timer > ServoYaw)
			PCout(5) = 0;
		
		if(timer < ServoArm)		
			PCout(2) = 1;
		else if(timer > ServoArm)
			PCout(2) = 0;
		
		if(timer < ServoHand)		
			PCout(3) = 1;
		else if(timer > ServoHand)
			PCout(3) = 0;
		
		if(timer < launch_pwm)		
		{PFout(9) = 1;PFout(8) = 0;}
		else if(timer > launch_pwm)
		{PFout(9) = 0;PFout(8) = 0;}
		
	}
	TIM_ClearITPendingBit(TIM3 ,TIM_IT_Update);  //����жϱ�־λ
}


