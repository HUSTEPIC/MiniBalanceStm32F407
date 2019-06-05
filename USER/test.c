#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart2.h"
#include "can.h"
#include "timer.h"


//------------------------����С������---------------------------------
//����
u8 forward_cmd[10] = 	{0xff, 0xfe, 0x01 ,0x00 ,0x00, 0x00, 0x12, 0x00, 0x00 ,0x00};
u8 backward_cmd[10] = 	{0xff, 0xfe, 0x01 ,0x00 ,0x00, 0x00, 0x12, 0x00, 0x00 ,0x02};

u8 stop_cmd[10] = 		{0xff, 0xfe, 0x01 ,0x00 ,0x00, 0x00, 0x00, 0x00, 0x00 ,0x00};

u8 turn_left_cmd[10] = 		{0xff, 0xfe, 0x01 ,0x00 ,0x00, 0x00, 0x00, 0x00, 0x12 ,0x01};
u8 turn_right_cmd[10] = 		{0xff, 0xfe, 0x01 ,0x00 ,0x00, 0x00, 0x00, 0x00, 0x12 ,0x00};
//-------


u8 Way_Angle=1;                             //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_Direction=0; //����ң����صı���
u8 Flag_Stop=1,Flag_Show=0;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Encoder_A,Encoder_B,Encoder_C;             //���������������
int Encoder_A_EXTI;
int Motor_A,Motor_B,Motor_C;                   //���PWM����
int Target_A,Target_B,Target_C;                   //���Ŀ���ٶ�
int Temperature;                            //��ʾ�¶�
int Voltage;                                //��ص�ѹ������صı���
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
float Show_Data_Mb;                         //ȫ����ʾ������������ʾ��Ҫ�鿴������
//u32 Distance;                               //��������࣬�����������timer�ﶨ����
u8 delay_50,delay_flag;         //Ĭ������£����������Ϲ��ܣ������û�����2s���Ͽ��Խ������ģʽ
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
	//Stm32_Clock_Init(9);            //=====ϵͳʱ������ ������������������һ������
	Stm32_Clock_Init(336,8,2,7);//����ʱ��
	delay_init(72);                 //=====��ʱ��ʼ��
  uart_init(72,128000);           //=====��ʼ������1
	//
  //usart2_init(36,115200);            //=====����2��ʼ��
	usart2_init(42,115200);            //=====����2��ʼ��,ժ������ͷ��Ŀ
	//Timer1_Init(499,7199);  //��仰meifanyign �ĳ��������
	//TIM5_CH1_Cap_Init(499,7199);
	CAN1_Mode_Init(1,2,3,6,0);  //CAN��ʼ��
	
	while(1)
		{    
				int i;
				usart_send(0xff);
				
				//ǰ
				for( i=0;i<10;i++)
				{
					usart2_send(forward_cmd[i]);
				}
				delay_ms(2000);
				//ͣ
				for( i=0;i<10;i++)
				{
					usart2_send(stop_cmd[i]);
				}
				delay_ms(2000);
				//��
				for( i=0;i<10;i++)
				{
					usart2_send(backward_cmd[i]);
				}
				delay_ms(2000);
				//ͣ
				for( i=0;i<10;i++)
				{
					usart2_send(stop_cmd[i]);
				}
				delay_ms(2000);
				
				
				//��
				for( i=0;i<10;i++)
				{
					usart2_send(turn_left_cmd[i]);
				}
				delay_ms(2000);
				//ͣ
				for( i=0;i<10;i++)
				{
					usart2_send(stop_cmd[i]);
				}
				delay_ms(2000);
				//��
				for( i=0;i<10;i++)
				{
					usart2_send(turn_right_cmd[i]);
				}
				delay_ms(2000);
				//ͣ
				for( i=0;i<10;i++)
				{
					usart2_send(stop_cmd[i]);
				}
				delay_ms(2000);
		} 
}
















