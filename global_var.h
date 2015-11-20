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
//DESCRIPTION:定义全局变量
//****************************************************************************************************************


//-------------------------------------------------------------------------------------------
//---------------------------------UPS 命令字------------------------------------------------
//-------------------------------------------------------------------------------------------
//保存命令的ascii格式，为转化后的命令设置空间，并为该命令接收的数据设置空间
//_DECODE后缀的字符串存储实际发送出去的字符

const char UPS_COMMUNICATION_INI[]="16";			//UPS通信初始化
char UPS_COMMUNICATION_INI_DECODE[2]={0};			//实际发送的数据+一个字节的NULL

const char UPS_CMD_ACCEPT[]="06";						//确认接收到ups发送的数据
char UPS_CMD_ACCEPT_DECODE[2]={0};						//

const char UPS_CMD_01[]="8188A101010300001200B0";	//UPS电池充电状态
char UPS_CMD_01_DECODE[sizeof(UPS_CMD_01)+1]={0};	//实际发送的数据+NULL

const char UPS_CMD_02[]="8188A101020300001200B3";	//UPS 故障状态信息
char UPS_CMD_02_DECODE[sizeof(UPS_CMD_02)/2+1]={0};	//实际发送的字节+NULL

const char UPS_CMD_03[]="8188A101030300001200B2";	//风扇和温度
char UPS_CMD_03_DECODE[sizeof(UPS_CMD_03)+1]={0};	//实际发送的数据+NULL

const char UPS_CMD_06[]="8188A101060300001200B7";	//电池剩余容量，剩余时间
char UPS_CMD_06_DECODE[sizeof(UPS_CMD_06)+1]={0};	//实际发送的数据+NULL

const char UPS_CMD_07[]="8188A101070300001200B6";	//负载百分比、电池电压
char UPS_CMD_07_DECODE[sizeof(UPS_CMD_07)+1]={0};	//

const char UPS_CMD_24[]="8188A10124030000120095";	//电池自检状态
char UPS_CMD_24_DECODE[sizeof(UPS_CMD_24)+1]={0};	//实际发送数据+NULL

const char UPS_CMD_27[]="8188A10127030000120096";	//电池连接、过冲情况
char UPS_CMD_27_DECODE[sizeof(UPS_CMD_27)+1]={0};	//

const char UPS_CMD_31[]="8188A10131030000120080";	//市电频率、电压
char UPS_CMD_31_DECODE[sizeof(UPS_CMD_31)+1]={0};	//

const char UPS_CMD_32[]="8188A10132030000120083";	//UPS工作模式
char UPS_CMD_32_DECODE[sizeof(UPS_CMD_32)+1]={0};	//

const char UPS_CMD_3B[]="8188A1013B03000012008A";	//电池供电模式
char UPS_CMD_3B_DECODE[sizeof(UPS_CMD_3B)+1]={0};	//

const char UPS_CMD_42[]="8188A101420300001200F3";	//输出频率，输出va，输出电流，输出watt
char UPS_CMD_42_DECODE[sizeof(UPS_CMD_42)+1]={0};	//






//-------------------------------------------------------------------------------------------
//--------------------------------串口初始化参数---------------------------------------------
//-------------------------------------------------------------------------------------------
const char _24_N_8_1[]="baud=2400 parity=N data=8 stop=1";//2400bps,None parity,8bit datas,1 bit stop
const char _48_N_8_1[]="baud=4800 parity=N data=8 stop=1";
const char _96_N_8_1[]="baud=9600 parity=N data=8 stop=1";
const char _1152_N_8_1[]="baud=115200 parity=N data=8 stop=1";

//-------------------------------------------------------------------------------------------
//--------------------------------串口调试参数-----------------------------------------------
//-------------------------------------------------------------------------------------------
unsigned long	CHECK_TIME=4;									 //串口发送接收错误后尝试的次数
/*
#define READ_INTERVAL 5
#define READ_MULTIPLIER 15
#define READ_CONSTANT 15
#define WRITE_MULTIPLIER 10
#define WRITE_CONSTANT 10
*/
//-------------------------------------------------------------------------------------------
//--------------------------------UPS相关全局变量--------------------------------------------
//-------------------------------------------------------------------------------------------

#ifdef _DEBUG_
#define NUM_OF_UPS	1
#else
#define	NUM_OF_UPS	4
#endif


struct _UPS_STATE _2023ups[NUM_OF_UPS];


//-------------------------------------------------------------------------------------------
//--------------------------------图形界面全局变量-------------------------------------------
//-------------------------------------------------------------------------------------------
const char *frames[]={	"四选一机柜UPS"	,	"Ku波段UPS"	,	"C波段UPS"	,	"乙机房UPS"	};
const char *items[]={	"通信状态"	,	"UPS状态"	,	"市电状态"	,	"市电电压"	,\
		"市电频率"	,	"电池工作模式"	,	"电池剩余容量"	,	"输出电压"	,	"输出频率"	};
GtkWidget *itemValue[4][11];						//4 个ups 9个参数显示


const unsigned int REFRESH_PER_X_SECONDS=10;			//图形界面调试参数



//---------------------------------------------------------------------------------
//----------------------------系统声音常量-----------------------------------------
//---------------------------------------------------------------------------------

#define ALARM_NOT_CONNECT			"alarm\\communicate_error.wav"
#define ALARM_UPS_ERROR				"alarm\\UPS_ERROR.wav"
#define ALARM_INPUT_ERROR			"alarm\\input_error.wav"
#define ALARM_BATTERY_DISCHARGE		"alarm\\bat_discharge.wav"