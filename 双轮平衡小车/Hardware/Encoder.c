#include "stm32f10x.h"                  // Device header

/***************************************************************************************
								编码器采用TIM2，TIM4
*****************************************************************************************/

/***************************************************************************************
							左侧电机编码器输入为PA0,PA1(TIM2)
							右侧电机编码器输入为PB6,PB7(TIM4)
***************************************************************************************/
void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
	TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseInitStructure.TIM_Period = 65536 - 1;   //ARR
	TimeBaseInitStructure.TIM_Prescaler = 1 - 1;   //PSC
	TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2,&TimeBaseInitStructure);
	
	TIM_TimeBaseInit(TIM4,&TimeBaseInitStructure);
	
	
TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Falling);
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Falling);
	
	TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
}

int16_t EncoderL_Get(void)
{
	int16_t Temp1;
 Temp1 = TIM_GetCounter(TIM2);
	TIM_SetCounter(TIM2,0);
	return Temp1;
}

int16_t EncoderR_Get(void)
{
	int16_t Temp2;
 Temp2 = TIM_GetCounter(TIM4);
	TIM_SetCounter(TIM4,0);
	return Temp2;
}