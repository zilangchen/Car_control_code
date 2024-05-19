#include "system.h"

// 机器人软件失能标志位
u8 Flag_Stop = 0, Last_Flag_Stop = 1;

// ADC值分段变量，取决于小车型号数量，目前有6种小车型号
int Divisor_Mode;

// 机器人型号变量
// 0=Mec_Car，1=Omni_Car，2=Akm_Car，3=Diff_Car，4=FourWheel_Car，5=Tank_Car
u8 Car_Mode = 0;

// 舵机控制PWM值
int Group1_Servo1;
int Group1_Servo2;

int Group2_Servo1;
int Group2_Servo2;

// 遥控小车的默认速度，单位：mm/s
float RC_Velocity = 1000;

// 小车三轴目标运动速度，单位：m/s
float Move_X, Move_Y, Move_Z;

// 速度控制PID参数
float Velocity_KP = 500, Velocity_KI = 500;

// 平滑控制中间变量，全向移动小车专用
Smooth_Control smooth_control;

// 电机的参数结构体
Motor_parameter MOTOR_A, MOTOR_B, MOTOR_C, MOTOR_D;

/************ 小车型号相关变量 **************************/
// 编码器精度
float Encoder_precision;
// 轮子周长，单位：m
float Wheel_perimeter;
// 主动轮轮距，单位：m
float Wheel_spacing;
// 小车前后轴的轴距，单位：m
float Wheel_axlespacing;
// 全向轮转弯半径，单位：m
float Omni_turn_radiaus;
/************ 小车型号相关变量 **************************/
// PS2手柄、蓝牙APP、航模手柄、CAN通信、串口1通信控制标志位。这5个标志位默认都为0，代表串口3控制模式
u8 PS2_ON_Flag = 1, APP_ON_Flag = 0, Remote_ON_Flag = 0, CAN_ON_Flag = 0, Usart_ON_Flag = 0;

// 蓝牙遥控相关的标志位
u8 Flag_Left, Flag_Right, Flag_Direction = 0, Turn_Flag;

// 向蓝牙APP发送参数的标志位
u8 PID_Send;

// PS2手柄控制相关变量
float PS2_LX, PS2_LY, PS2_RX, PS2_RY, PS2_KEY;

void systemInit(void)
{
	// 中断优先级分组设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	// 延时函数初始化
	delay_init(168);

	// 初始化与LED灯连接的硬件接口
	LED_Init();

	// 初始化与蜂鸣器连接的硬件接口
	Buzzer_Init();

	// 初始化与使能开关连接的硬件接口
	Enable_Pin();

	// 初始化与OLED显示屏连接的硬件接口
	OLED_Init();

	// 初始化与用户按键连接的硬件接口
	KEY_Init();

	// 串口1初始化，通信波特率115200，可用于与ROS端通信
	uart1_init(115200);

	// 串口4初始化，通信波特率9600，用于与蓝牙APP端通信
	uart4_init(9600);

	// 串口3初始化，通信波特率115200，串口3为默认用于与ROS端通信的串口
	uart3_init(115200);

	// CAN通信接口初始化
	CAN1_Mode_Init(1, 3, 3, 6, 0);

	// ADC引脚初始化，用于读取电池电压与电位器档位，电位器档位决定小车开机后的小车适配型号
	Adc_Init();

	// 根据电位器的档位判断需要适配的是哪一种型号的小车，然后进行对应的参数初始化
	Robot_Select();

	// 编码器ABCD初始化，并读取电机ABCD的实时速度
	Encoder_Init_TIM2();
	Encoder_Init_TIM3();
	Encoder_Init_TIM4();
	Encoder_Init_TIM5();

	// 初始化电机方向控制引脚，用于控制电机正反转
	MiniBalance_Motor_Init();

	// 初始化电机速度控制以及，用于控制电机速度，PWM频率10KHZ
	MiniBalance_PWM_Init(16799, 0); // 高级定时器TIM8的频率为168M，满PWM为16799，频率=168M/((16799+1)*(0+1))=10k

	// IIC初始化，用于MPU6050
	I2C_GPIOInit();

	// MPU6050初始化，用于读取小车三轴角速度、三轴加速度信息
	MPU6050_initialize();

	// Servo_Group1_PWM_Init(9999,168-1);
	// Servo_Group2_PWM_Init(9999,168-1);
	Servo_PWM_Init(19999, 167); // pwm频率是50Hz

	// 初始化与PS2手柄连接的硬件接口
	PS2_Init();

	// PS2手柄配置初始化,配置为模拟量模式
	PS2_SetInit();
}
