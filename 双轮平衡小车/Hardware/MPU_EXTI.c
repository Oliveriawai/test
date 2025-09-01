#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "MPU6050.h"
#include "inv_mpu.h"

float Pitch,Roll,Yaw;	//欧拉角(由姿态解算指针获取),分别为俯仰角,横滚角,偏航角

void MPU_EXTI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//AFIO用于配置外部中断引脚
	
	/*GPIO配置*/
	GPIO_InitTypeDef GPIO_InitStructure;				//GPIO结构体配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//上拉输入模式(默认高电平)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;			//PB5口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);				//初始化GPIOB外设
	
	/*AFIO外部中断引脚配置*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);//选择MPU的INT接的PB5作为外部中断引脚
	
	/*EXTI配置*/
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	/*NVIC配置*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//分组2,即2位抢占2位响应
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//5到9的通道合并为此通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//中断通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//响应优先级0
	NVIC_Init(&NVIC_InitStructure);
		
}

/**
  * @brief 中断线5,PB5中断函数,当MPU6050数据变化时,进入中断
  * @param  无
  * @retval 无
  */
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) == SET)//确保是PB5进来的中断
	{
		/*数据接收*/
		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);
		EXTI_ClearITPendingBit(EXTI_Line5);//清除中断标志位
	}	
}


