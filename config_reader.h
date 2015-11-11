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

//2015.10.21 kimi wang

//该结构体用来保存配置文件每行的字符串
typedef struct conf_line {
	char line_content[100];
	struct conf_line *next;
} CONF_LINE;

//该结构体用来保存参数名、数值
typedef struct conf_key_val {
	char key[30];
	char value[30];
	struct conf_key_val *next;
} KEY_VAL;


//该函数用来清除字符串中的空白字符
char* trimf(const char* src){
	int i=0,j=0;
	char *buf=(char*)malloc(80);
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
char * ignoreSharp(char* src){
	int i=0;
	while( src[i] != NULL ){
		if(src[i]=='#'){
			src[i]==NULL;
			i++;
			break;
		}
		i++;
	}
	return src;
}



//该函数用来将配置文件中的字符串转换成CONF_LINE的结构体中
_Bool trimFile(const char *filePath,CONF_LINE **ptr){
		FILE *fp=fopen(filePath,"r");
		char *buf=(char*)malloc(81);
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
			while(fgets(buf,81,fp) != NULL){
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
		return 1;
}

_Bool printCont(CONF_LINE *head){
	CONF_LINE *ptr=head;
	while(ptr!=NULL){
		printf("%s\n",ptr->line_content);
		ptr=ptr->next;
	}
	return 1;
}


_Bool analyzeConfFile(char *filePath,KEY_VAL *key_value){
	
	//trim empty characters
	CONF_LINE *ptr=NULL,*head;
	trimFile(filePath,&ptr);
	head=ptr;
	//split by '='
	ptr=head;
	KEY_VAL *kv_ptr=key_value,*kv_pre=NULL;
	int i=0;
	while(ptr!=NULL){
		i=0;
		memset(kv_ptr->key,0,30);
		memset(kv_ptr->value,0,30);
		while(ptr->line_content[i] != NULL){
			if(ptr->line_content[i] == '='){
				memcpy(kv_ptr->key	,&(ptr->line_content[0]),i);
				strcpy(kv_ptr->value,&(ptr->line_content[i+1]));
				kv_ptr->next=(KEY_VAL*)malloc(sizeof(KEY_VAL));
				kv_pre=kv_ptr;
				kv_ptr=kv_pre->next;
				break;
			}
			i++;
		}		
		ptr=ptr->next;
	}
	kv_pre->next=NULL;
	free(kv_ptr);
}

_Bool printKeyValue(KEY_VAL *kv){
	KEY_VAL *ptr=kv;
	while(ptr!=NULL){
		printf("key:%s value:%s\n",ptr->key,ptr->value);
		ptr=ptr->next;
	}
	return 1;
}

_Bool getValue(CONF_LINE *head,char *key,char *value){
	CONF_LINE *ptr=head;
	while(ptr !=NULL){
		if(!strcmp(ptr->line_content,key)){
			
		}
	}
}
