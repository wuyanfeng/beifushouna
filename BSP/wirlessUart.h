#ifndef _WIRLESS_UART_H
#define _WIRLESS_UART_H

#define WIRLESS_UART_IN_PORT	GPIOC
#define WIRLESS_UART_OUT_PORT	GPIOB

#define WIRLESS_UART_AUX	GPIO_Pin_12
#define WIRLESS_UART_M0		GPIO_Pin_14
#define WIRLESS_UART_M1		GPIO_Pin_15

typedef enum{Normal,Wakeup,LowPower,Sleep}WIRLESS_MODE;
typedef INT8U	WirlessSendByte ;
typedef INT8U	WirlessErr;

////////////////////////////ģ�����ò���////////////////////////////////
enum
{
	AirSpeed_1_2_k,
	AirSpeed_2_4_k,
	AirSpeed_4_8_k,
	AirSpeed_9_6_k,
	AirSpeed_19_2_k,
	AirSpeed_38_4_k,
	AirSpeed_50_k,
	AirSpeed_70_k
};
////////////////////////////////���ڲ�����////////////////////
enum
{
	UartBps1200,
	UartBps2400,
	UartBps4800,
	UartBps9600,
	UartBps19200,
	UartBps38400,
	UartBps57600,
	UartBps115200
};
////////////////////////////////У��λ////////////////////
enum
{
	UartVarify8N1,
	UartVarify8O1,
	UartVarify8E1,
	UartVarify8N1_1
};
////////////////////////////////���书��////////////////////
enum
{
	SendPower17dBm,
	SendPower14dBm,
	SendPower10dBm,
	SendPower7dBm
};
////////////////////////////////FEC(ǰ�����)////////////////////
enum
{
	FecClose,
	FecOpen
};
////////////////////////////////����ʱ��////////////////////
enum
{
	WakeTime250ms,
	WakeTime500ms,
	WakeTime750ms,
	WakeTime1000ms,
	WakeTime1250ms,
	WakeTime1500ms,
	WakeTime1750ms,
	WakeTime2000ms,
};
////////////////////////////////IO������ʽ////////////////////
enum
{
	IODriveModePUD,
	IODriveModeOC
};
////////////////////////////////���㷢��ʹ��////////////////////
enum
{
	DirectedSendDisable,
	DirectedSendEnable
};

typedef struct 
{
  	INT8U	AddrH;	  //ģ���ַ���ֽ�
	INT8U	AddrL;	  //ģ���ַ���ֽ�
	INT8U	AirSpeed;	  //ͨ�����ʣ��������ʵ�
	INT8U	UartBps;
	INT8U	UartVarify;
	INT8U	SendPower;
	INT8U	FecSwitch;
	INT8U	WakeTime;
	INT8U	IODriveMode;
	INT8U	DirectedSend;
	INT8U	Channel; //�����ŵ�0~63
}WirlessSetStruct;


#define GetAUXStatus()					GPIO_ReadInputDataBit(WIRLESS_UART_IN_PORT,WIRLESS_UART_AUX)

#define WaitSendComplete(err);				OSFlagPend(Uart_Flags,USART2_T_FLAG,OS_FLAG_WAIT_SET_OR,1000,&err);
#define SendData(msg);						USARTx_SendData(USART2,&msg);//���ͼĴ�������
#define ChangeBaud();						UART2_Init(9600);
#define ResumeBaud();						UART2_Init(UART2_BAUD);

void WirlessModeSet(WIRLESS_MODE mode);
void SetWirlessParaSave(WirlessSetStruct para);
void SetWirlessParaUnSave(WirlessSetStruct para);
void WirlessReset(void);

#endif
