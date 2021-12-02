#include "head_file.h"

int count=1000;
extern int X,Y; 
extern u16 launch_pwm, ServoArm, ServoPitch;
extern u8 CamYawFlag,CheckFlag;									//����ͷ������������־λ
extern u8 KeyFlag4,KeyFlag5,KeyFlag6,KeyFlag7;
extern int pwm_dianji1, pwm_dianji2, pwm_dianji3, pwm_dianji4;
u8 AdvoidFlag = 0, BallFlag = 0;										//������ϵı�־λ
u8 FreeFlag = 0;
u16 GoFlag = 0,Step = 1,BallColor = blue, InfraredFlag = 0, Ball_X=159;				//�����־λ��ǰ�����˱�־λ
u8 TRound = 0;											//��ת��־λ�����ڶ���У���ʱ���ٶȵ���
extern unsigned char ErrFlag;
u16 dirflag = 0;
/*************************************************************************************
*************************************************************************************/
void Avoidance(void)	//��������㷨
{
	if((KeyFlag4 == 0)&&(KeyFlag5 == 1))
	{
		AdvoidFlag = 1;
		TRound = 0;
		Step--;
		back();
		avoid_speed();
		delay_ms(500);
		crossleft();
		delay_ms(1000);
		stop();
	}
	
	else if((KeyFlag4 == 1)&&(KeyFlag5 == 0))
	{
		TRound = 0;
		AdvoidFlag = 1;
		Step--;
		back();
		avoid_speed();
		delay_ms(500);
		crossright();
		delay_ms(1000);
		stop();
	}
	
	else if((KeyFlag4 == 0)&&(KeyFlag5 == 0))
	{
		TRound = 0;
		AdvoidFlag = 1;
		Step--;
		back();
		avoid_speed();
		delay_ms(500);
		crossright();
		delay_ms(1000);
		stop();
	}
	
	else GoFlag = 0;
}


void MoveToFree(void)
{
	camera_more_up();
	delay_ms(150);
	Repead(green);		//�л���ֵ����ɫ
	Repead(center);		//ʶ��Բ��
	SetBackCore();			//����
	MoveTargetFree(229);	//����Ͷ����
	Step = 1;
}


void SetCore(void)								//�����㷨
{
	int i=0,j=0;
	AdvoidFlag = 0;
	BallFlag = 0;
	if(X > Ball_X)
	{
		while((X > Ball_X)&&(BallFlag == 0))
		{
			j ++;
			TRound = 0;
			turnright();							//��ת
			if(j == count)
			{
				i++;
				j=0;
			}
			if(i == 1000)
			{
				MoveToFree();
				BallFlag = 1;
				Step = 1;
			}
		}
		stop();
		delay_ms(150);
	
		while((X < Ball_X)&&(BallFlag == 0))
		{
			TRound = 1;
			turnleft();								//��ת
		}
		stop();
	}
	
	else if(X < Ball_X)
	{
		while((X < Ball_X)&&(BallFlag == 0))
		{
			j++;
			TRound = 0;
			turnleft();								//��ת
			if(j == count)
			{
				i++;
				j=0;
			}
			if(i == 1000)
			{
				MoveToFree();
				BallFlag = 1;
				Step = 1;
			}
		}
		stop();
		delay_ms(100);
	
		while((X > Ball_X)&&(BallFlag == 0))
		{
			TRound = 1;
			turnright();							//��ת
		}
		stop();
		delay_ms(80);
	}
	
	if(BallFlag == 1)
		BallFlag = 0;
}


void SetBackCore(void)								//�����㷨
{
	FreeFlag = 1 - FreeFlag;
	
	if(FreeFlag == 0)
	{
		while((X > 170) || (X < 130))
		{
			TRound = 0;
			turnright();							//��ת
		}
		stop();
		delay_ms(150);
		
	}
	
	else if(FreeFlag == 1)
	{
		while((X > 170) || (X < 130))
		{
			TRound = 0;
			turnleft();							//��ת
		}
		stop();
		delay_ms(150);
	}
}



