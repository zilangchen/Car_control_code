#ifndef __ROBOTSELECTINIT_H
#define __ROBOTSELECTINIT_H
#include "sys.h"
#include "system.h"

// Parameter structure of robot
// �����˲����ṹ��
typedef struct
{
  float WheelSpacing;    // Wheelspacing, Mec_Car is half wheelspacing //�־� ���ֳ�Ϊ���־�
  float AxleSpacing;     // Axlespacing, Mec_Car is half axlespacing //��� ���ֳ�Ϊ�����
  int GearRatio;         // Motor_gear_ratio //������ٱ�
  int EncoderAccuracy;   // Number_of_encoder_lines //����������(����������)
  float WheelDiameter;   // Diameter of driving wheel //������ֱ��
  float OmniTurnRadiaus; // Rotation radius of omnidirectional trolley //ȫ����С����ת�뾶
} Robot_Parament_InitTypeDef;

// half wheelspacing //���־�
#define SENIOR_MEC_BS_wheelspacing 0.176
#define SENIOR_MEC_DL_wheelspacing 0.247
#define TOP_MEC_BS_wheelspacing 0.311
#define TOP_MEC_DL_wheelspacing 0.295
#define FLAGSHIP_MEC_DL_wheelspacing 0.285
#define FLAGSHIP_MEC_BS_wheelspacing 0.292
#define TOP_MEC_DL_wheelspacing_Customized 0.446  // Custom size //���Ƴߴ�
#define Senior_MEC_DL_wheelspacing_Customized 0.3 // Custom size //���Ƴߴ�

// half axlespacing //�����
#define SENIOR_MEC_BS_axlespacing 0.156
#define SENIOR_MEC_DL_axlespacing 0.214
#define TOP_MEC_BS_axlespacing 0.308
#define TOP_MEC_DL_axlespacing 0.201
#define FLAGSHIP_MEC_DL_axlespacing 0.178
#define FLAGSHIP_MEC_BS_axlespacing 0.178
#define TOP_MEC_DL_axlespacing_Customized 0.401   // Custom size //���Ƴߴ�
#define Senior_MEC_DL_axlespacing_Customized 0.24 // Custom size //���Ƴߴ�

// Motor_gear_ratio
// ������ٱ�
#define MD36N_5_18 5.18f
#define MD36N_27 27
#define MD36N_51 51
#define MD36N_71 71
#define MD60N_18 18
#define MD60N_47 47

// Number_of_encoder_lines
// ����������
#define Photoelectric_500 500
#define Hall_13 13

// Mecanum wheel tire diameter series
// ������ֱ̥��
#define Mecanum_60 0.060f
#define Mecanum_75 0.075f
#define Mecanum_100 0.100f
#define Mecanum_127 0.127f
#define Mecanum_152 0.152f

// Omni wheel tire diameter series
// �־�ȫ����ֱ��ϵ��
#define FullDirecion_75 0.075
#define FullDirecion_127 0.127
#define FullDirecion_152 0.152
#define FullDirecion_203 0.203
#define FullDirecion_217 0.217

// Rotation radius of omnidirectional trolley
// ȫ����С����ת�뾶
#define Omni_Turn_Radiaus_164 0.164
#define Omni_Turn_Radiaus_180 0.160 // ����Ϊ160
#define Omni_Turn_Radiaus_290 0.280 // ����Ϊ280

// The encoder octave depends on the encoder initialization Settings
// ��������Ƶ����ȡ���ڱ�������ʼ������
#define EncoderMultiples 4
// Encoder data reading frequency
// ���������ݶ�ȡƵ��
#define CONTROL_FREQUENCY 100

// #define PI 3.1415f  //PI //Բ����

void Robot_Select(void);
#if Mec
void Robot_Init(float wheelspacing, float axlespacing, int gearratio, int Accuracy, float tyre_diameter);
#elif Omni
void Robot_Init(float omni_turn_radiaus, int gearratio, int Accuracy, float tyre_diameter);
#endif

#endif
