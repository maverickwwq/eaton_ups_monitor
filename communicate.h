#define COMMUNICATE_H

#ifndef GLOBAL_VAR_H 
#include "global_var.h"
#endif

//****************************************************************************************************************
//AUTHOR:KIMI WANG
//DATE:2013-03-07
//DESCRIPTION:      ���dxrt1-3k�ͺ�ups�Ĵ���ͨѶЭ�飬�������Ͳ��ʺ�
//					��ups������Ӧ�������ԭʼ���ݴ�ŵ���Ӧλ��
//****************************************************************************************************************

extern DWORD CHECK_TIME;

//��ups������Ӧ�������ԭʼ���ݱ��浽��Ӧ�Ĵ洢��
BOOL sendCMD(HANDLE hCom,const char* cmd,DWORD bytesToRead);




BOOL sendCMD(HANDLE hCom,const char* original_cmd,const char* decode_cmd,char* answer,DWORD bytesToRead){
	unsigned int length=strlen(original_cmd);				//��ʼ����ĳ���
	DWORD writtenBytes=0,readBytes=0,doIt=CHECK_TIME;
	if(bytesToRead == 0){										//ֻ���Ͳ���������
		while( (doIt--) && (writtenBytes!=length/2) ){
			writtenBytes=writeToCom(hCom,decode_cmd,length/2);
			readFromCom(hCom,NULL,0);
		}
		goto End;
	}
	doIt=CHECK_TIME;
	while(	(doIt--)>0 && (readBytes<bytesToRead) ){
		Sleep(50);
		printf(".");
		writtenBytes=writeToCom(hCom,decode_cmd,length/2);	//���ͳ�ʼ����һ�볤�ȵ�����
		readBytes=readFromCom(hCom,answer,bytesToRead);
	}
printf("Write %d bytes\n",writtenBytes);
printf("Read %d bytes\n",readBytes);

End:
	if( doIt == -1 )
		return FALSE;
	else
		return TRUE;
}