void SetPinkCore(void)								//�����㷨
{
	AdvoidFlag = 0;
	if(X > 130)
	{
		while(X > 130)
		{
			TRound = 0;
			turnright();							//��ת
		}
		stop();
		delay_ms(150);
	
		while(X < 130)
		{
			TRound = 1;
			turnleft();								//��ת
		}
		stop();
	}
	
	else if(X < 130)
	{
		while(X < 130)
		{
			TRound = 0;
			turnleft();								//��ת
		}
		stop();
		delay_ms(100);
	
		while(X > 130)
		{
			TRound = 1;
			turnright();							//��ת
		}
		stop();
		delay_ms(80);
	}
}


void MoveTargetBlue(u16 target)						//�ƶ�����ɫĿ��λ��i
{
	
	AdvoidFlag = 0;
	while((Y <= target)&&(AdvoidFlag ==0)&&(Y != 10000)&&(Step == 2))							//������Ŀ��λ��(Y = i)����һֱ��ǰ�ߣ�ͬʱ��PID����
	{
		dirflag = 0;
		Avoidance();
		front();
		car_adjust();
	}
	if((Y == 10000) || (X == 10000))
		Step = 1;
	stop();
	delay_ms(200);
	while((Y > target)&&(AdvoidFlag ==0)&&(Y != 10000)&&(Step == 2))				//������Ŀ��λ��(Y = i)����һֱ��ǰ�ߣ�ͬʱ��PID����
	{
		dirflag = 1;
		Avoidance();
		back();
		car_adjust();
	}
	if((Y == 10000) || (X == 10000))
		Step = 1;
	stop();
	delay_ms(100);
	while((Y <= target)&&(AdvoidFlag ==0)&&(Y != 10000)&&(Step == 2))							//������Ŀ��λ��(Y = i)����һֱ��ǰ�ߣ�ͬʱ��PID����
	{
		dirflag = 6;
		Avoidance();
		front();
		car_adjust();
	}
	if((Y == 10000) || (X == 10000))
		Step = 1;
	stop();
	delay_ms(100);
}


void MoveTargetFree(u16 target)						//�ƶ�����ɫĿ��λ��i
{
	AdvoidFlag = 0;
	while((Y <= target)&&(AdvoidFlag ==0))			//������Ŀ��λ��(Y = i)����һֱ��ǰ�ߣ�ͬʱ��PID����
	{
		dirflag = 2;
		Avoidance();
		front();
		car_adjust();
	}
	stop();
	delay_ms(200);
}


void MoveTargetGreen(u16 target)					//�ƶ�����ɫĿ��λ��i
{
	AdvoidFlag = 0;
	while(Y <= target)								//������Ŀ��λ��(Y = i)����һֱ��ǰ�ߣ�ͬʱ��PID����
	{
		dirflag = 2;
		back();
		car_adjust();
	}
	stop();
	delay_ms(200);
}


void Check(void)				//������򣺰�ٻ�е�֣������ڷ�Χ�ڣ���ץ���������ڣ���ûץ��������ץ��
{
	TRound = 0;					//���ùܣ�����ߴ���ı�־λ
	Repead(tb_ds);				//�رո���
	arm_up();
	delay_ms(200);
	ServoPitch = 220;
	delay_ms(1000);
	if((X < 185) && (X > 125) && (Y < 149) && (Y > 89))		//У�����Ƿ���Ŀ��λ��
		Step = 3;				//��ȷ��ִ����һ��
	else 
	{
		right_front();
		delay_ms(500);
		TRound = 0;
		turnright();
		delay_ms(300);
		stop();
		ServoArm = 180;
		delay_ms(300);
		HandOpen();
		delay_ms(200);
		arm_up();
		Step = 1;				//��������ץ��
	}
	Repead(tb_en);				//��������
}


void BallCatched(void)			//ִ��ץ�����
{
	arm_down();
	delay_ms(900);
	HandClose();
	delay_ms(130);
	Check();
	arm_up();
}


