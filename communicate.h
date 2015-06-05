#define COMMUNICATE_H

#ifndef GLOBAL_VAR_H 
#include "global_var.h"
#endif

//****************************************************************************************************************
//AUTHOR:KIMI WANG
//DATE:2013-03-07
//DESCRIPTION:      针对dxrt1-3k型号ups的串口通讯协议，其他机型不适合
//					向ups发送相应命令，并将原始数据存放到相应位置
//****************************************************************************************************************

extern DWORD CHECK_TIME;

//向ups发送相应命令，并将原始数据保存到相应的存储区
BOOL sendCMD(HANDLE hCom,const char* cmd,DWORD bytesToRead);




BOOL sendCMD(HANDLE hCom,const char* original_cmd,const char* decode_cmd,char* answer,DWORD bytesToRead){
	unsigned int length=strlen(original_cmd);				//初始命令的长度
	DWORD writtenBytes=0,readBytes=0,doIt=CHECK_TIME;
	if(bytesToRead == 0){										//只发送不接受数据
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
		writtenBytes=writeToCom(hCom,decode_cmd,length/2);	//发送初始命令一半长度的数据
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
