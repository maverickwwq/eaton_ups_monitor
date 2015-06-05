#define UPSINFO_STRUCTURE_H

#ifndef WINDOWS_H
#define _WIN32_WINNT 0x0400	
#include <windows.h>
#endif

//****************************************************************************************************************
//AUTHOR:KIMI WANG
//DATE:2013-03-07
//DESCRIPTION:   ����ups״̬�ṹ��
//****************************************************************************************************************






//--------------------------------------------------------------------------------------------------
//--------------------------------------UPS״̬�ṹ��-----------------------------------------------
//--------------------------------------------------------------------------------------------------
typedef struct	_UPS_STATE {
	//--------------------ups������Ϣ----------------------------------------------
	char	UPS_NAME[40];			//UPS��ʾ��
	HANDLE	UPS_COM_HANDLE;			//��UPSռ�õ�COM��HANDLE
	bool	UPS_SET_ACTIVE;			//UPS�Ƿ�����Ϊ����
	bool	UPS_COMMUNICATE_NORMAL;	//ͨ������
	bool	UPS_ERROR;				//TRUE FOR error,FALSE FOR NORMAL
	bool	SHUTDOWN_MODE;			//TRUE FOR SHUTDOWN,FALSE FOR OTHER MODE
	bool	OVERHEAT;				//ups����;TRUE FOR YES
	bool	UPS_ALARM_ENABLE;		//ʹ�ܱ�������
	int		LINK_COM_NUM;			//��UPS�����ӵ�COM�ں�
	//--------------------�е���Ϣ-------------------------------------------------
	bool	INPUT_POWER_ABNORMAL;		//�е��쳣	true for abnormal ,false for normal
	bool	INPUT_POWER_MODE;			//TRUE FOR �е�,FALSE FOR ���е繩��
	bool	INPUT_FREQUENCY_ABNORMAL;	//TRUE FOR ABNORMAL
	bool	INPUT_VOLTAGE_ABNORMAL;		//TRUE FOR ABNORMAL
	unsigned int	INPUT_VOLTAGE;				//�е��ѹ
	unsigned char	INPUT_FREQUENCY;			//�е�Ƶ��
	//--------------------�����Ϣ-------------------------------------------------
	bool	BATTERY_MODE;		//TRUE FOR ��ع���ģʽ,FALSE FOR �ǵ�ع���ģʽ
	bool	DISCHARGE;			//��طŵ�״̬ true for diacharge
	bool	BATTERY_LINK_STATE;	//�������״̬
	BOOL	BATTERY_LOW_VOLTAGE;//��ص�ѹ
	char	BATTERY_VOLTATE;	//��ص�ѹ
	char	BATTERY_CAPACITY;	//���ʣ������ %xx
	char	BATTERY_NUM;		//��ؽ��� 3:1k 6:2k 8:3k
	char	BATTERY_SELFTEST;	//1:OK 3:self test failed 5:self testing 6:other state
	char	OVERCHARGE;			//���� 1:over charge 0:no
	bool	CHARGER_ERROR;		//1:ERROR	0:NO
	int		BATTERY_REMAIN_TIME;//ʣ��ʱ��		
	//--------------------�����Ϣ-------------------------------------------------
	bool	OVERLOAD;				//TRUE FOR OVERLOAD
	char	LOAD_PERCEN;			//���ذٷֱ�
	unsigned int	OUTPUT_VOLTAGE;	//�����ѹ
	char	OUTPUT_FREQUENCY;		//���Ƶ��	
	unsigned int	OUTPUT_WATT;	//�������
	unsigned int	OUTPUT_VA;		//���VA
	float	OUTPUT_CURRENT;			//�������
	
	//--------------------����----------------------------------------------------
	bool	FAN_ERROR;			//TRUE FOR ERROR
	//--------------------��·----------------------------------------------------
	bool	BYPASS_MODE;		//TRUE FOR YES
	bool	BYPASS_FREQUENCY_NORMAL;//TRUE FOR NORMAL
	bool	BYPASS_NORMAL;			//TRUE:BYPASS NORMAL
	bool	BYPASS_VOLTAGE_NORMAL;	//TRUE:VOLTAGE NORMAL

	//------------------������������õ���Ӧ��------------------------------------
	char UPS_COMMUNICATION_INI_ANSWER[3];			//ʵ�ʽ��ܵ�������+һ���ֽڵ�NULL
	char UPS_CMD_ACCEPT_ANSWER[2];
	char UPS_CMD_01_ANSWER[11];					//ʵ�ʽ��ܵ�������+NULL
	char UPS_CMD_02_ANSWER[10];						//ʵ�ʽ��ܵ�������+NULL
	char UPS_CMD_03_ANSWER[9];						//ʵ�ʽ��յ�������+NULL
	char UPS_CMD_06_ANSWER[11];					//ʵ�ʽ��յ�����+NULL
	char UPS_CMD_07_ANSWER[9];					//ʵ�ʽ��յ�������+NULL
	char UPS_CMD_24_ANSWER[7];						//ʵ�ʽ�������+NULL
	char UPS_CMD_27_ANSWER[9];						//
	char UPS_CMD_31_ANSWER[9];						//
	char UPS_CMD_32_ANSWER[10];						//
	char UPS_CMD_3B_ANSWER[6];						//
	char UPS_CMD_42_ANSWER[18];						//
	
	//------------------�����ȷ��------------------------------------------------
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