void TranslateHorizontal(void)		//ƽ����Ŀ��λ�ã�����ƽ�ƶ���
{
	if(X < 150)						//��һ��ʼ���ڻ������Ҷ�
	{
		while(X < 150)				//������Ŀ��λ������ƽ��
		{
			right();
		}
		stop();
		delay_ms(100);
		while(X > 150)				//�ٴ�ƽ�ƶ��У���ֹ�Թ�ͷ
		{
			left();
		}
		stop();
		delay_ms(80);
	}
	
	else if(X > 150)				//��һ��ʼ���ڻ��������
	{
		while(X > 150)				//������Ŀ��λ������ƽ��
		{
			left();
		}
		stop();
		delay_ms(100);
		while(X < 150)				//�ٴ�ƽ�ƶ��У���ֹ�Թ�ͷ
		{
			right();
		}
		stop();
		delay_ms(80);
	}
}


void TranslateVertical(void)
{
	AdvoidFlag = 0;
	while(Y <= 160)				//������Ŀ��λ��(Y = i)����һֱ��ǰ�ߣ�ͬʱ��PID����
	{
		dirflag = 4;
		back();
		car_adjust();
	}
	stop();
	delay_ms(150);
	while(Y > 160)				//������Ŀ��λ��(Y = i)����һֱ��ǰ�ߣ�ͬʱ��PID����
	{
		dirflag = 5;
		front();
		car_adjust();
	}
	stop();
	delay_ms(150);
	while(Y <= 160)				//������Ŀ��λ��(Y = i)����һֱ��ǰ�ߣ�ͬʱ��PID����
	{
		dirflag = 5;
		back();
		car_adjust();
	}
	stop();
	delay_ms(100);
}

/********************************************************************************
****************����Ϊ�����˵��˶�����*******************************************
*********************************************************************************/


/*
����ͷ�л���ʶ����ɫ���ģ����к��ƶ�����ǰ�����ץ��
*/
void PickBall(void)
{
	HandOpen();
	camera_front();		//����ͷǰ��
	camera_up();		//����ͷ����
	delay_ms(150);
	Repead(BallColor);	//�л���ֵ����ɫ
	delay_ms(30);
	Repead(center);		//ʶ��Բ��	
	SetCore();			//����	
	if(Step == 2)
	{
		MoveTargetBlue(141);	//�ƶ���250��λ��
		ErrFlag = 1;
	}
	if(Step == 2)
	{
		BallCatched();		//����ץ��
	}
}


/*
Ѱ����ɫͶ���������ƶ����ӽ�Ͷ�����ĵط�
*/
void MoveToGreen(void)
{
	camera_back();		//����ͷ��
	camera_up();		//����ͷ����
	delay_ms(500);
	Repead(green);		//�л���ֵ����ɫ
	Repead(center);		//ʶ��Բ��
	SetBackCore();			//����
	if(Step == 4)
		MoveTargetGreen(229);	//����Ͷ����
	Step = 5;
}


/*
�л���ʶ����ɫ��Ե��������ͷ��ǰ��ͷ��ʶ��Ͷ�������˺���ƽ�ƶ��У�����ǰ�ƶ���
ʹ��ͣ����ɫͶ��������
*/
void OnGreenCore(void)
{			
	camera_down();		//����ͷ��ͷ��
	delay_ms(100);		//��Ҫ����ʱ���ǳ���Ҫ	
	Repead(edge);		//ʶ���Ե
	TranslateVertical();	//ǰ����Ŀ��λ��
	TranslateHorizontal();	//ƽ�ƶ�
	Step = 7;
}


void SeekAndLunch(void)		//Ѱ������Ͷ��
{
	camera_back();		//����ͷ��
	camera_pink_up();		//����ͷ̧ͷ
	delay_ms(100);
	Repead(pink);		//�л���ֵ����ɫ
	delay_ms(30);
	Repead(center);		//ʶ��Բ��	
	SetPinkCore();			//����	
	HandPut();			//�ſ�צ�ӣ�������
	delay_ms(1000);
	Step = 1;
}















