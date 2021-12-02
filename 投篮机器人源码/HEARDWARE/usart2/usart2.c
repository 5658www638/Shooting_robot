#include "head_file.h"

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////���ļ�Ϊ��ݮ���뵥Ƭ��ͨ�ŵ�Э�飬�����޸ģ�����////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


u8 res, flag=0, CheckFlag = 0;
u16 Position = 0;
int X,Y,HandX=137,HandY=82,BallX=153,BallY=101;	//��ݮ�ɷ��͹�����������Ϣ��ͨ������2��ֵ��X��Y
char ResData[40];			//���ջ�������
extern u16 step;

void MY_USART2_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//����ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//IO��ʹ��
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);//����
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
		    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//IO�ڳ�ʼ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=115200;//���ڳ�ʼ��
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART2,&USART_InitStructure);
		
	USART_Cmd(USART2,ENABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;//�жϳ�ʼ��
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
}


//////////////////////////////////////////////////////////////////////////////////////
void Usart2SendByte(char byte)//����һ���ֽ�
{
	USART2->SR; 
	USART_SendData(USART2, (uint8_t) byte);
	while( USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);	
}


void SendCommand(u16 i)	//��������ݮ�ɵ�ָ��
{
	u16 j;
	u8 
	StarSand[3] = "<K>",	//������ݮ��λ�ú��������ݵķ���
	StopSend[3] = "<S>",	//�ر���ݮ��λ�ú��������ݵķ���
	Red[3] = "<R>",			//�л���ֵ����ɫ
	Blue[3] = "<B>",		//�л���ֵ����ɫ
	Green[3] = "<G>",		//�л���ֵ����ɫ
	Pink[3] = "<P>",		//�л���ֵ����ɫ
	Edge[3] = "<E>",		//�л��л������ͱ�Ե��ߵ�ָ��
	Center[3] = "<C>",		//�л��л�������Բ��ָ��
	JAW_POS[9] = "<JAW_POS=",
	CK_B[6] = "<CK=",
	TB_EN[7] = "<TB_EN>",
	TB_DS[7] = "<TB_DS>";
//	StarSandY[3] = "<Y>";	//������ݮ��λ�����������ݵķ���
	
	switch (i)
	{
		case star_send:
		{
			for(j = 0;j<=2;j++)
				{Usart2SendByte(StarSand[j]);}
			break;
		}
		case stop_send:
		{
			for(j = 0;j<=2;j++)
				{Usart2SendByte(StopSend[j]);}
			break;
		}
		case red:
		{
			led_r = 0;led_g = 1;led_b = 1;
			for(j = 0;j<=2;j++)
				{Usart2SendByte(Red[j]);}
			break;
		}
		case blue:
		{
			led_r = 1;led_g = 1;led_b = 0;
			for(j = 0;j<=2;j++)
				{Usart2SendByte(Blue[j]);}
			break;
		}
		case green:
		{
			led_r = 1;led_g = 0;led_b = 1;
			for(j = 0;j<=2;j++)
				{Usart2SendByte(Green[j]);}
			break;
		}
		case pink:
		{
			led_r = 1;led_g = 1;led_b = 1;
			for(j = 0;j<=2;j++)
				{Usart2SendByte(Pink[j]);}
			break;
		}
		case edge:
		{
			for(j = 0;j<=2;j++)
				{Usart2SendByte(Edge[j]);}
			break;
		}
		case center:
		{
			for(j = 0;j<=2;j++)
				{Usart2SendByte(Center[j]);}
			break;
		}
		case pos:
		{
			for(j = 0;j<=8;j++)
				{Usart2SendByte(JAW_POS[j]);}
			ChangeIntSend(HandX);
			Usart2SendByte(',');
			ChangeIntSend(HandY);
			Usart2SendByte('>');
			break;
		}
		case ck_b:
		{
			for(j = 0;j<=5;j++)
				{Usart2SendByte(CK_B[j]);}
			ChangeIntSend(BallX);
			Usart2SendByte(',');
			ChangeIntSend(BallY);
			Usart2SendByte('>');
			break;
		}
		case tb_en:
		{
			for(j = 0;j<=6;j++)
				{Usart2SendByte(TB_EN[j]);}
			break;
		}
		case tb_ds:
		{
			for(j = 0;j<=6;j++)
				{Usart2SendByte(TB_DS[j]);}
			break;
		}
	}
}


