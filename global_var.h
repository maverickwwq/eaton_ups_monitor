#define GLOBAL_VAR_H

#ifndef UPSINFO_STRUCTURE_H
#define UPSINFO_STRUCTURE_H
#include "upsinfo_structure.h"
#endif

#ifndef GTK_H
#define GTK_H
#include "gtk/gtk.h"
#endif
//****************************************************************************************************************
//AUTHOR:KIMI WANG
//DATE:2013-03-04
//DESCRIPTION:����ȫ�ֱ���
//****************************************************************************************************************


//-------------------------------------------------------------------------------------------
//---------------------------------UPS ������------------------------------------------------
//-------------------------------------------------------------------------------------------
//���������ascii��ʽ��Ϊת������������ÿռ䣬��Ϊ��������յ��������ÿռ�
//_DECODE��׺���ַ����洢ʵ�ʷ��ͳ�ȥ���ַ�

const char UPS_COMMUNICATION_INI[]="16";			//UPSͨ�ų�ʼ��
char UPS_COMMUNICATION_INI_DECODE[2]={0};			//ʵ�ʷ��͵�����+һ���ֽڵ�NULL

const char UPS_CMD_ACCEPT[]="06";						//ȷ�Ͻ��յ�ups���͵�����
char UPS_CMD_ACCEPT_DECODE[2]={0};						//

const char UPS_CMD_01[]="8188A101010300001200B0";	//UPS��س��״̬
char UPS_CMD_01_DECODE[sizeof(UPS_CMD_01)+1]={0};	//ʵ�ʷ��͵�����+NULL

const char UPS_CMD_02[]="8188A101020300001200B3";	//UPS ����״̬��Ϣ
char UPS_CMD_02_DECODE[sizeof(UPS_CMD_02)/2+1]={0};	//ʵ�ʷ��͵��ֽ�+NULL

const char UPS_CMD_03[]="8188A101030300001200B2";	//���Ⱥ��¶�
char UPS_CMD_03_DECODE[sizeof(UPS_CMD_03)+1]={0};	//ʵ�ʷ��͵�����+NULL

const char UPS_CMD_06[]="8188A101060300001200B7";	//���ʣ��������ʣ��ʱ��
char UPS_CMD_06_DECODE[sizeof(UPS_CMD_06)+1]={0};	//ʵ�ʷ��͵�����+NULL

const char UPS_CMD_07[]="8188A101070300001200B6";	//���ذٷֱȡ���ص�ѹ
char UPS_CMD_07_DECODE[sizeof(UPS_CMD_07)+1]={0};	//

const char UPS_CMD_24[]="8188A10124030000120095";	//����Լ�״̬
char UPS_CMD_24_DECODE[sizeof(UPS_CMD_24)+1]={0};	//ʵ�ʷ�������+NULL

const char UPS_CMD_27[]="8188A10127030000120096";	//������ӡ��������
char UPS_CMD_27_DECODE[sizeof(UPS_CMD_27)+1]={0};	//

const char UPS_CMD_31[]="8188A10131030000120080";	//�е�Ƶ�ʡ���ѹ
char UPS_CMD_31_DECODE[sizeof(UPS_CMD_31)+1]={0};	//

const char UPS_CMD_32[]="8188A10132030000120083";	//UPS����ģʽ
char UPS_CMD_32_DECODE[sizeof(UPS_CMD_32)+1]={0};	//

const char UPS_CMD_3B[]="8188A1013B03000012008A";	//��ع���ģʽ
char UPS_CMD_3B_DECODE[sizeof(UPS_CMD_3B)+1]={0};	//

const char UPS_CMD_42[]="8188A101420300001200F3";	//���Ƶ�ʣ����va��������������watt
char UPS_CMD_42_DECODE[sizeof(UPS_CMD_42)+1]={0};	//






//-------------------------------------------------------------------------------------------
//--------------------------------���ڳ�ʼ������---------------------------------------------
//-------------------------------------------------------------------------------------------
const char _24_N_8_1[]="baud=2400 parity=N data=8 stop=1";//2400bps,None parity,8bit datas,1 bit stop
const char _48_N_8_1[]="baud=4800 parity=N data=8 stop=1";
const char _96_N_8_1[]="baud=9600 parity=N data=8 stop=1";
const char _1152_N_8_1[]="baud=115200 parity=N data=8 stop=1";

//-------------------------------------------------------------------------------------------
//--------------------------------���ڵ��Բ���-----------------------------------------------
//-------------------------------------------------------------------------------------------
unsigned long	CHECK_TIME=4;									 //���ڷ��ͽ��մ�����ԵĴ���
/*
#define READ_INTERVAL 5
#define READ_MULTIPLIER 15
#define READ_CONSTANT 15
#define WRITE_MULTIPLIER 10
#define WRITE_CONSTANT 10
*/
//-------------------------------------------------------------------------------------------
//--------------------------------UPS���ȫ�ֱ���--------------------------------------------
//-------------------------------------------------------------------------------------------

#ifdef _DEBUG_
#define NUM_OF_UPS	1
#else
#define	NUM_OF_UPS	4
#endif


struct _UPS_STATE _2023ups[NUM_OF_UPS];


//-------------------------------------------------------------------------------------------
//--------------------------------ͼ�ν���ȫ�ֱ���-------------------------------------------
//-------------------------------------------------------------------------------------------
const char *frames[]={	"��ѡһ����UPS"	,	"Ku����UPS"	,	"C����UPS"	,	"�һ���UPS"	};
const char *items[]={	"ͨ��״̬"	,	"UPS״̬"	,	"�е�״̬"	,	"�е��ѹ"	,\
		"�е�Ƶ��"	,	"��ع���ģʽ"	,	"���ʣ������"	,	"�����ѹ"	,	"���Ƶ��"	};
GtkWidget *itemValue[4][11];						//4 ��ups 9��������ʾ


const unsigned int REFRESH_PER_X_SECONDS=10;			//ͼ�ν�����Բ���



//---------------------------------------------------------------------------------
//----------------------------ϵͳ��������-----------------------------------------
//---------------------------------------------------------------------------------

#define ALARM_NOT_CONNECT			"alarm\\communicate_error.wav"
#define ALARM_UPS_ERROR				"alarm\\UPS_ERROR.wav"
#define ALARM_INPUT_ERROR			"alarm\\input_error.wav"
#define ALARM_BATTERY_DISCHARGE		"alarm\\bat_discharge.wav"