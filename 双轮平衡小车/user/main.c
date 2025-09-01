#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Timer.h"
#include "RP.h"
#include "PWM.h"
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"
#include "MPU6050.h"
#include "MPU_EXTI.h"
#include "inv_mpu.h"
#include "PID.h"

extern float Pitch,Roll,Yaw;
//单环PID
PID_t LocationPID = {
	.Target = -5 ,

	.Kp = 8,  
	.Ki = 0,
	.Kd = 20 ,
	
	.OutMax = 100,
	.OutMin = -100,
};

/*电机测试*/	
//uint8_t KeyNum;
//int16_t PWM = 20;
//int16_t Count;
//float TargetL , ActualL , OutL;
//float KpL = 0.35, KiL =0.25 , KdL = 0.5;
//float Error0L,Error1L,ErrorIntL;
//float TargetR , ActualR , OutR;
//float KpR = 0.35, KiR =0.25 , KdR = 0.5;
//float Error0R, Error1R, ErrorIntR;
/*电机测试*/	

int main(void)
{ 
	OLED_Init();
	delay_init();
	MPU6050_DMP_Init();
	MPU_EXTI_Init();
	
	Timer_Init();
	Motor_Init();
	Encoder_Init();
	
	while(1)
	{
//MPU6050角度解算显示		
//		OLED_Printf(0,16,OLED_8X16,"横滚角:%.2f ", Pitch);
//		OLED_Printf(0,32,OLED_8X16,"俯仰角:%.2f ", Roll);
//		OLED_Printf(0,48,OLED_8X16,"偏航角:%.2f ", Yaw);
//		OLED_Update();
		
/*电机测试*/		
//		TargetL = 50; 
//		TargetR = 30;
//		ActualL = EncoderL_Get();
//		ActualR = EncoderR_Get();
//		Motor_SetPWML(PWM);
//		Motor_SetPWMR(PWM);
//		OLED_Printf(0,0,OLED_8X16,"ActualL:%+04.0f",ActualL);
//		OLED_Printf(0,16,OLED_8X16,"ActualR:%+04.0f",ActualR);
//		OLED_Printf(0,32,OLED_8X16,"TargetL:%+04.0f",TargetL);
//		OLED_Printf(0,64,OLED_8X16,"TargetR:%+04.0f",TargetR);
//		OLED_Update();		
/*电机测试*/
		
		OLED_Printf(0, 0, OLED_6X8," Location");
		OLED_Printf(0, 12, OLED_6X8,"Kp:%05.3f",LocationPID.Kp);
		OLED_Printf(0, 20, OLED_6X8,"Ki:%05.3f",LocationPID.Ki);
		OLED_Printf(0, 28, OLED_6X8,"Kd:%05.3f",LocationPID.Kd);
		OLED_Printf(0, 40, OLED_6X8,"Tar:%04.0f",LocationPID.Target);
		OLED_Printf(0, 48, OLED_6X8,"Act:%.2f",Roll);
		OLED_Printf(0, 56, OLED_6X8,"Out:%+04.0f",LocationPID.Out);
		OLED_Update();
		
		
		
	}
}

