#ifndef __BALANCE_H
#define __BALANCE_H
#include "sys.h"
#include "system.h"
#define BALANCE_TASK_PRIO 4  // Task priority //�������ȼ�
#define BALANCE_STK_SIZE 512 // Task stack size //�����ջ��С

// Parameter of kinematics analysis of omnidirectional trolley
// ȫ����С���˶�ѧ��������
#define X_PARAMETER (sqrt(3) / 2.f)
#define Y_PARAMETER (0.5f)
#define L_PARAMETER (1.0f)

extern int A, B, C, DD;
extern u8 command_lost_count; // ���ڡ�CAN�������ʧʱ���������ʧ1���ֹͣ����
void Balance_task(void *pvParameters);
void Limit_Pwm(int amplitude);
float target_limit_float(float insert, float low, float high);
int target_limit_int(int insert, int low, int high);
u8 Turn_Off(int voltage);
u32 myabs(long int a);
float float_abs(float insert);
int Incremental_PI_A(float Encoder, float Target);
int Incremental_PI_B(float Encoder, float Target);
int Incremental_PI_C(float Encoder, float Target);
int Incremental_PI_D(float Encoder, float Target);

void Get_RC(void);
void PS2_control(void);
void Remote_Control(void);
void Set_Pwm(int motor_a, int motor_b, int motor_c, int motor_d);

void Excute_Servo_Group1(int servo_group1_command);
void Excute_Servo_Group2(int servo_group2_command);

void Drive_Motor(float Vx, float Vy, float Vz);
void Key(void);
void Get_Velocity_Form_Encoder(void);
void robot_mode_check(void);
// void Smooth_control(float vx, float vz, float step, float step_Vz);
int Smooth_steering(int currentPWM, int targetPWM, float step);
int Mean_Filter(int data);
void Smooth_control(float vx, float vy, float vz);
#endif
