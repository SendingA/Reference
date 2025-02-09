#include "IRSEARCH.h"
#include "delay.h"
#include "motor.h"
#include "stm32f10x.h"                  // Device header

char ctrl_comm = COMM_STOP;//控制指令
char ctrl_comm_last = COMM_STOP;//上一次的指令

void IRSearchInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC , ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = SEARCH_R_PIN;//配置使能GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
	GPIO_Init(SEARCH_R_GPIO , &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = SEARCH_L_PIN;//配置使能GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置GPIO模式,输入上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
	GPIO_Init(SEARCH_L_GPIO , &GPIO_InitStructure); 
}

void SearchRun(void)
{
	if(SEARCH_L_IO == WHITE_AREA && SEARCH_R_IO == WHITE_AREA)
		ctrl_comm = COMM_UP;  //两边数值相同
	else if (SEARCH_L_IO == BLACK_AREA && SEARCH_R_IO == WHITE_AREA)
		ctrl_comm = COMM_LEFT;
	else if (SEARCH_R_IO == BLACK_AREA & SEARCH_L_IO == WHITE_AREA)
		ctrl_comm = COMM_RIGHT;
	else ctrl_comm = COMM_STOP;
	
	if(ctrl_comm_last != ctrl_comm)
	{
			ctrl_comm_last = ctrl_comm;
		 	switch(ctrl_comm)
				{
					case COMM_UP:    HJduino_run(50,10);break; //前 数值越小，机器人速度越慢
					case COMM_DOWN:  HJduino_back(70,10);break;
					case COMM_LEFT:  HJduino_Left(50,100);break;
					case COMM_RIGHT: HJduino_Right(50,100);break;
					case COMM_STOP:  HJduino_brake(10);break;
					default : break;
				}
	}
}





