#include "head_file.h"

u8 KeyFlag4=1,KeyFlag5=1,KeyFlag6=1,KeyFlag7=1;

/**************************************************************************************
������ϳ���
***************************************************************************************/
void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void TIM4_IRQHandler()//�жϷ�����
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==!RESET)//�ж�Ϊʲô�ж�
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0)
			KeyFlag4=0;
		else KeyFlag4=1;
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == 0)
			KeyFlag5=0;
		else KeyFlag5=1;
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == 0)
			KeyFlag6=0;
		else KeyFlag6=1;
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) == 0)
			KeyFlag7=0;
		else KeyFlag7=1;
		
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//�����־λ
	}
}




