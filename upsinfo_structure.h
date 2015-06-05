#define UPSINFO_STRUCTURE_H

#ifndef WINDOWS_H
#define _WIN32_WINNT 0x0400	
#include <windows.h>
#endif

//****************************************************************************************************************
//AUTHOR:KIMI WANG
//DATE:2013-03-07
//DESCRIPTION:   定义ups状态结构体
//****************************************************************************************************************






//--------------------------------------------------------------------------------------------------
//--------------------------------------UPS状态结构体-----------------------------------------------
//--------------------------------------------------------------------------------------------------
typedef struct	_UPS_STATE {
	//--------------------ups总体信息----------------------------------------------
	char	UPS_NAME[40];			//UPS标示符
	HANDLE	UPS_COM_HANDLE;			//该UPS占用的COM口HANDLE
	bool	UPS_SET_ACTIVE;			//UPS是否被设置为启用
	bool	UPS_COMMUNICATE_NORMAL;	//通信正常
	bool	UPS_ERROR;				//TRUE FOR error,FALSE FOR NORMAL
	bool	SHUTDOWN_MODE;			//TRUE FOR SHUTDOWN,FALSE FOR OTHER MODE
	bool	OVERHEAT;				//ups过温;TRUE FOR YES
	bool	UPS_ALARM_ENABLE;		//使能报警声音
	int		LINK_COM_NUM;			//该UPS所连接的COM口号
	//--------------------市电信息-------------------------------------------------
	bool	INPUT_POWER_ABNORMAL;		//市电异常	true for abnormal ,false for normal
	bool	INPUT_POWER_MODE;			//TRUE FOR 市电,FALSE FOR 非市电供电
	bool	INPUT_FREQUENCY_ABNORMAL;	//TRUE FOR ABNORMAL
	bool	INPUT_VOLTAGE_ABNORMAL;		//TRUE FOR ABNORMAL
	unsigned int	INPUT_VOLTAGE;				//市电电压
	unsigned char	INPUT_FREQUENCY;			//市电频率
	//--------------------电池信息-------------------------------------------------
	bool	BATTERY_MODE;		//TRUE FOR 电池供电模式,FALSE FOR 非电池供电模式
	bool	DISCHARGE;			//电池放电状态 true for diacharge
	bool	BATTERY_LINK_STATE;	//电池连接状态
	BOOL	BATTERY_LOW_VOLTAGE;//电池低压
	char	BATTERY_VOLTATE;	//电池电压
	char	BATTERY_CAPACITY;	//电池剩余容量 %xx
	char	BATTERY_NUM;		//电池节数 3:1k 6:2k 8:3k
	char	BATTERY_SELFTEST;	//1:OK 3:self test failed 5:self testing 6:other state
	char	OVERCHARGE;			//过冲 1:over charge 0:no
	bool	CHARGER_ERROR;		//1:ERROR	0:NO
	int		BATTERY_REMAIN_TIME;//剩余时间		
	//--------------------输出信息-------------------------------------------------
	bool	OVERLOAD;				//TRUE FOR OVERLOAD
	char	LOAD_PERCEN;			//负载百分比
	unsigned int	OUTPUT_VOLTAGE;	//输出电压
	char	OUTPUT_FREQUENCY;		//输出频率	
	unsigned int	OUTPUT_WATT;	//输出功率
	unsigned int	OUTPUT_VA;		//输出VA
	float	OUTPUT_CURRENT;			//输出电流
	
	//--------------------风扇----------------------------------------------------
	bool	FAN_ERROR;			//TRUE FOR ERROR
	//--------------------旁路----------------------------------------------------
	bool	BYPASS_MODE;		//TRUE FOR YES
	bool	BYPASS_FREQUENCY_NORMAL;//TRUE FOR NORMAL
	bool	BYPASS_NORMAL;			//TRUE:BYPASS NORMAL
	bool	BYPASS_VOLTAGE_NORMAL;	//TRUE:VOLTAGE NORMAL

	//------------------发送命令后所得到的应答------------------------------------
	char UPS_COMMUNICATION_INI_ANSWER[3];			//实际接受到的数据+一个字节的NULL
	char UPS_CMD_ACCEPT_ANSWER[2];
	char UPS_CMD_01_ANSWER[11];					//实际接受到的数据+NULL
	char UPS_CMD_02_ANSWER[10];						//实际接受到的数据+NULL
	char UPS_CMD_03_ANSWER[9];						//实际接收到的数据+NULL
	char UPS_CMD_06_ANSWER[11];					//实际接收的数据+NULL
	char UPS_CMD_07_ANSWER[9];					//实际接收到的数据+NULL
	char UPS_CMD_24_ANSWER[7];						//实际接收数据+NULL
	char UPS_CMD_27_ANSWER[9];						//
	char UPS_CMD_31_ANSWER[9];						//
	char UPS_CMD_32_ANSWER[10];						//
	char UPS_CMD_3B_ANSWER[6];						//
	char UPS_CMD_42_ANSWER[18];						//
	
	//------------------命令的确认------------------------------------------------
	BOOL CMD_01_CHECK;
	BOOL CMD_02_CHECK;
	BOOL CMD_03_CHECK;
	BOOL CMD_06_CHECK;
	BOOL CMD_07_CHECK;
	BOOL CMD_24_CHECK;
	BOOL CMD_27_CHECK;
	BOOL CMD_31_CHECK;
	BOOL CMD_32_CHECK;
	BOOL CMD_3B_CHECK;
	BOOL CMD_42_CHECK;
} UPS_STATE;