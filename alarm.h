#define ALARM_H

#ifndef MMSYSTEM_H
#include "mmsystem.h"
#endif
//---------------------------------------------------------------------------------------
//Author:Kimi Wang
//Date:2013-3-24
//Descri:�����������ļ�
//
//---------------------------------------------------------------------------------------
void makeSound(char * fileName);

void makeSound(char * fileName){
	PlaySound((char*)fileName,NULL,SND_ASYNC|SND_FILENAME);		//�첽��ʽ��������
}