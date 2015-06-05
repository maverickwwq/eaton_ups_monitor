#define ALARM_H

#ifndef MMSYSTEM_H
#include "mmsystem.h"
#endif
//---------------------------------------------------------------------------------------
//Author:Kimi Wang
//Date:2013-3-24
//Descri:播放声音的文件
//
//---------------------------------------------------------------------------------------
void makeSound(char * fileName);

void makeSound(char * fileName){
	PlaySound((char*)fileName,NULL,SND_ASYNC|SND_FILENAME);		//异步方式产生声音
}