void Repead(u16 i)		//��Ϊ��ݮ�ɸ���Ƭ��ͨѶ�����ݶ�ʧ����������Ҫһ��ָ��Ͷ��
{						//��ʱ���Գ�һ�㣬��ò�Ҫ̫�̣�̫�̻�������ݽ��մ���Ͷ�ʧ��200ms��ʱ
	SendCommand(i);		//�ظ�5�η��ͣ�������OK
	SendCommand(i);
	SendCommand(i);
	SendCommand(i);
	SendCommand(i);
}


void ChangeIntSend(int IntSide)		//��������ת��Ϊ�ַ�����ͨ�����ڷ���
{
	unsigned int i = 0,ReadySend;
	char CharString[30];
	ReadySend = sprintf(CharString, "%d", IntSide);
	
	while(ReadySend>0)
	{
		Usart2SendByte(CharString[i]);
		ReadySend--;
		i++;
	}	
}


void ChangeDoubleSend(double DoubleSide)		//��������ת��Ϊ�ַ�����ͨ�����ڷ���
{
	unsigned int i = 0,ReadySend;
	char CharString[30];
	ReadySend = sprintf(CharString, "%f", DoubleSide);
	
	while(ReadySend>0)
	{
		Usart2SendByte(CharString[i]);
		ReadySend--;
		i++;
	}
	Usart2SendByte('\r');	
	Usart2SendByte('\n');	
}


void ReceiveWaiting(void)				//���ݶ�ȡ����
{
	if((res == '>') && (ResData[0] == '<'))	//�ж��Ƿ������ϣ������յ�֡ͷ֡β���������ϣ�flag��λ
		flag = 1;
	else flag = 0;						//��û�н��յ�����flagһֱΪ0
		
	if(flag == 0)						//flag=0����δ���������ݣ��򽫽��յ�ÿһλ�Ž����ݻ���������
	{									//�мǣ���Ƭ�������յ��������ݲ�����65535���������
		ResData[Position] = res;
		Position++;
	}
	else if(flag == 1)					//��������ϣ�������ת��Ϊ��ֵ������ֵת��Ϊ�ַ�����������λ��
	{
		switch (ResData[1]) 
		{
			case 'N' :{X = 10000,Y = 10000;Position = 0;break;}//���յ�'N'��ûĿ�꣬X��Y��Ϊ10000
			case 'X' :{X = ChangeStrRes();break;}//���յ�X����Ϊʶ���X���꣬�������ݼ�X������Ϣ
			case 'Y' :{Y = ChangeStrRes();break;}//���յ�X����Ϊʶ���X���꣬�������ݼ�X������Ϣ
			case 'T' :{CheckFlag=1;break;}
		}
	}
}	


int ChangeStrRes(void)			//�����յ��������ַ�������תΪ������ֵ
{
	unsigned int i=0, j,RealNumber;
	
	if(flag == 1)							//�������ݽ�����ϣ������ַ�������ֵ��ת��
	{
		for(j=2;j<Position;j++)				//���ջ���������λ
			ResData[j-2] = ResData[j];		
		ResData[Position-1] = 0;			//���һλ����
		ResData[Position-2] = 0;			//�����λ����
		
		RealNumber = atoi(ResData);			//�������ַ�����תΪ��������
		Position = 0;						//����ָ��λ��ָ���׵�ַ
		flag = 0;								//���ڽ��ձ�־λ����
	}		
	for(i = 0; i < 40; i ++)	//���ݻ���������
		ResData[i] = 0;
	
	return 	RealNumber;				//����ת�������ֵ
}


void USART2_IRQHandler(void)//�����жϷ�����
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE))
	{
		led_2 = 0;
		led_3 = !led_3;
		res = USART_ReceiveData(USART2);
		ReceiveWaiting();
	}
}



 




