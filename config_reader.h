#ifndef CONFIG_READER_H
#define CONFIG_READER_H
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef MALLOC_H
#define MALLOC_H
#include <malloc.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//每行的最大字符数
#define MAX_CHAR_PER_LINE 100
#define MAX_CHAR_PER_PARA 40
#define MAX_CHAR_PER_CONF 40
//2015.10.21 kimi wang

//该结构体用来保存配置文件每行的字符串
typedef struct conf_line {
	char line_content[MAX_CHAR_PER_LINE];
	struct conf_line *next;
} CONF_LINE;

//该结构体用来保存参数名、数值
typedef struct conf_key_val {
	char key[MAX_CHAR_PER_PARA];
	char value[MAX_CHAR_PER_CONF];
	struct conf_key_val *next;
} KEY_VAL;


//该函数用来清除字符串中的空白字符
char* trimf(const char* src){
	int i=0,j=0;
	char *buf=(char*)malloc(MAX_CHAR_PER_LINE);
	while(src[i]!= NULL){
		switch(src[i]){
			case ' '	:
			case '\t'	:
			case '\n'	:
			case '\r'	:
				break;
			default		:
				buf[j++]=src[i];
		}
		i++;
	}
	buf[j]=NULL;
	return buf;
}



//
char* ignoreSharp(char* src){
	int i=0;
	while( src[i] != NULL ){
		if(src[i] == '#'){
			*(src+i)=NULL;
			break;
		}
		i++;
	}
	return src;
}



//该函数用来将配置文件中的字符串转换成存放在CONF_LINE的结构体中
_Bool trimFile(const char *filePath,CONF_LINE **ptr){
		FILE *fp=fopen(filePath,"r");
		char *buf=(char*)malloc(MAX_CHAR_PER_LINE+1);
		char *s_trim=NULL;
		CONF_LINE *previous=NULL,*current=NULL,*next=NULL,*head=NULL;
		if(fp == NULL){
			//file open failed or file not existed
		}
		else{
			head=(CONF_LINE *)malloc(sizeof(CONF_LINE));
			*ptr=head;
			current=head;
			previous=NULL;
			while(fgets(buf,MAX_CHAR_PER_LINE+1,fp) != NULL){
				s_trim=trimf(buf);
				ignoreSharp(s_trim);
				if(s_trim[0]==NULL){
					free(s_trim);
					continue;
				}
				strcpy(current->line_content,s_trim);
				free(s_trim);
				next=(CONF_LINE *)malloc(sizeof(CONF_LINE));
				current->next=next;
				previous=current;
				current=next;				
			}
			previous->next=NULL;
			free(next);
		}
		free(buf);
		fclose(fp);
		return 1;
}

/*
_Bool printCont(CONF_LINE *head){
	CONF_LINE *ptr=head;
	while(ptr!=NULL){
		printf("%s\n",ptr->line_content);
		ptr=ptr->next;
	}
	return 1;
}*/


_Bool analyzeConfFile(char *filePath,KEY_VAL *key_value){
	//trim empty characters
	CONF_LINE *conf_ptr=NULL,*head=NULL,*conf_ptr_cur;
	memset(key_value,0,sizeof(KEY_VAL));
	trimFile(filePath,&conf_ptr);
	head=conf_ptr;
	//split by '='
//	ptr=head;
	KEY_VAL *kv_ptr=key_value,*kv_pre=NULL;
	int i=0;
	while(conf_ptr!=NULL){
		i=0;
		while(conf_ptr->line_content[i] != NULL){
			if(conf_ptr->line_content[i] == '='){
				memcpy(kv_ptr->key	,&(conf_ptr->line_content[0]),i);
				strcpy(kv_ptr->value,&(conf_ptr->line_content[i+1]));
				kv_ptr->next=(KEY_VAL*)malloc(sizeof(KEY_VAL));
				memset(kv_ptr->next,0,sizeof(KEY_VAL));
				kv_pre=kv_ptr;
				kv_ptr=kv_pre->next;
				break;
			}
			i++;
		}
		conf_ptr_cur=conf_ptr;
		conf_ptr=conf_ptr->next;
		free(conf_ptr_cur);
	}
	kv_pre->next=NULL;
	free(kv_ptr);
}

_Bool getValue(KEY_VAL *kv,const char *key,char *value){
	if(kv == NULL || key == NULL )
		return FALSE;
	KEY_VAL *kv_ptr=kv;
	while(kv_ptr != NULL){
		if(!strcmp(kv_ptr->key,key)){
			strcpy(value,kv_ptr->value);
			return TRUE;
		}
		kv_ptr=kv_ptr->next;
	}
	return FALSE;
}
