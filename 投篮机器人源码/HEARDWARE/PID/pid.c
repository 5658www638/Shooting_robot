#include "head_file.h"

unsigned char ErrFlag = 0;

typedef struct PID
{
	float P ,I ,D ,B;	//���������֡�΢��ϵ����ƫ��ֵ
}PID;

typedef struct Error
{
	float Current_Error;  //��ǰ���
	float Last_Error;		//��һ�����
	float Previous_Error;	//��ʷ���
	   
}Error;

//struct PID pid = {2, 0, 0, 0.2};		//��ʼ��PID		//��Ҫ�޸�
struct PID pid = {10, 0, 0.8, 0};		//��ʼ��PID		//��Ҫ�޸�
struct Error error = {0, 0, 0};		//��ʼ��ƫ��ֵ


//#############################################################################
//####################λ��ʽPID�㷨############################################
//#############################################################################


float PID_Realize(u16 NowPlace,u16 Point)	//������ĵ�ǰλ�á����Ŀ��λ�ã��������PIDֵ
{
	int PidPwm;
	float PWM_P,PWM_I,PWM_D, PWM_B;
	
	if(ErrFlag == 1)
	{
		error.Current_Error = 0;
		error.Last_Error = 0;
		error.Previous_Error = 0;
		ErrFlag = 0;
	}
		
	error.Current_Error = Point - NowPlace;		//��ǰ���
	error.Previous_Error = error.Current_Error + error.Previous_Error;		//��ʷ���
	
	PWM_P = pid.P * error.Current_Error;
	PWM_I = pid.I * error.Previous_Error;
	PWM_D = pid.D * (error.Last_Error - error.Current_Error);
	PWM_B = pid.B;
	
	error.Last_Error = error.Current_Error;	//��һ�����
	
	PidPwm = PWM_P + PWM_I + PWM_D + PWM_B;
	
	error.Last_Error = error.Current_Error;
	error.Previous_Error  = error.Previous_Error;
	
	return PidPwm;
}
	


