#include "robot_select_init.h"

//Initialize the robot parameter structure
//��ʼ�������˲����ṹ��
Robot_Parament_InitTypeDef  Robot_Parament; 
/**************************************************************************
Function: According to the potentiometer switch needs to control the car type
Input   : none
Output  : none
�������ܣ����ݵ�λ���л���Ҫ���Ƶ�С������
��ڲ�������
����  ֵ����
**************************************************************************/
void Robot_Select(void)
{
	//The ADC value is variable in segments, depending on the number of car models. Currently there are 6 car models, CAR_NUMBER=6
  //ADCֵ�ֶα�����ȡ����С���ͺ�������Ŀǰ��6��С���ͺţ�CAR_NUMBER=6
	Divisor_Mode=4096/CAR_NUMBER+5;
	Car_Mode=(int) ((Get_adc_Average(CAR_MODE_ADC,10))/Divisor_Mode); //Collect the pin information of potentiometer //�ɼ���λ��������Ϣ	
  if(Car_Mode>10)Car_Mode=10;
	#if Mec
	{	
		if (Car_Mode==0)  Robot_Init(SENIOR_MEC_BS_wheelspacing, SENIOR_MEC_BS_axlespacing, MD36N_27, Hall_13, Mecanum_100); //SENIOR_MEC_BS - �������ְ�ʽ���� //BS: Pendulum suspension
		if (Car_Mode==1)  Robot_Init(SENIOR_MEC_BS_wheelspacing, SENIOR_MEC_BS_axlespacing, MD36N_27, Hall_13, Mecanum_100); //SENIOR_MEC_BS - �������ְ�ʽ����  
		
		if (Car_Mode==2)  Robot_Init(SENIOR_MEC_DL_wheelspacing, SENIOR_MEC_DL_axlespacing, MD36N_27, Hall_13, Mecanum_152); //SENIOR_MEC_DL - �������ֶ������� //DL: Independent suspension 
		if (Car_Mode==3)  Robot_Init(TOP_MEC_BS_wheelspacing,    TOP_MEC_BS_axlespacing,    MD60N_18, Hall_13, Mecanum_152); //TOP_MEC_BS_18 - �������ְ�ʽ���ҳ�����
		
		if (Car_Mode==4)  Robot_Init(TOP_MEC_BS_wheelspacing,    TOP_MEC_BS_axlespacing,    MD60N_47, Hall_13, Mecanum_152); //TOP_MEC_BS_47 - �������ְ�ʽ����������
		
		if (Car_Mode==5)  Robot_Init(TOP_MEC_DL_wheelspacing,    TOP_MEC_DL_axlespacing,    MD60N_18, Hall_13, Mecanum_152); //TOP_MEC_DL_18 - �������ֶ������ҳ�����
		if (Car_Mode==6)  Robot_Init(TOP_MEC_DL_wheelspacing,    TOP_MEC_DL_axlespacing,    MD60N_47, Hall_13, Mecanum_152); //TOP_MEC_DL_18 - �������ֶ�������������
		
		if (Car_Mode==7)  Robot_Init(FLAGSHIP_MEC_BS_wheelspacing,    FLAGSHIP_MEC_BS_axlespacing,    MD60N_18, Hall_13, Mecanum_152); //FlagShip_MEC_DL_18 - �콢���ְ�ʽ���ҳ�����
		if (Car_Mode==8)  Robot_Init(FLAGSHIP_MEC_BS_wheelspacing,    FLAGSHIP_MEC_BS_axlespacing,    MD60N_47, Hall_13, Mecanum_152); //FlagShip_MEC_DL_47 - �콢���ְ�ʽ����������
		
		if (Car_Mode==9)   Robot_Init(FLAGSHIP_MEC_DL_wheelspacing,FLAGSHIP_MEC_DL_axlespacing,MD60N_18, Hall_13, Mecanum_152); //flagship_MEC_dl_18 - �콢���ֶ������ҳ�����
		if (Car_Mode==10)  Robot_Init(FLAGSHIP_MEC_DL_wheelspacing,FLAGSHIP_MEC_DL_axlespacing,MD60N_47, Hall_13, Mecanum_152); //flagship_MEC_dl_47 - �콢���ֶ�������������
	}
	#elif Omni
	{
		if (Car_Mode==0)  Robot_Init(Omni_Turn_Radiaus_164, MD36N_5_18, Hall_13, FullDirecion_75); //SENIOR_OMNI_5_18 - ����ȫ���������μ�����
	  if (Car_Mode==1)  Robot_Init(Omni_Turn_Radiaus_180, MD36N_27,   Hall_13, FullDirecion_127);//SENIOR_OMNI_27   - ����ȫ���������γ���     
		if (Car_Mode==2)  Robot_Init(Omni_Turn_Radiaus_180, MD36N_27,   Hall_13, FullDirecion_127);//SENIOR_OMNI_27   - ����ȫ����Բ�γ���       
		if (Car_Mode==3)  Robot_Init(Omni_Turn_Radiaus_180, MD36N_51,   Hall_13, FullDirecion_127);//SENIOR_OMNI_51   - ����ȫ����Բ������       
		
		if (Car_Mode==4)  Robot_Init(Omni_Turn_Radiaus_290, MD60N_18,   Hall_13, FullDirecion_127);//TOP_OMNI_18      - ����ȫ���ֳ��� ֱ��127   
		if (Car_Mode==5)  Robot_Init(Omni_Turn_Radiaus_290, MD60N_18,   Hall_13, FullDirecion_152);//TOP_OMNI_18      - ����ȫ���ֳ��� ֱ��152
		if (Car_Mode==6)  Robot_Init(Omni_Turn_Radiaus_290, MD60N_18,   Hall_13, FullDirecion_203);//TOP_OMNI_18      - ����ȫ���ֳ��� ֱ��203
	}
	#endif
}


