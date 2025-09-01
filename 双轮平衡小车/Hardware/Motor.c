#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	PWM_Init();
}
/***************************************************************************************
				左侧电机输入方向引脚为PB12,PB13，PWM输入为PA11(TIM1)
				右侧电机输入方向引脚为PB14,PB15，PWM输入为PA8(TIM1)
***************************************************************************************/
void Motor_SetPWML(int8_t PWM)
{
	if (PWM >= 0)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		PWM_SetCompare4(PWM);
	}
	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		PWM_SetCompare4(-PWM);
	}
}
void Motor_SetPWMR(int8_t PWM)
{
	if (PWM >= 0)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		PWM_SetCompare1(PWM);
	}
	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		PWM_SetCompare1(-PWM);
	}
}

