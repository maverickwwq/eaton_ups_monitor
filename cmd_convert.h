#define CMD_CONVERT_H


//****************************************************************************************************************
//AUTHOR:KIMI WANG
//DATE:2013-03-07
//DESCRIPTION:��ʽת��
//****************************************************************************************************************


//������ת������ȷ�ĸ�ʽ
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
	memset(dest,0,lenth/2+1);					//��ս������
	char *buf=(char*)malloc(lenth+1);			//��ʱ����
	memset(buf,0,lenth+1);						//
	strcpy(buf,src);							//�������
	unsigned char tmp;							//
	for (int i=0;i<lenth;i++){					//
		tmp=*(buf+i);							//
		if (tmp>='A' && tmp<='F'){				//��ת����ʵ����ֵ
			*(buf+i)=tmp-'A'+10;				//'A'-'F'
		}
		else{
			*(buf+i)=tmp-'0';					//'1'-'9'
		}
	}
	for (i=0;i<lenth/2;i++){
		*(dest+i)=*(buf+2*i)<<4 | *(buf+2*i+1);	//�ڴ�͵�ַ���ݷŵ��ֽڵĸ�4λ
	}
	free(buf);
	return dest;
}