#if Mec
/**************************************************************************
Function: Initialize cart parameters
Input   : wheelspacing, axlespacing, omni_rotation_radiaus, motor_gear_ratio, Number_of_encoder_lines, tyre_diameter
Output  : none
�������ܣ���ʼ��С������
��ڲ������־� ��� ��ת�뾶 ������ٱ� ������������� ��ֱ̥��
����  ֵ����
**************************************************************************/
void Robot_Init(float wheelspacing,float axlespacing,int gearratio,int Accuracy,float tyre_diameter) 
{
  Robot_Parament.WheelSpacing=wheelspacing;   //Wheelspacing �־�  
	Robot_Parament.AxleSpacing=axlespacing;     //Axlespacing ���
  Robot_Parament.GearRatio=gearratio;         //motor_gear_ratio //������ٱ�
  Robot_Parament.EncoderAccuracy=Accuracy;    //Number_of_encoder_lines //����������(����������)
  Robot_Parament.WheelDiameter=tyre_diameter; //Diameter of driving wheel //�������־�
	
	//Encoder value corresponding to 1 turn of motor (wheel)
	//���(����)ת1Ȧ��Ӧ�ı�������ֵ
	Encoder_precision=EncoderMultiples*Robot_Parament.EncoderAccuracy*Robot_Parament.GearRatio;
	//Driving wheel circumference //�������ܳ�	
	Wheel_perimeter=Robot_Parament.WheelDiameter*PI; 
	//Wheelspacing �־� 
  Wheel_spacing=Robot_Parament.WheelSpacing;  
 //Wheel_axlespacing (Wheel_axlespacing is not required for motion analysis of differential trolleys) //���(����С�����˶���������Ҫ���)	
	Wheel_axlespacing=Robot_Parament.AxleSpacing;    
}

#elif Omni
/**************************************************************************
Function: Initialize cart parameters
Input   : omni_rotation_radiaus, motor_gear_ratio, Number_of_encoder_lines, tyre_diameter
Output  : none
�������ܣ���ʼ��С������
��ڲ�������ת�뾶 ������ٱ� ������������� ��ֱ̥��
����  ֵ����
**************************************************************************/
void Robot_Init(float omni_turn_radiaus,int gearratio,int Accuracy,float tyre_diameter)
{
	//Rotation radius of omnidirectional trolley
  //ȫ����С����ת�뾶	
  Robot_Parament.OmniTurnRadiaus=omni_turn_radiaus;
	//motor_gear_ratio
	//������ٱ�
  Robot_Parament.GearRatio=gearratio;
	//Number_of_encoder_lines
  //����������(����������)
  Robot_Parament.EncoderAccuracy=Accuracy;
	//Diameter of driving wheel
  //������ֱ��
  Robot_Parament.WheelDiameter=tyre_diameter;
	
	//Encoder value corresponding to 1 turn of motor (wheel)
	//���(����)ת1Ȧ��Ӧ�ı�������ֵ
	Encoder_precision=EncoderMultiples*Robot_Parament.EncoderAccuracy*Robot_Parament.GearRatio;
	//Driving wheel circumference
  //�������ܳ�	
	Wheel_perimeter=Robot_Parament.WheelDiameter*PI;
	//Rotation radius of omnidirectional trolley
  //ȫ����С����ת�뾶	
  Omni_turn_radiaus=Robot_Parament.OmniTurnRadiaus;
}

#endif

