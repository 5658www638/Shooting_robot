#include "head_file.h"


//174�����ſ�
extern u16 ServoPitch, ServoYaw, ServoArm, ServoHand;
u8 CamYawFlag = 0;


void camera_up(void)
{
	ServoPitch = 191;		//����������ͷ�׶ˣ�������ͷ̧ͷ��
}

void camera_more_up(void)
{
	ServoPitch = 176;		//����������ͷ�׶ˣ�������ͷ̧ͷ��
}


void camera_pink_up(void)
{
	ServoPitch = 176;		//����������ͷ�׶ˣ�������ͷ̧ͷ��
}


void camera_down(void)
{
	ServoPitch = 200;		//����������ͷ���ˣ�������ͷ��ͷ��
}


void camera_front(void)
{
	ServoYaw = 208;		//����ͷǰ��
}


void camera_back(void)
{
	ServoYaw = 87;		//����ͷ��	(��û��)
}


void camera_left(void)
{
	ServoYaw = 220;		//����ͷ��
}

void arm_up(void)//�����ֱ�
{
	ServoArm = 100;
}

void arm_down(void)//�����ֱ�
{
	ServoArm = 204;
}

void HandOpen(void)//�򿪻�еצ
{
	ServoHand = 90;
}

void HandClose(void)//���ϻ�еצ
{
	ServoHand = 53;//72
}

void HandPut(void)//�򿪻�еצ
{
	ServoHand = 90;

}