void TIM3_IRQHandler(void)
{
static	 uint16_t Count1;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		Count1 ++;
		if(Count1 >= 5)
		{
			Count1 = 0;
			
			LocationPID.Actual = Roll;
			PID_UpDate(&LocationPID);
			Motor_SetPWML(LocationPID.Out);
			Motor_SetPWMR(LocationPID.Out);
			
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
	
}
	
	
	
		
		
		
 /*OLED测试*/ 
//int main(void)
//{
//	OLED_Init();
//	OLED_ShowString(0,0,"Oliveria",OLED_8X16);
//	
//	OLED_Update();
//	while(1)
//	{
//	
//	}
//	
//}   

 /*LED测试*/
//int main(void)
//{
//	LED_Init();
//	
//	while(1)
//	{
//	LED_ON();
//	Delay_ms(500);
//	LED_OFF();
//	Delay_ms(500);
//	LED_Turn();
//	Delay_ms(500);
//	LED_Turn();
//	Delay_ms(500);		
//	}
//	
//} 

/*按键测试*/
//uint16_t i ;
//uint16_t j ;
//uint8_t KeyNum ;
//int main(void)
//{
//	OLED_Init();
//	Key_Init();
//	Timer_Init();
//	while(1)
//	{
//	KeyNum = Key_GetNum();
//if(KeyNum == 1)
//{
//	j++;
//}	
//if(KeyNum == 2)
//{
//	j--;
//}	
//if(KeyNum == 3)
//{
//	j+=10;
//}	
//if(KeyNum == 4)
//{
//	j-=10;
//}	
//	OLED_Printf(0,0,OLED_8X16,"i:%05d",i);
//	OLED_Printf(0,16,OLED_8X16,"j:%05d",j);		
//	OLED_Update();
//	}
//	
//} 
//void TIM1_UP_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM1,TIM_IT_Update) == SET)//
//	{
//			i++;
//		
//			Key_Tick();
//		
//			TIM_ClearITPendingBit(TIM1,TIM_IT_Update);//
//	}
//}

/*电位器测试*/
//int main(void)
//{
//	OLED_Init();
//	RP_Init();
//	
//	while(1)
//	{
//	                                        
//	OLED_Printf(0,0,OLED_8X16,"RP1:%04d",RP_GetValue(1));
//	OLED_Printf(0,16,OLED_8X16,"RP2:%04d",RP_GetValue(2));
//	OLED_Printf(0,32,OLED_8X16,"RP3:%04d",RP_GetValue(3));
//	OLED_Printf(0,48,OLED_8X16,"RP4:%04d",RP_GetValue(4));		
//		
//	OLED_Update();
//	}
//}

/*电机驱动测试*/
//uint8_t KeyNum ;
//int16_t PWM;
//int main(void)
//{
//	OLED_Init();
//	Key_Init();
//	Motor_Init();
//	Timer_Init();
//	while(1)
//	{
//	KeyNum = Key_GetNum();
//if(KeyNum == 1)
//{
//	PWM +=10;
//	if(PWM > 100){PWM = 100;}
//}	
//if(KeyNum == 2)
//{
//	PWM -=10;
//	if(PWM < -100){PWM = -100;}
//}	
//if(KeyNum == 3)
//{
//	PWM=0;
//}	
//	Motor_SetPWM(PWM) ;
//	OLED_Printf(0,0,OLED_8X16,"PWM:%+04d",PWM);	
//	OLED_Update();
//	}
//	
//} 
//void TIM1_UP_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM1,TIM_IT_Update) == SET)//
//	{
//		
//			Key_Tick();
//		
//			TIM_ClearITPendingBit(TIM1,TIM_IT_Update);//
//	}
//}

/*编码器测试*/
//int16_t Speed ;
//int16_t Location;
//int main(void)
//{
//	OLED_Init();
//	Encoder_Init();
//	Timer_Init();
//	while(1)
//	{

//	OLED_Printf(0,0,OLED_8X16,"Speed:%+04d",Speed);
//	OLED_Printf(0,16,OLED_8X16,"Location:%+04d",Location);			
//	OLED_Update();
//	}
//	
//} 
//void TIM1_UP_IRQHandler(void)
//{
//	static uint16_t Count;
//	if(TIM_GetITStatus(TIM1,TIM_IT_Update) == SET)//
//	{
//		Count ++;
//		if(Count >= 40)
//		{
//		Count = 0;
//		Speed = Encoder_Get();
//			Location+= Speed;
//		}
//			Key_Tick();
//		
//			TIM_ClearITPendingBit(TIM1,TIM_IT_Update);//
//	}
//}

/*串口测试未测试*/
//uint16_t RP1, RP2 ,RP3 ,RP4;
//int main(void)
//{
//	OLED_Init();
//	RP_Init();
//	Serial_Init();
//	while(1)
//	{
//	RP1 = RP_GetValue(1);   
//	RP2 = RP_GetValue(2);  
//	RP3 = RP_GetValue(3);  
//	RP4 = RP_GetValue(4);  		
//	OLED_Printf(0,0,OLED_8X16,"RP1:%04d",RP1);
//	OLED_Printf(0,16,OLED_8X16,"RP2:%04d",RP2);
//	OLED_Printf(0,32,OLED_8X16,"RP3:%04d",RP3);
//	OLED_Printf(0,48,OLED_8X16,"RP4:%04d",RP4);		
//		
//	OLED_Update();
//		
//	Serial_Printf("%d,%d,%d,%d\r\n",RP1, RP2 ,RP3 ,RP4);
//	Delay_ms(10);
//	}
//}
