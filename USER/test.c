#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart2.h"
#include "can.h"
#include "timer.h"


//------------------------底盘小车控制---------------------------------
//命令
u8 forward_cmd[10] = 	{0xff, 0xfe, 0x01 ,0x00 ,0x00, 0x00, 0x12, 0x00, 0x00 ,0x00};
u8 backward_cmd[10] = 	{0xff, 0xfe, 0x01 ,0x00 ,0x00, 0x00, 0x12, 0x00, 0x00 ,0x02};

u8 stop_cmd[10] = 		{0xff, 0xfe, 0x01 ,0x00 ,0x00, 0x00, 0x00, 0x00, 0x00 ,0x00};

u8 turn_left_cmd[10] = 		{0xff, 0xfe, 0x01 ,0x00 ,0x00, 0x00, 0x00, 0x00, 0x12 ,0x01};
u8 turn_right_cmd[10] = 		{0xff, 0xfe, 0x01 ,0x00 ,0x00, 0x00, 0x00, 0x00, 0x12 ,0x00};
//-------


u8 Way_Angle=1;                             //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_Direction=0; //蓝牙遥控相关的变量
u8 Flag_Stop=1,Flag_Show=0;                 //停止标志位和 显示标志位 默认停止 显示打开
int Encoder_A,Encoder_B,Encoder_C;             //编码器的脉冲计数
int Encoder_A_EXTI;
int Motor_A,Motor_B,Motor_C;                   //电机PWM变量
int Target_A,Target_B,Target_C;                   //电机目标速度
int Temperature;                            //显示温度
int Voltage;                                //电池电压采样相关的变量
float Angle_Balance,Gyro_Balance,Gyro_Turn; //平衡倾角 平衡陀螺仪 转向陀螺仪
float Show_Data_Mb;                         //全局显示变量，用于显示需要查看的数据
//u32 Distance;                               //超声波测距，这个变量放在timer里定义了
u8 delay_50,delay_flag;         //默认情况下，不开启避障功能，长按用户按键2s以上可以进入避障模式
int Velocity=30;
u8 Usart3_Receive;
u8 rxbuf[8],Rxbuf[16];
u8 txbuf[8];
int AZ,GZ;
float Pitch,Roll,Yaw; 
u32 count,usart_count;
int temp,temp2,temp3,count_temp,flag;
u8 ON_txbuf[8]={10,12,15,19,24,30,37,1} ;
u8 Velocity_txbuf[8]={11,13,16,20,25,31,38,50} ; 

int main(void)
{ 
	//float i;   //never used
	//Stm32_Clock_Init(9);            //=====系统时钟设置 换成下面这句随便设置一下试试
	Stm32_Clock_Init(336,8,2,7);//设置时钟
	delay_init(72);                 //=====延时初始化
  uart_init(72,128000);           //=====初始化串口1
	//
  //usart2_init(36,115200);            //=====串口2初始化
	usart2_init(42,115200);            //=====串口2初始化,摘自摄像头项目
	//Timer1_Init(499,7199);  //这句话meifanyign 改成下面这个
	//TIM5_CH1_Cap_Init(499,7199);
	CAN1_Mode_Init(1,2,3,6,0);  //CAN初始化
	
	while(1)
		{    
				int i;
				usart_send(0xff);
				
				//前
				for( i=0;i<10;i++)
				{
					usart2_send(forward_cmd[i]);
				}
				delay_ms(2000);
				//停
				for( i=0;i<10;i++)
				{
					usart2_send(stop_cmd[i]);
				}
				delay_ms(2000);
				//后
				for( i=0;i<10;i++)
				{
					usart2_send(backward_cmd[i]);
				}
				delay_ms(2000);
				//停
				for( i=0;i<10;i++)
				{
					usart2_send(stop_cmd[i]);
				}
				delay_ms(2000);
				
				
				//左
				for( i=0;i<10;i++)
				{
					usart2_send(turn_left_cmd[i]);
				}
				delay_ms(2000);
				//停
				for( i=0;i<10;i++)
				{
					usart2_send(stop_cmd[i]);
				}
				delay_ms(2000);
				//右
				for( i=0;i<10;i++)
				{
					usart2_send(turn_right_cmd[i]);
				}
				delay_ms(2000);
				//停
				for( i=0;i<10;i++)
				{
					usart2_send(stop_cmd[i]);
				}
				delay_ms(2000);
		} 
}
















