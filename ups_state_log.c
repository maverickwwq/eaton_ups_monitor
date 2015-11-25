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
//exceptionCode �����쳣������룬exceptionSolved ��ʾ�쳣�Ƿ��� true�����쳣�ѽ����false�����쳣����
//exceptionCode:
//				"1" �е��ѹ����������趨ֵ
//				"2" �е�Ƶ�ʳ���������趨ֵ
//				"3"	�е�Ͽ�
//				"4" ups����
//				"5" ups�����ѹ����������趨ֵ
//				"6" ups���Ƶ�ʳ���������趨ֵ
//				"7" ups���ع��ʳ���������趨ֵ
//				"8" ups������������趨ֵ
//				"9" ups��ص��������趨ֵ
//				"10"ups��ص�ѹ�����趨ֵ
//				"11"ups��·ʹ��
//
//


//				"50"����ͨ���쳣

_Bool exceptionLog(int exceptionCode,_Bool exceptionSolved,int upsNo){
	extern const char *frames[];
	time_t time_seconds;
	struct tm *t;
	time_seconds=time(NULL);
	t=localtime(&time_seconds);
	FILE *logFile=fopen("log.txt","a+");//a+ �Ը��ӷ�ʽ�򿪿ɶ�д���ļ������ļ������ڣ���Ὠ�����ļ���
										//����ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�󣬼��ļ�ԭ�ȵ����ݻ�
										//�������� ��ԭ����EOF����������
	fprintf(logFile,"%4d-%02d-%02d %02d:%02d:%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	switch (exceptionCode)	{
		case 1:
			fprintf(logFile," %s\t:�е��ѹ����������趨ֵ",frames[upsNo]);
			break;
		case 2:
			fprintf(logFile," %s\t:�е�Ƶ�ʳ���������趨ֵ",frames[upsNo]);
			break;
		case 3:
			fprintf(logFile," %s\t:�е�Ͽ�",frames[upsNo]);
			break;
		case 4:
			fprintf(logFile," %s\t:ups����",frames[upsNo]);
			break;
		case 5:
			fprintf(logFile," %s\t:ups�����ѹ����������趨ֵ",frames[upsNo]);
			break;
		case 6:
			fprintf(logFile," %s\t:ups���Ƶ�ʳ���������趨ֵ",frames[upsNo]);
			break;
		case 7:
			fprintf(logFile," %s\t:ups���ع��ʳ���������趨ֵ",frames[upsNo]);
			break;
		case 8:
			fprintf(logFile," %s\t:ups������������趨ֵ",frames[upsNo]);
			break;
		case 9:
			fprintf(logFile," %s\t:ups��ص��������趨ֵ",frames[upsNo]);
			break;
		case 10:
			fprintf(logFile," %s\t:ups��ص�ѹ�����趨ֵ",frames[upsNo]);
			break;
		case 11:
			fprintf(logFile," %s\t:ups��·ʹ��",frames[upsNo]);
			break;
		case 50:
			fprintf(logFile," %s\t:upsͨ�Ź���",frames[upsNo]);
			break;
		default:
			break;
	}
	if(exceptionSolved	== TRUE){
		fprintf(logFile,"�쳣�ָ�\n");
	}
	else{
		fprintf(logFile,"�쳣\n");
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
