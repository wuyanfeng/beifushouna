#include "includes.h"
static WirlessSendByte dataBuf[6]={0xc0,0x00,0x00,0x00,0x00,0x00};

/*******************************************************************************
* ������  : WirlessModeSet
* ����    : ����ģʽ����
* ����    : ģʽ����
* ���    : ��
* ����    : �� 
* ˵��    : 
*******************************************************************************/
void WirlessModeSet(WIRLESS_MODE mode)
{
	switch(mode)
	{
		case Normal:
			GPIO_ResetBits(WIRLESS_UART_OUT_PORT,WIRLESS_UART_M0);	  
			GPIO_ResetBits(WIRLESS_UART_OUT_PORT,WIRLESS_UART_M1);
			break;
		case Wakeup:
			GPIO_SetBits(WIRLESS_UART_OUT_PORT,WIRLESS_UART_M0);	   
			GPIO_ResetBits(WIRLESS_UART_OUT_PORT,WIRLESS_UART_M1);
			break;
		case LowPower:
			GPIO_ResetBits(WIRLESS_UART_OUT_PORT,WIRLESS_UART_M0);
			GPIO_SetBits(WIRLESS_UART_OUT_PORT,WIRLESS_UART_M1);
			break;
		case Sleep:
			GPIO_SetBits(WIRLESS_UART_OUT_PORT,WIRLESS_UART_M0);
			GPIO_SetBits(WIRLESS_UART_OUT_PORT,WIRLESS_UART_M1);
			break;
		default:
			break;
	}
}
/*******************************************************************************
* ������  : SetWirlessParaSave
* ����    : �������߲��������籣��
* ����    : ���ò����ṹ
* ���    : ��
* ����    : �� 
* ˵��    :
*******************************************************************************/
void SetWirlessParaSave(WirlessSetStruct para)
{
	Uart_Send_Data_Struct  msg;
	WirlessErr	err;

	WirlessModeSet(Sleep);
	ChangeBaud();
	dataBuf[0] = 0xc0;
	dataBuf[1] = para.AddrH;
	dataBuf[2] = para.AddrL;
	dataBuf[3] = para.AirSpeed | (para.UartBps << 3) | (para.UartVarify << 6);
	dataBuf[4] = para.Channel & 0x3f; 
	dataBuf[5] = para.SendPower | (para.FecSwitch << 2) | (para.WakeTime << 3) | (para.IODriveMode << 6) | (para.DirectedSend << 7);
	msg.dataLen = 6;
	msg.dataPoint = dataBuf;

	SendData(msg);
	WaitSendComplete(err);	
	WirlessModeSet(Normal);
	ResumeBaud();
}
/*******************************************************************************
* ������  : SetWirlessParaUnSave
* ����    : �������߲��������粻����
* ����    : ���ò����ṹ
* ���    : ��
* ����    : �� 
* ˵��    :
*******************************************************************************/
void SetWirlessParaUnSave(WirlessSetStruct para)
{
	Uart_Send_Data_Struct  msg;
	WirlessErr	err;

	WirlessModeSet(Sleep);
	ChangeBaud();
	dataBuf[0] = 0xc2;
	dataBuf[1] = para.AddrH;
	dataBuf[2] = para.AddrL;
	dataBuf[3] = para.AirSpeed | (para.UartBps << 3) | (para.UartVarify << 6);
	dataBuf[4] = para.Channel & 0x3f; 
	dataBuf[5] = para.SendPower | (para.FecSwitch << 2) | (para.WakeTime << 3) | (para.IODriveMode << 6) | (para.DirectedSend << 7);
	msg.dataLen = 6;
	msg.dataPoint = dataBuf;

	SendData(msg);
	WaitSendComplete(err);	
	WirlessModeSet(Normal);
	ResumeBaud();
}
/*******************************************************************************
* ������  : WirlessReset
* ����    : ����ģ�鸴λ
* ����    : 
* ���    : ��
* ����    : �� 
* ˵��    :
*******************************************************************************/
void WirlessReset(void)
{
	Uart_Send_Data_Struct  msg;
	WirlessErr	err;
	WirlessModeSet(Sleep);
	ChangeBaud();

	dataBuf[0] = 0xc4;
	dataBuf[1] = 0xc4;
	dataBuf[2] = 0xc4;
	dataBuf[3] = 0xc4;

	msg.dataLen = 4;
	msg.dataPoint = dataBuf;

	SendData(msg);
	WaitSendComplete(err);	
	WirlessModeSet(Normal);
	ResumeBaud();
}
