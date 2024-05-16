#include "motor.h"

/**************************************************************************
Function: Motor orientation pin initialization
Input   : none
Output  : none
函数功能：电机方向引脚初始化
入口参数：无
返回  值：无
**************************************************************************/
void MiniBalance_Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE); // 使能GPIOB C D时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;		 // 对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	 // 普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 50MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 // 上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);			 // 初始化GPIO

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14; //| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;						   // 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_12; // 对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			// 普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		// 50MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			// 上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);					// 初始化GPIO

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12; // 对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			 // 普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			 // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 // 50MHz
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//上拉			GPIO_PuPd_NOPULL
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);		 // 初始化GPIO

	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
	GPIO_ResetBits(GPIOC, GPIO_Pin_0 | GPIO_Pin_12);
	GPIO_ResetBits(GPIOD, GPIO_Pin_10 | GPIO_Pin_12);
}

/**************************************************************************
Function: The motor PWM initialization
Input   : arr: Automatic reload value, psc: clock preset frequency
Output  : none
函数功能：电机PWM引脚初始化
入口参数：arr：自动重装值  psc：时钟预分频数
返回  值：无
**************************************************************************/
void MiniBalance_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);  // TIM8时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); // 使能PORTC时钟

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; // GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;									 // 复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;								 // 速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;									 // 推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;									 // 上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);											 // 初始化PC口

	// Sets the value of the auto-reload register cycle for the next update event load activity
	// 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Period = arr;
	// Sets the pre-divider value used as the TIMX clock frequency divisor
	// 设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	// Set the clock split :TDTS = Tck_tim
	// 设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = 1;
	// Up counting mode
	// 向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	// Initializes the timebase unit for TIMX based on the parameter specified in TIM_TIMEBASEINITSTRUCT
	// 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

	// Select Timer mode :TIM Pulse Width Modulation mode 1
	// 选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// Compare output enablement
	// 比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// Output polarity :TIM output polarity is higher
	// 输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
	// 根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);

	// Advanced timer output must be enabled
	// 高级定时器输出必须使能这句
	TIM_CtrlPWMOutputs(TIM8, ENABLE);

	// CH1 is pre-loaded and enabled
	// CH1预装载使能
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);

	// Enable the TIMX preloaded register on the ARR
	// 使能TIMx在ARR上的预装载寄存器
	TIM_ARRPreloadConfig(TIM8, ENABLE);

	TIM8->CCR1 = 0;
	TIM8->CCR2 = 0;
	TIM8->CCR3 = 0;
	TIM8->CCR4 = 0;

	// Enable TIM8
	// 使能TIM8
	TIM_Cmd(TIM8, ENABLE);
}

/**************************************************************************
Function: Enable switch pin initialization
Input   : none
Output  : none
函数功能：使能开关引脚初始化
入口参数：无
返回  值：无
**************************************************************************/
void Enable_Pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // 使能GPIOE时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;			  // KEY对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		  // 普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	  // 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		  // 上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);				  // 初始化GPIOE4
}

/**************************************************************************
Function: Model aircraft three channel remote control pin and steering gear PWM pin initialization
Input   : ARR: Automatic reload value  PSC: clock preset frequency
Output  : none
函数功能：航模三通道遥控引脚与舵机PWM引脚初始化
入口参数：arr：自动重装值  psc：时钟预分频数
返回  值：无
**************************************************************************/
void Servo_PWM_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // 定时器
	TIM_OCInitTypeDef TIM_OCInitStructure;		   // PWM输出
	GPIO_InitTypeDef GPIO_InitStructure;		   // IO

	//NVIC_InitTypeDef NVIC_InitStructure;   // 中断优先级
	//TIM_ICInitTypeDef TIM_ICInitStructure; // 输入捕获

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  // TIM1时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // 使能PORTE时钟

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; // 这里为什么用下拉不用上拉要看看
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*** Initialize timer 1 || 初始化定时器1 ***/
	// Set the counter to automatically reload //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Period = arr;
	// Pre-divider //预分频器
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	// Set the clock split: TDTS = Tck_tim //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_ClockDivision = 1;
	// TIM up count mode //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	// Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
	// 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	//-----------舵机初始化-----------//
	// Select Timer mode :TIM Pulse Width Modulation mode 1
	// 选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// Compare output enablement
	// 比较输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// Set the pulse value of the capture comparison register to be loaded
	// 设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_Pulse = 0;
	// Output polarity :TIM output polarity is higher
	// 输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;

	// Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
	// 根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	// Advanced timer output must be enabled //高级定时器输出必须使能这句
	// 我也不知道有什么用，开了应该也没问题
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	// Channel preload enable
	// 通道预装载使能
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	// Enable the TIMX preloaded register on the ARR
	// 使能TIMx在ARR上的预装载寄存器
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	//-----------舵机初始化-----------//

	// The channel value is initialized to 1500, corresponding to the steering gear zero
	// 通道值初始化为1500，舵机零点对应值，我们的舵机2500对应270度，旋转方向是逆时针
	TIM1->CCR1 = 1500;
	TIM1->CCR2 = 1500;
	TIM1->CCR3 = 1500;
	TIM1->CCR4 = 1500;

	TIM_Cmd(TIM1, ENABLE);
}
/**************************************************************************
void Servo_Group2_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;		   // IO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // 定时器
	NVIC_InitTypeDef NVIC_InitStructure;		   // 中断优先级
	TIM_ICInitTypeDef TIM_ICInitStructure;		   // 输入捕获
	TIM_OCInitTypeDef TIM_OCInitStructure;		   // PWM输出

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM4, ENABLE);  // TIM1时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // 使能PORTE时钟

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);

	*/

/*** Initialize timer 1 || 初始化定时器1 ***/

/*
// Set the counter to automatically reload //设定计数器自动重装值
TIM_TimeBaseStructure.TIM_Period = arr;
// Pre-divider //预分频器
TIM_TimeBaseStructure.TIM_Prescaler = psc;
// Set the clock split: TDTS = Tck_tim //设置时钟分割:TDTS = Tck_tim
TIM_TimeBaseStructure.TIM_ClockDivision = 1;
// TIM up count mode //TIM向上计数模式
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
// Initializes the timebase unit for TIMX based on the parameter specified in TIM_TimeBaseInitStruct
// 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//-----------舵机初始化-----------//
// Select Timer mode :TIM Pulse Width Modulation mode 1
// 选择定时器模式:TIM脉冲宽度调制模式1
TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
// Compare output enablement
// 比较输出使能
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
// Set the pulse value of the capture comparison register to be loaded
// 设置待装入捕获比较寄存器的脉冲值
TIM_OCInitStructure.TIM_Pulse = 0;
// Output polarity :TIM output polarity is higher
// 输出极性:TIM输出比较极性高
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;

// Initialize the peripheral TIMX based on the parameter specified in TIM_OCINITSTRUCT
// 根据TIM_OCInitStruct中指定的参数初始化外设TIMx
TIM_OC2Init(TIM4, &TIM_OCInitStructure);
// Channel preload enable
// 通道预装载使能
TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
// Enable the TIMX preloaded register on the ARR
// 使能TIMx在ARR上的预装载寄存器
TIM_ARRPreloadConfig(TIM4, ENABLE);
//-----------舵机初始化-----------//
TIM_Cmd(TIM4, ENABLE);

// The channel value is initialized to 1500, corresponding to the steering gear zero
// 通道值初始化为1500，舵机零点对应值
TIM4->CCR2 = 1500;
}*/
