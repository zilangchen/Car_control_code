#include "system.h"

// ���������ʧ�ܱ�־λ
u8 Flag_Stop = 0, Last_Flag_Stop = 1;

// ADCֵ�ֶα�����ȡ����С���ͺ�������Ŀǰ��6��С���ͺ�
int Divisor_Mode;

// �������ͺű���
// 0=Mec_Car��1=Omni_Car��2=Akm_Car��3=Diff_Car��4=FourWheel_Car��5=Tank_Car
u8 Car_Mode = 0;

// �������PWMֵ
int Group1_Servo1;
int Group1_Servo2;

int Group2_Servo1;
int Group2_Servo2;

// ң��С����Ĭ���ٶȣ���λ��mm/s
float RC_Velocity = 1000;

// С������Ŀ���˶��ٶȣ���λ��m/s
float Move_X, Move_Y, Move_Z;

// �ٶȿ���PID����
float Velocity_KP = 500, Velocity_KI = 500;

// ƽ�������м������ȫ���ƶ�С��ר��
Smooth_Control smooth_control;

// ����Ĳ����ṹ��
Motor_parameter MOTOR_A, MOTOR_B, MOTOR_C, MOTOR_D;

/************ С���ͺ���ر��� **************************/
// ����������
float Encoder_precision;
// �����ܳ�����λ��m
float Wheel_perimeter;
// �������־࣬��λ��m
float Wheel_spacing;
// С��ǰ�������࣬��λ��m
float Wheel_axlespacing;
// ȫ����ת��뾶����λ��m
float Omni_turn_radiaus;
/************ С���ͺ���ر��� **************************/
// PS2�ֱ�������APP����ģ�ֱ���CANͨ�š�����1ͨ�ſ��Ʊ�־λ����5����־λĬ�϶�Ϊ0��������3����ģʽ
u8 PS2_ON_Flag = 1, APP_ON_Flag = 0, Remote_ON_Flag = 0, CAN_ON_Flag = 0, Usart_ON_Flag = 0;

// ����ң����صı�־λ
u8 Flag_Left, Flag_Right, Flag_Direction = 0, Turn_Flag;

// ������APP���Ͳ����ı�־λ
u8 PID_Send;

// PS2�ֱ�������ر���
float PS2_LX, PS2_LY, PS2_RX, PS2_RY, PS2_KEY;

void systemInit(void)
{
	// �ж����ȼ���������
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	// ��ʱ������ʼ��
	delay_init(168);

	// ��ʼ����LED�����ӵ�Ӳ���ӿ�
	LED_Init();

	// ��ʼ������������ӵ�Ӳ���ӿ�
	Buzzer_Init();

	// ��ʼ����ʹ�ܿ������ӵ�Ӳ���ӿ�
	Enable_Pin();

	// ��ʼ����OLED��ʾ�����ӵ�Ӳ���ӿ�
	OLED_Init();

	// ��ʼ�����û��������ӵ�Ӳ���ӿ�
	KEY_Init();

	// ����1��ʼ����ͨ�Ų�����115200����������ROS��ͨ��
	uart1_init(115200);

	// ����4��ʼ����ͨ�Ų�����9600������������APP��ͨ��
	uart4_init(9600);

	// ����3��ʼ����ͨ�Ų�����115200������3ΪĬ��������ROS��ͨ�ŵĴ���
	uart3_init(115200);

	// CANͨ�Žӿڳ�ʼ��
	CAN1_Mode_Init(1, 3, 3, 6, 0);

	// ADC���ų�ʼ�������ڶ�ȡ��ص�ѹ���λ����λ����λ����λ����С���������С�������ͺ�
	Adc_Init();

	// ���ݵ�λ���ĵ�λ�ж���Ҫ���������һ���ͺŵ�С����Ȼ����ж�Ӧ�Ĳ�����ʼ��
	Robot_Select();

	// ������ABCD��ʼ��������ȡ���ABCD��ʵʱ�ٶ�
	Encoder_Init_TIM2();
	Encoder_Init_TIM3();
	Encoder_Init_TIM4();
	Encoder_Init_TIM5();

	// ��ʼ���������������ţ����ڿ��Ƶ������ת
	MiniBalance_Motor_Init();

	// ��ʼ������ٶȿ����Լ������ڿ��Ƶ���ٶȣ�PWMƵ��10KHZ
	MiniBalance_PWM_Init(16799, 0); // �߼���ʱ��TIM8��Ƶ��Ϊ168M����PWMΪ16799��Ƶ��=168M/((16799+1)*(0+1))=10k

	// IIC��ʼ��������MPU6050
	I2C_GPIOInit();

	// MPU6050��ʼ�������ڶ�ȡС��������ٶȡ�������ٶ���Ϣ
	MPU6050_initialize();

	// Servo_Group1_PWM_Init(9999,168-1);
	// Servo_Group2_PWM_Init(9999,168-1);
	Servo_PWM_Init(19999, 167); // pwmƵ����50Hz

	// ��ʼ����PS2�ֱ����ӵ�Ӳ���ӿ�
	PS2_Init();

	// PS2�ֱ����ó�ʼ��,����Ϊģ����ģʽ
	PS2_SetInit();
}
