#include "head_file.h"

/*
��Ҫ������ǣ���������û��Ŀ��ʱ�����ḳֵX,Y����10000�������ô���ֵ��Ҫ���������Ƿ�����ȷֵ
Ҳ����ʹ����Ŀ��ʱ����û��Ŀ�꣬��һֱת��ֱ������ͷ�ҵ�Ŀ��Ϊֹ

��Ҫ�޸ĵĵط���

1.����λ�õĶ���Ƕȣ���Ϊ��װ��λ�ò�̫һ����������Ҫ�����Լ���
2.��ǰ�ߺ��ߵ�λ��(��Ŀ��Ӧ���ڻ����кδ���λ��) ��X��Y
3.����ʱ���Xֵ�������е��м�ֵΪX = 160�����ǳ�ת�Ĺ��Ի������ߵĹ���Զ�򣬴ﲻ����λ��
  ���˲������޸�������������ζ���
4.PID�Ĳ���(pid.c)
5.С��ԭ����ת���ٶ�(��car.c)

������ʱ��û���룬���ӿɼӽ�ȥ

*/

extern int X, Y, H1, H2, H3, H4;
extern u8 TRound;
extern u16 Step,BallColor,launch_pwm,ServoArm,ServoPitch;
unsigned int PickFlag = 0;
extern char hand_flag;
int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�����ж����ȼ�
	MY_USART2_Init();
	car_Init();
	uart_init(115200);
	TIM3_Int_Init(10-1, 84-1);
	TIM4_Int_Init(10-1, 84-1);
	delay_init(168);
	LedInit();
	printf("ok\r\n");
	arm_up();
	HandOpen();
	Repead(star_send);	//����ʶ��λ�����ݽ��գ���Ϊ�������ݶԿ���Ӱ�첻�󣬿�����һֱ����	
	camera_front();		//����ͷǰ��
	camera_up();		//����������ͷ���ˣ�������ͷ��ͷ
	Launch(launch_pwm);
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 1)
	{
		BallColor = blue;
		led_r = 1;
		led_g = 1;
		led_b = 0;
	}
	else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 0) 
	{
		BallColor = red;
		led_r = 0;
		led_g = 1;
		led_b = 1;
	}
	delay_ms(3000);
	right_front();
	delay_ms(1500);
	stop();
	Step = 1;
/**************************************************************************************************
**************************************************************************************************/
	/////////////////////////////////////////////////////////////////////////////////	
	while(1)
	{
////		printf("X = %d Y = %d\r\n",X, Y);
/////********************************************************************************************************
////�����в����ţ�����Step1,3,5,7��Ϊ�˵����������ϰ���������ͷִ�б��β��裬�����Ǵ���һ�����¿�ʼ
////*************************************************************************************************************/	
		switch(Step)			
		{
			case 1: Step++;break;
			case 2: PickBall();break;		//ʶ���򲢼���
			case 3: Step++;break;
			case 4: MoveToGreen();break;	//ʶ����ɫ��Ե
			case 5: Step++;break; 
			case 6: OnGreenCore();break;	//ʶ����ɫ����
			case 7: Step++;break;
			case 8: SeekAndLunch();break;	//Ѱ������Ͷ��
		}		
	}
}
