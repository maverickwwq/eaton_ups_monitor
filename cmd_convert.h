#define CMD_CONVERT_H


//****************************************************************************************************************
//AUTHOR:KIMI WANG
//DATE:2013-03-07
//DESCRIPTION:格式转换
//****************************************************************************************************************


//将数据转换成正确的格式
extern char* asciiToHex(const char* src,char* dest);



//************************************
// Method:    asciiToHex
// FullName:  asciiToHex
// Access:    public 
// Returns:   char*
// Qualifier:
// Parameter: const char * src
// Parameter: char * dest
// 
//************************************

char* asciiToHex(const char* src,char* dest){
	unsigned int lenth=strlen(src);				//
	memset(dest,0,lenth/2+1);					//清空结果数组
	char *buf=(char*)malloc(lenth+1);			//临时数组
	memset(buf,0,lenth+1);						//
	strcpy(buf,src);							//保存参数
	unsigned char tmp;							//
	for (int i=0;i<lenth;i++){					//
		tmp=*(buf+i);							//
		if (tmp>='A' && tmp<='F'){				//先转化成实际数值
			*(buf+i)=tmp-'A'+10;				//'A'-'F'
		}
		else{
			*(buf+i)=tmp-'0';					//'1'-'9'
		}
	}
	for (i=0;i<lenth/2;i++){
		*(dest+i)=*(buf+2*i)<<4 | *(buf+2*i+1);	//内存低地址内容放到字节的高4位
	}
	free(buf);
	return dest;
}
