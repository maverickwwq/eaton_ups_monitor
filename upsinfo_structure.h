#define UPSINFO_STRUCTURE_H

#ifndef WINDOWS_H
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
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
	int 	READ_INTERVAL;			//----------------
	int		READ_MULTIPLIER;		//				  |	
	int		READ_CONSTANT;			//				  |---��upsʹ�õĴ�����ʹ�õ���Ӧ����
	int 	WRITE_MULTIPLIER;		//				  |
	int 	WRITE_CONSTANT;			//----------------
	_Bool	UPS_SET_ACTIVE;			//UPS�Ƿ�����Ϊ����
	_Bool	UPS_COMMUNICATE_NORMAL;	//ͨ������
	_Bool	UPS_ERROR;				//TRUE FOR error,FALSE FOR NORMAL
	_Bool	SHUTDOWN_MODE;			//TRUE FOR SHUTDOWN,FALSE FOR OTHER MODE
	_Bool	OVERHEAT;				//ups����;TRUE FOR YES
	_Bool	UPS_ALARM_ENABLE;		//ʹ�ܱ�������
	int		LINK_COM_NUM;			//��UPS�����ӵ�COM�ں�
	//--------------------�е���Ϣ-------------------------------------------------
	_Bool	INPUT_POWER_ABNORMAL;		//�е��쳣	true for abnormal ,false for normal
	_Bool	INPUT_POWER_MODE;			//TRUE FOR �е�,FALSE FOR ���е繩��
	_Bool	INPUT_FREQUENCY_ABNORMAL;	//TRUE FOR ABNORMAL
	_Bool	INPUT_VOLTAGE_ABNORMAL;		//TRUE FOR ABNORMAL
	unsigned int	INPUT_VOLTAGE;				//�е��ѹ
	unsigned char	INPUT_FREQUENCY;			//�е�Ƶ��
	//--------------------�����Ϣ-------------------------------------------------
	_Bool	BATTERY_MODE;		//TRUE FOR ��ع���ģʽ,FALSE FOR �ǵ�ع���ģʽ
	_Bool	DISCHARGE;			//��طŵ�״̬ true for diacharge
	_Bool	BATTERY_LINK_STATE;	//�������״̬
	_Bool	BATTERY_LOW_VOLTAGE;//��ص�ѹ
	char	BATTERY_VOLTATE;	//��ص�ѹ
	char	BATTERY_CAPACITY;	//���ʣ������ %xx
	char	BATTERY_NUM;		//��ؽ��� 3:1k 6:2k 8:3k
	char	BATTERY_SELFTEST;	//1:OK 3:self test failed 5:self testing 6:other state
	char	OVERCHARGE;			//���� 1:over charge 0:no
	_Bool	CHARGER_ERROR;		//1:ERROR	0:NO
	int		BATTERY_REMAIN_TIME;//ʣ��ʱ��		
	//--------------------�����Ϣ-------------------------------------------------
	_Bool	OVERLOAD;				//TRUE FOR OVERLOAD
	char	LOAD_PERCEN;			//���ذٷֱ�
	unsigned int	OUTPUT_VOLTAGE;	//�����ѹ
	char	OUTPUT_FREQUENCY;		//���Ƶ��	
	unsigned int	OUTPUT_WATT;	//�������
	unsigned int	OUTPUT_VA;		//���VA
	float	OUTPUT_CURRENT;			//�������
	
	//--------------------����----------------------------------------------------
	_Bool	FAN_ERROR;			//TRUE FOR ERROR
	//--------------------��·----------------------------------------------------
	_Bool	BYPASS_MODE;		//TRUE FOR YES
	_Bool	BYPASS_FREQUENCY_NORMAL;//TRUE FOR NORMAL
	_Bool	BYPASS_NORMAL;			//TRUE:BYPASS NORMAL
	_Bool	BYPASS_VOLTAGE_NORMAL;	//TRUE:VOLTAGE NORMAL

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
	_Bool CMD_01_CHECK;
	_Bool CMD_02_CHECK;
	_Bool CMD_03_CHECK;
	_Bool CMD_06_CHECK;
	_Bool CMD_07_CHECK;
	_Bool CMD_24_CHECK;
	_Bool CMD_27_CHECK;
	_Bool CMD_31_CHECK;
	_Bool CMD_32_CHECK;
	_Bool CMD_3B_CHECK;
	_Bool CMD_42_CHECK;
} UPS_STATE;