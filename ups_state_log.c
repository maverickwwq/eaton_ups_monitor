#include <stdio.h>

#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H
#include "global_var.h"
#endif

#ifndef TIME_H
#define TIME_H
#include "time.h"
#endif

//------------------------------------------
//------------------------------------------
//2015/6/26 kimi wang
//_Bool exceptionLog(int exceptionCode,_Bool exceptionSolved)	
//exceptionCode 代表异常情况代码，exceptionSolved 表示异常是否解除 true代表异常已解除，false代表异常存在
//exceptionCode:
//				"1" 市电电压超过或低于设定值
//				"2" 市电频率超过或低于设定值
//				"3"	市电断开
//				"4" ups故障
//				"5" ups输出电压超过或低于设定值
//				"6" ups输出频率超过或低于设定值
//				"7" ups负载功率超过或低于设定值
//				"8" ups输出电流超过设定值
//				"9" ups电池电量低于设定值
//				"10"ups电池电压低于设定值
//				"11"ups旁路使能
//
//


//				"50"串口通信异常

_Bool exceptionLog(int exceptionCode,_Bool exceptionSolved,int upsNo){
	extern const char *frames[];
	time_t time_seconds;
	struct tm *t;
	time_seconds=time(NULL);
	t=localtime(&time_seconds);
	FILE *logFile=fopen("log.txt","a+");//a+ 以附加方式打开可读写的文件。若文件不存在，则会建立该文件，
										//如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会
										//被保留。 （原来的EOF符不保留）
	fprintf(logFile,"%4d-%02d-%02d %02d:%02d:%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	switch (exceptionCode)	{
		case 1:
			fprintf(logFile," %s\t:市电电压超过或低于设定值",frames[upsNo]);
			break;
		case 2:
			fprintf(logFile," %s\t:市电频率超过或低于设定值",frames[upsNo]);
			break;
		case 3:
			fprintf(logFile," %s\t:市电断开",frames[upsNo]);
			break;
		case 4:
			fprintf(logFile," %s\t:ups故障",frames[upsNo]);
			break;
		case 5:
			fprintf(logFile," %s\t:ups输出电压超过或低于设定值",frames[upsNo]);
			break;
		case 6:
			fprintf(logFile," %s\t:ups输出频率超过或低于设定值",frames[upsNo]);
			break;
		case 7:
			fprintf(logFile," %s\t:ups负载功率超过或低于设定值",frames[upsNo]);
			break;
		case 8:
			fprintf(logFile," %s\t:ups输出电流超过设定值",frames[upsNo]);
			break;
		case 9:
			fprintf(logFile," %s\t:ups电池电量低于设定值",frames[upsNo]);
			break;
		case 10:
			fprintf(logFile," %s\t:ups电池电压低于设定值",frames[upsNo]);
			break;
		case 11:
			fprintf(logFile," %s\t:ups旁路使能",frames[upsNo]);
			break;
		case 50:
			fprintf(logFile," %s\t:ups通信故障",frames[upsNo]);
			break;
		default:
			break;
	}
	if(exceptionSolved	== TRUE){
		fprintf(logFile,"异常恢复\n");
	}
	else{
		fprintf(logFile,"异常\n");
	}
	fclose(logFile);
}

_Bool softwareException(){
	return 1;
}

int main(int argc,char *argv[]){
	exceptionLog(1,TRUE,0);
	exceptionLog(1,FALSE,0);
	return 0;
}
