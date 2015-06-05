#include <stdio.h>
#include <string.h>

#define _DEBUG_							//�����ã�������ʱ��Ҫע�͵�

//---------------------------------------------------
//   2016/6/4
// 1.	BOOL sendCMD(HANDLE hCom,const char* original_cmd,const char* decode_cmd,char* answer,DWORD bytesToRead)���������Ż���const char* original_cmd����û��
// 2.	asciiToHex����ÿ�γ������������¼���һ��
//
//
//
//
//---------------------------------------------------

#ifndef GLOBAL_VAR_H
#include "global_var.h"
#endif

#ifndef SERIAL_H
#include "serial.h"
#endif

#ifndef CMD_CONVERT_H
#include "cmd_convert.h"
#endif

#ifndef UPSINFO_STRUCTURE_H
#include "upsinfo_structure.h"
#endif

#ifndef COMMUNICATE_H
#include "communicate.h"
#endif

#ifndef UI_H
#include "ui.h"
#endif

#ifndef ALARM_H
#include "alarm.h"
#endif

//���߳�1�����ú���-���ͽ�������
DWORD WINAPI	sendDataViaCom(void*);
//��ʱˢ�½���
gboolean refreshUI(void *nothing);
//��Դ����,�˳�����ʱ����
//�رվ�����ر��̣߳��رմ���
void _atExit();


extern UPS_STATE _2023ups[NUM_OF_UPS];//���������ļ���ȫ�ֱ���

int main(void){
	//1.�����͵�����ת������ȷ�ĸ�ʽ
	asciiToHex(UPS_COMMUNICATION_INI,UPS_COMMUNICATION_INI_DECODE);
	asciiToHex(UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE);
	asciiToHex(UPS_CMD_01,UPS_CMD_01_DECODE);
	asciiToHex(UPS_CMD_02,UPS_CMD_02_DECODE);
	asciiToHex(UPS_CMD_03,UPS_CMD_03_DECODE);
	asciiToHex(UPS_CMD_06,UPS_CMD_06_DECODE);
	asciiToHex(UPS_CMD_07,UPS_CMD_07_DECODE);
	asciiToHex(UPS_CMD_24,UPS_CMD_24_DECODE);
	asciiToHex(UPS_CMD_27,UPS_CMD_27_DECODE);
	asciiToHex(UPS_CMD_31,UPS_CMD_31_DECODE);
	asciiToHex(UPS_CMD_32,UPS_CMD_32_DECODE);
	asciiToHex(UPS_CMD_3B,UPS_CMD_3B_DECODE);
	asciiToHex(UPS_CMD_42,UPS_CMD_42_DECODE);

	//2.��ȡ�����ļ�����
	_2023ups[0].LINK_COM_NUM=1;
	_2023ups[1].LINK_COM_NUM=0;
	_2023ups[2].LINK_COM_NUM=0;
	_2023ups[3].LINK_COM_NUM=0;

	
#define READ_INTERVAL 5
#define READ_MULTIPLIER 15
#define READ_CONSTANT 15
#define WRITE_MULTIPLIER 10
#define WRITE_CONSTANT 10

#ifdef _DEBUG_
	printf("DEBUG !!!!!!!!!!!!!!!!!!!!!!!\n\n\n");
#endif
	
	
	//3.��ʼ����Ӧ����
	int i=0;
	char com[20];
	for(i=0;i<NUM_OF_UPS;i++){
		memset(com,0,20);
		if(_2023ups[i].LINK_COM_NUM	>	0){		// _2023ups[i].LINK_COM_NUM�������ļ���ȡ,>0��Ч
			sprintf(com,"COM%d",_2023ups[i].LINK_COM_NUM);
#ifdef _DEBUG_
	printf("start com%d communication\n",_2023ups[i].LINK_COM_NUM);
#endif
			_2023ups[i].UPS_COM_HANDLE=initialCom(com,1024);
			if(_2023ups[i].UPS_COM_HANDLE == INVALID_HANDLE_VALUE){
				printf("Open Com Error\n");
				exit(0);
			}
			COMMTIMEOUTS timeouts={READ_INTERVAL,READ_MULTIPLIER,READ_CONSTANT,WRITE_MULTIPLIER,WRITE_CONSTANT};
			if(setComTimeout(_2023ups[i].UPS_COM_HANDLE,timeouts))
				printf("set com timeout ok\n");
			if(setComPara(_2023ups[i].UPS_COM_HANDLE,_24_N_8_1))
				printf("set com parameter ok\n");	
		}
	}



		//	4.ͼ�ν������

		if(!gtk_init_check(NULL,NULL)){
//			g_thread_init(NULL);
			printf("����ϵͳ�޷���ʼ��\n");
			exit(0);
		}
		GtkWidget *mainWin;													//������
		GtkWidget *horizonAllUPS;											//
		GtkWidget *frame;													//
		GtkWidget *vbox;													//
		GtkWidget *hbox;													//
		GtkWidget *item;													//
		GtkWidget *evenbox;													//
		
		extern GtkWidget *itemValue[4][11];									//
		extern const char *frames[];
		extern const char *items[];
		
		mainWin=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(mainWin),_G("2023̨�ڴ�UPS��ʾϵͳ"));	//������
		gtk_window_set_resizable(GTK_WINDOW(mainWin),TRUE);						//�ɸı��С
		gtk_window_set_default_size(GTK_WINDOW(mainWin),1000,640);				//���ڴ�С
		gtk_window_set_position(GTK_WINDOW(mainWin),GTK_WIN_POS_CENTER);		//����
		
		gtk_container_set_border_width(GTK_CONTAINER(mainWin),6);				//�߽��С
		g_signal_connect(mainWin,"destroy",G_CALLBACK(destroyEvent),NULL);		//���ٺ���
		GdkPixbuf *pixBuf;														//����Сͼ��
		GError *error=NULL;														//
		pixBuf=gdk_pixbuf_new_from_file("icons/battery.png",&error);			//ͼ��·��
		if(!pixBuf){															//
			fprintf(stderr, "%s\n", error->message);							//
			g_error_free(error);												//
		}																		//
		gtk_window_set_icon(GTK_WINDOW(mainWin),pixBuf);						//
		
		int frameCount=0,itemCount=0;											//
		GdkColor valueBGColor;
		horizonAllUPS=gtk_hbox_new(TRUE,2);										//
		gtk_container_add(GTK_CONTAINER(mainWin),horizonAllUPS);				//
		for(frameCount=0;frameCount<4;frameCount++){							//
			frame=gtk_frame_new(_G(frames[frameCount]));						//
			gtk_box_pack_start(GTK_BOX(horizonAllUPS),frame,TRUE,TRUE,2);		//
			vbox=gtk_vbox_new(TRUE,10);											//
			gtk_container_add(GTK_CONTAINER(frame),vbox);						//
			for(int i=0;i<9;i++){
				hbox=gtk_hbox_new(TRUE,2);												//
				gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,5);						//
				item=gtk_label_new(_G(items[i]));										//
				setFontColor(item,11,"blue");											//
				gtk_box_pack_start(GTK_BOX(hbox),item,TRUE,TRUE,2);						//
				evenbox=gtk_event_box_new();											//
				gdk_color_parse("black",&valueBGColor);
				gtk_widget_modify_bg(evenbox, GTK_STATE_NORMAL, &valueBGColor);		//������ɫ
				gtk_box_pack_start(GTK_BOX(hbox),evenbox,TRUE,TRUE,2);					//
				itemValue[frameCount][i]=gtk_label_new("-- --");									//
				setFontColor(itemValue[frameCount][i],15,"green");									//
				gtk_container_add(GTK_CONTAINER(evenbox),itemValue[frameCount][i]);					//
			}
			itemValue[frameCount][9] = gtk_info_bar_new ();
			gtk_box_pack_start (GTK_BOX (vbox), itemValue[frameCount][i], FALSE, FALSE, 0);
			gtk_info_bar_set_message_type (GTK_INFO_BAR (itemValue[frameCount][i]),\
				GTK_MESSAGE_QUESTION);
			itemValue[frameCount][10]= gtk_label_new (_G("����"));
			gtk_box_pack_start (GTK_BOX (gtk_info_bar_get_content_area (GTK_INFO_BAR (itemValue[frameCount][9]))),\
				itemValue[frameCount][10], FALSE, FALSE, 0);
		}
		g_timeout_add(REFRESH_PER_X_SECONDS*1000,GSourceFunc(refreshUI),NULL);
		gtk_widget_show_all(mainWin);
		



	//5.����һ���̣߳��������ͽ��մ�������
	HANDLE sendDataThreadProc=CreateThread(NULL,0,sendDataViaCom,NULL,0,NULL);

	gtk_main();

	return 0;
}





//************************************
// Method:    sendDataViaCom
// FullName:  sendDataViaCom
// Access:    public 
// Returns:   DWORD WINAPI
// Qualifier:
// Parameter: void *
// ����:ȷ��ͨ����������������com���ٳ��ԣ�ʧ�ܺ�����������Ч��ʶ��FALSE
//		���ͨ����������ô�����ý���浽UPS_STATE�ṹ���е���Ӧ�ֶ�
//		
//************************************
DWORD WINAPI sendDataViaCom(void*){
	FILE* log;
	int i=0;
	DWORD tryTime;
	while(1){
	Sleep(15000);
	for(i=0;i<NUM_OF_UPS;i++){
		tryTime=CHECK_TIME;
	start_commu:
		//����ͨ���Ƿ�����
 		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_COMMUNICATION_INI,\
			UPS_COMMUNICATION_INI_DECODE,_2023ups[i].UPS_COMMUNICATION_INI_ANSWER,1) && \
			!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_01,UPS_CMD_01_DECODE,_2023ups[i].UPS_CMD_01_ANSWER,10)){
				//��������������
			memset(_2023ups[i].UPS_COMMUNICATION_INI_ANSWER,0,\
					sizeof(_2023ups[i].UPS_COMMUNICATION_INI_ANSWER));			//
			memset(_2023ups[i].UPS_CMD_01_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_01_ANSWER));
			//������������com�ڣ�������
			if(tryTime--){			//��ೢ��CHECK_TIME��
				Sleep(1000);
				printf("����com%d\n",_2023ups[i].LINK_COM_NUM);
				closeCom(_2023ups[i].UPS_COM_HANDLE);
				char com[10]={0};
				sprintf(com,"COM%d",_2023ups[i].LINK_COM_NUM);
				_2023ups[i].UPS_COM_HANDLE=initialCom(com,1024);
//				COMMTIMEOUTS timeouts={5,15,15,1,1};
				COMMTIMEOUTS timeouts={READ_INTERVAL,READ_MULTIPLIER,READ_CONSTANT,WRITE_MULTIPLIER,WRITE_CONSTANT};
				if(setComTimeout(_2023ups[i].UPS_COM_HANDLE,timeouts))
					printf("set com timeout ok\n");
				if(setComPara(_2023ups[i].UPS_COM_HANDLE,_24_N_8_1))
					printf("set com parameter ok\n");	
				if(_2023ups[i].UPS_COM_HANDLE == INVALID_HANDLE_VALUE){		//��Ч���
					printf("Open Com Error\n");								//�˳�
					exit(0);
				}
				goto start_commu;											//���²���ͨ��
			}
			//ȷ��ͨ�Ź���
			else{		//���������ʶ��Ϊ��Ч
				_2023ups[i].UPS_COMMUNICATE_NORMAL=FALSE;
				_2023ups[i].CMD_01_CHECK=FALSE;
				_2023ups[i].CMD_02_CHECK=FALSE;
				_2023ups[i].CMD_03_CHECK=FALSE;
				_2023ups[i].CMD_06_CHECK=FALSE;
				_2023ups[i].CMD_07_CHECK=FALSE;
				_2023ups[i].CMD_24_CHECK=FALSE;
				_2023ups[i].CMD_27_CHECK=FALSE;
				_2023ups[i].CMD_31_CHECK=FALSE;
				_2023ups[i].CMD_32_CHECK=FALSE;
				_2023ups[i].CMD_3B_CHECK=FALSE;
				_2023ups[i].CMD_42_CHECK=FALSE;
				if((log=fopen("log","w"))!=NULL){
					fprintf(log,"%s\n","ͨ�Ź���");
					fclose(log);
				}
				break;			//ͨ�Ź��ϣ������ٷ������������һ̨ups
			}
		}

		_2023ups[i].UPS_COMMUNICATE_NORMAL=TRUE;	//ȷ��ͨ��������ͨ�ű�ʶ��Ϊ��
		printf("communicate:%s\n",_2023ups[i].UPS_COMMUNICATION_INI_ANSWER);

		printf("\nCmd1:\n");
		//�������������õĽ���ֽ�����Ԥ�ڣ���ô��ս���ֶ�
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_01,UPS_CMD_01_DECODE,\
			_2023ups[i].UPS_CMD_01_ANSWER,10)){
				memset(_2023ups[i].UPS_CMD_01_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_01_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
		printf("cmd01:%s\n",_2023ups[i].UPS_CMD_01_ANSWER);
Sleep(1000);		
		printf("\nCmd2:\n");
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_02,UPS_CMD_02_DECODE,\
			_2023ups[i].UPS_CMD_02_ANSWER,9)){
				memset(_2023ups[i].UPS_CMD_02_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_02_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
		printf("cmd02:%s\n",_2023ups[i].UPS_CMD_02_ANSWER);
Sleep(1000);
		printf("\nCmd3:\n");
		//���͵��������յ������ݳ��Ȳ���ȷ�����������
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_03,UPS_CMD_03_DECODE,\
			_2023ups[i].UPS_CMD_03_ANSWER,8)){
				memset(_2023ups[i].UPS_CMD_03_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_03_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
		printf("cmd03:%s\n",_2023ups[i].UPS_CMD_03_ANSWER);
Sleep(1000);
		printf("\nCmd06:\n");
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_06,UPS_CMD_06_DECODE,\
			_2023ups[i].UPS_CMD_06_ANSWER,10)){
				memset(_2023ups[i].UPS_CMD_06_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_06_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
		printf("cmd06:%s\n",_2023ups[i].UPS_CMD_06_ANSWER);
Sleep(1000);
		printf("\nCmd07:\n");
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_07,UPS_CMD_07_DECODE,\
			_2023ups[i].UPS_CMD_07_ANSWER,8)){
				memset(_2023ups[i].UPS_CMD_07_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_07_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
		printf("cmd07:%s\n",_2023ups[i].UPS_CMD_07_ANSWER);
Sleep(1000);
		printf("\nCmd24:\n");
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_24,UPS_CMD_24_DECODE,\
			_2023ups[i].UPS_CMD_24_ANSWER,6)){
				memset(_2023ups[i].UPS_CMD_24_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_24_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
		printf("cmd24:%s\n",_2023ups[i].UPS_CMD_24_ANSWER);

/*printf("\nCmd27:\n");
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_27,UPS_CMD_27_DECODE,\
			_2023ups[i].UPS_CMD_27_ANSWER,8)){
				memset(_2023ups[i].UPS_CMD_27_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_27_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
printf("cmd27:%s\n",_2023ups[i].UPS_CMD_27_ANSWER);*/			//�޷��õ���Ӧ��ע�� 2015/6/4
Sleep(1000);
		printf("\nCmd31:\n");
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_31,UPS_CMD_31_DECODE,\
			_2023ups[i].UPS_CMD_31_ANSWER,8)){
				memset(_2023ups[i].UPS_CMD_31_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_31_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
		printf("cmd31:%s\n",_2023ups[i].UPS_CMD_31_ANSWER);
Sleep(1000);
		printf("\nCmd32:\n");
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_32,UPS_CMD_32_DECODE,\
			_2023ups[i].UPS_CMD_32_ANSWER,9)){
				memset(_2023ups[i].UPS_CMD_32_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_32_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
		printf("cmd32:%s\n",_2023ups[i].UPS_CMD_32_ANSWER);
Sleep(1000);
		printf("\nCmd3B:\n");
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_3B,UPS_CMD_3B_DECODE,\
			_2023ups[i].UPS_CMD_3B_ANSWER,6)){
				memset(_2023ups[i].UPS_CMD_3B_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_3B_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
		printf("cmd3B:%s\n",_2023ups[i].UPS_CMD_3B_ANSWER);
Sleep(1000);
		printf("\nCmd42:\n");
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_42,UPS_CMD_42_DECODE,\
			_2023ups[i].UPS_CMD_42_ANSWER,12)){
				memset(_2023ups[i].UPS_CMD_42_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_42_ANSWER));
		}
		if(!sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,\
			&_2023ups[i].UPS_CMD_42_ANSWER[12],5)){
				memset(_2023ups[i].UPS_CMD_42_ANSWER,0,sizeof(_2023ups[i].UPS_CMD_42_ANSWER));
		}
		sendCMD(_2023ups[i].UPS_COM_HANDLE,UPS_CMD_ACCEPT,UPS_CMD_ACCEPT_DECODE,NULL,0);
		printf("cmd42:%s\n",_2023ups[i].UPS_CMD_42_ANSWER);

//�����յ�������ת����ʽ���浽UPS_STATE�ṹ����
		//����ͨ��������ʶ
		if(_2023ups[i].UPS_COMMUNICATION_INI_ANSWER[0] == 0x16){
			_2023ups[i].UPS_COMMUNICATE_NORMAL=TRUE;
		}
		else{
			_2023ups[i].UPS_COMMUNICATE_NORMAL=FALSE;
		}
		//�жϸ�Ӧ���Ƿ���Ч��0x06,0x84��ͷ����ŵ��Ч������Ӧ�����UPS_STATE�ṹ��
		//����������Ч��ʶ��FALSE
		static const char VALID_ANSWER[3]={0x06,0x84,0x00};
		static const char VALID_CMD1_ANSWER[4]={0x06,0x84,0x66,0x00};
		static const char VALID_CMD2_ANSWER[4]={0x06,0x84,0x55,0x00};
		static const char VALID_CMD3_ANSWER[4]={0x06,0x84,0x44,0x00};
		static const char VALID_CMD6_ANSWER[4]={0x06,0x84,0x66,0x00};
		if(!strncmp(VALID_CMD1_ANSWER,_2023ups[i].UPS_CMD_01_ANSWER,3)){
			_2023ups[i].INPUT_POWER_ABNORMAL=(_2023ups[i].UPS_CMD_01_ANSWER[4]==0x00)?TRUE:FALSE;
			_2023ups[i].BATTERY_LOW_VOLTAGE=(_2023ups[i].UPS_CMD_01_ANSWER[5]==0x01)?TRUE:FALSE;
			_2023ups[i].DISCHARGE=(_2023ups[i].UPS_CMD_01_ANSWER[6]==0x00)?TRUE:FALSE;
			_2023ups[i].CMD_01_CHECK=TRUE;
		}
		else{
			_2023ups[i].CMD_01_CHECK=FALSE;
		}
		if(!strncmp(VALID_CMD2_ANSWER,_2023ups[i].UPS_CMD_02_ANSWER,3)){
			printf("\n\n--------    ");
			for(int e=0;e<9;e++){
				printf("%02x",(unsigned char)_2023ups[i].UPS_CMD_02_ANSWER[e]);
			}
			printf("    ------------\n\n");
			_2023ups[i].UPS_ERROR=(_2023ups[i].UPS_CMD_02_ANSWER[4]==0x01)?TRUE:FALSE;
			_2023ups[i].BATTERY_LINK_STATE=(_2023ups[i].UPS_CMD_02_ANSWER[5]==0x01)?TRUE:FALSE;
			_2023ups[i].OVERLOAD=(_2023ups[i].UPS_CMD_02_ANSWER[6]==0x00)?FALSE:TRUE;
			_2023ups[i].CMD_02_CHECK=TRUE;
		}
		else{
			_2023ups[i].CMD_02_CHECK=FALSE;
		}
		if(!strncmp(VALID_CMD3_ANSWER,_2023ups[i].UPS_CMD_03_ANSWER,3)){
			_2023ups[i].FAN_ERROR=(_2023ups[i].UPS_CMD_03_ANSWER[5]==0x00)?FALSE:TRUE;
			_2023ups[i].OVERHEAT=(_2023ups[i].UPS_CMD_03_ANSWER[6]==0x00)?FALSE:TRUE;
			_2023ups[i].CMD_03_CHECK=TRUE;
		}
		else{
			_2023ups[i].CMD_03_CHECK=FALSE;
		}
		if(!strncmp(VALID_CMD6_ANSWER,_2023ups[i].UPS_CMD_06_ANSWER,3)){
			_2023ups[i].BATTERY_CAPACITY=_2023ups[i].UPS_CMD_06_ANSWER[4];
			_2023ups[i].BATTERY_REMAIN_TIME=(	((unsigned char)_2023ups[i].UPS_CMD_06_ANSWER[5])+	\
				(((unsigned char)_2023ups[i].UPS_CMD_06_ANSWER[6])<<8)+	\
				(((unsigned char)_2023ups[i].UPS_CMD_06_ANSWER[7])<<16)+	\
				(((unsigned char)_2023ups[i].UPS_CMD_06_ANSWER[8])<<24)	)/60;
			_2023ups[i].CMD_06_CHECK=TRUE;
		}
		else{
			_2023ups[i].CMD_06_CHECK=FALSE;
		}

		if(!strncmp(VALID_ANSWER,_2023ups[i].UPS_CMD_07_ANSWER,2)){
			_2023ups[i].LOAD_PERCEN=_2023ups[i].UPS_CMD_07_ANSWER[4];
			_2023ups[i].BATTERY_VOLTATE=(unsigned char)_2023ups[i].UPS_CMD_07_ANSWER[5]+\
				((unsigned char)_2023ups[i].UPS_CMD_07_ANSWER[6]<<8);
			_2023ups[i].CMD_07_CHECK=TRUE;
		}
		else{
			_2023ups[i].CMD_07_CHECK=FALSE;
		}
		if(!strncmp(VALID_ANSWER,_2023ups[i].UPS_CMD_24_ANSWER,2)){
			_2023ups[i].BATTERY_SELFTEST=_2023ups[i].UPS_CMD_24_ANSWER[4];
			_2023ups[i].CMD_24_CHECK=TRUE;
		}
		else{
			_2023ups[i].CMD_24_CHECK=FALSE;
		}
		/*if(!strncmp(VALID_ANSWER,_2023ups[i].UPS_CMD_27_ANSWER,2)){
			_2023ups[i].BATTERY_LINK_STATE=(_2023ups[i].UPS_CMD_27_ANSWER[4]==0x01)?TRUE:FALSE;
			_2023ups[i].CHARGER_ERROR=(_2023ups[i].UPS_CMD_27_ANSWER[5]==0x01)?TRUE:FALSE;
			_2023ups[i].OVERCHARGE=(_2023ups[i].UPS_CMD_27_ANSWER[6]==0x01)?TRUE:FALSE;
			_2023ups[i].CMD_27_CHECK=TRUE;
		}
		else{
			_2023ups[i].CMD_27_CHECK=FALSE;
		}*/
		if(!strncmp(VALID_ANSWER,_2023ups[i].UPS_CMD_31_ANSWER,2)){
			_2023ups[i].INPUT_FREQUENCY=_2023ups[i].UPS_CMD_31_ANSWER[4];
			_2023ups[i].INPUT_VOLTAGE=(((unsigned char)_2023ups[i].UPS_CMD_31_ANSWER[6])<<8) +\
				(unsigned char)_2023ups[i].UPS_CMD_31_ANSWER[5];
			_2023ups[i].CMD_31_CHECK=TRUE;

		}
		else{
			_2023ups[i].CMD_31_CHECK=FALSE;
		}
		if(!strncmp(VALID_ANSWER,_2023ups[i].UPS_CMD_32_ANSWER,2)){
			_2023ups[i].INPUT_FREQUENCY_ABNORMAL=(_2023ups[i].UPS_CMD_32_ANSWER[4]==0x01)?TRUE:FALSE;
			_2023ups[i].INPUT_POWER_MODE=(_2023ups[i].UPS_CMD_32_ANSWER[6]==0x01)?TRUE:FALSE;
			_2023ups[i].INPUT_VOLTAGE_ABNORMAL=(_2023ups[i].UPS_CMD_32_ANSWER[7]==0x01)?TRUE:FALSE;
			_2023ups[i].CMD_32_CHECK=TRUE;
		}
		else{
			_2023ups[i].CMD_32_CHECK=FALSE;
		}
		if(!strncmp(VALID_ANSWER,_2023ups[i].UPS_CMD_3B_ANSWER,2)){
			_2023ups[i].BATTERY_MODE=(_2023ups[i].UPS_CMD_3B_ANSWER[4]==0x01)?TRUE:FALSE;
			_2023ups[i].CMD_3B_CHECK=TRUE;
		}
		else{
			_2023ups[i].CMD_3B_CHECK=FALSE;
		}
		if(_2023ups[i].UPS_CMD_42_ANSWER[0] == 0x06){
			_2023ups[i].OUTPUT_WATT=(unsigned char)_2023ups[i].UPS_CMD_42_ANSWER[4] + \
				((unsigned char)_2023ups[i].UPS_CMD_42_ANSWER[5]<<8);
			_2023ups[i].OUTPUT_VA=(unsigned char)_2023ups[i].UPS_CMD_42_ANSWER[6] + \
				((unsigned char)_2023ups[i].UPS_CMD_42_ANSWER[7]<<8);
			_2023ups[i].OUTPUT_CURRENT=(unsigned char)_2023ups[i].UPS_CMD_42_ANSWER[8]*0.1;
			_2023ups[i].OUTPUT_FREQUENCY=(unsigned char)_2023ups[i].UPS_CMD_42_ANSWER[9];
			_2023ups[i].OUTPUT_VOLTAGE=(unsigned char)_2023ups[i].UPS_CMD_42_ANSWER[14] + \
				((unsigned char)_2023ups[i].UPS_CMD_42_ANSWER[15]<<8);
			_2023ups[i].CMD_42_CHECK=TRUE;
		}
		else{
			_2023ups[i].CMD_42_CHECK=FALSE;
		}
 	}
}
	return 0;
}





//ˢ��ͼ�κ���+��������
gboolean refreshUI(void *nothing){
// 	HANDLE hTimer=CreateWaitableTimer(NULL,FALSE,NULL);
// 	if(hTimer == NULL)
// 		printf("\nCreateWaitableTimer error\n");
// 	LARGE_INTEGER li;
// 	li.QuadPart=-50000000;
// 	SetWaitableTimer(hTimer,&li,1000,printUPSState,NULL,FALSE);
// 	while(1){
// 		SleepEx(INFINITE,TRUE);
// 	}
// 	return 0;
//	gdk_threads_enter();
//	g_type_init();
	static unsigned int count=0;
	int i=0,j=0;
	printf("\n--------------------------------------------\n");
	printf("--------------------------------------------\n");
	printf("ͨ��:%s\n",(_2023ups[i].UPS_COMMUNICATE_NORMAL==TRUE)?"����":"����");
	printf("UPS:%s\n",(_2023ups[i].UPS_ERROR==FALSE)?"����":"����");
	printf("�е�:%s\n",(_2023ups[i].INPUT_POWER_ABNORMAL==FALSE)?"����":"����");
	printf("�е��ѹ:%d\n",_2023ups[i].INPUT_VOLTAGE);
	printf("�е�Ƶ��:%d\n",_2023ups[i].INPUT_FREQUENCY);
	printf("Count:%4d\n",count);
	printf("--------------------------------------------\n");
	printf("--------------------------------------------\n");
	extern GtkWidget *itemValue[4][11];
	char buf[25];
	
	for(i=0;i<NUM_OF_UPS;++i){
		if(_2023ups[i].LINK_COM_NUM	>	0){	// >0 ��ʼ��ʱ��򿪴���,���Դ���ͨ��
			if(_2023ups[i].UPS_COMMUNICATE_NORMAL){
				setFontColor(itemValue[i][0],15,"green");
				gtk_label_set_text(GTK_LABEL(itemValue[i][0]),_G("ͨ������"));
				if(_2023ups[i].CMD_01_CHECK){
					if(_2023ups[i].INPUT_POWER_ABNORMAL){
						gtk_label_set_text(GTK_LABEL(itemValue[i][2]),_G("�е����"));
						setFontColor(itemValue[i][2],15,"red");
					}
					else{
						gtk_label_set_text(GTK_LABEL(itemValue[i][2]),_G("�е�����"));
						setFontColor(itemValue[i][2],15,"green");
					}
					if(_2023ups[i].DISCHARGE){
						setFontColor(itemValue[i][5],15,"red");
						gtk_label_set_text(GTK_LABEL(itemValue[i][5]),_G("�ŵ�"));
					}
					else{
						setFontColor(itemValue[i][5],15,"green");
						gtk_label_set_text(GTK_LABEL(itemValue[i][5]),_G("���"));
					}
				}
				if(_2023ups[i].CMD_02_CHECK){
					if(_2023ups[i].UPS_ERROR){
						gtk_label_set_text(GTK_LABEL(itemValue[i][1]),_G("����"));
						setFontColor(itemValue[i][1],15,"red");
					}
					else{
						gtk_label_set_text(GTK_LABEL(itemValue[i][1]),_G("����"));
						setFontColor(itemValue[i][1],15,"green");
					}
				}
				if(_2023ups[i].CMD_42_CHECK){
					sprintf(buf,"%d V",_2023ups[i].INPUT_VOLTAGE);
					gtk_label_set_text(GTK_LABEL(itemValue[i][3]),\
						buf);
					sprintf(buf,"%d Hz",_2023ups[i].INPUT_FREQUENCY);
					gtk_label_set_text(GTK_LABEL(itemValue[i][4]),\
						buf);
				}
				if(_2023ups[i].CMD_06_CHECK){
					sprintf(buf,"%d %%",_2023ups[i].BATTERY_CAPACITY);
					gtk_label_set_text(GTK_LABEL(itemValue[i][6]),\
						buf);
				}
				if(_2023ups[i].CMD_42_CHECK){
					sprintf(buf,"%d V",_2023ups[i].OUTPUT_VOLTAGE);
					gtk_label_set_text(GTK_LABEL(itemValue[i][7]),\
						buf);
					sprintf(buf,"%d Hz",_2023ups[i].OUTPUT_FREQUENCY);
					gtk_label_set_text(GTK_LABEL(itemValue[i][8]),\
						buf);
				}
			}
			else{
				for(j=0;j<=8;j++){
 					setFontColor(itemValue[i][j],15,"red");
 					gtk_label_set_text(GTK_LABEL(itemValue[i][j]),"-- --");
				}
				setFontColor(itemValue[i][0],15,"green");
				gtk_label_set_text(GTK_LABEL(itemValue[i][0]),_G("ͨ�Ź���"));
			}
		}
	}

	for(i=0;i<NUM_OF_UPS;++i){
		if(_2023ups[i].LINK_COM_NUM	>	0){	// >0 ��ʼ��ʱ��򿪴���,���Դ���ͨ��
			if(_2023ups[i].UPS_COMMUNICATE_NORMAL){	//ͨ������
				if(!_2023ups[i].INPUT_POWER_ABNORMAL){//�е�����
					//
				}
				else{						//�е��쳣
					gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
						GTK_MESSAGE_WARNING);
					gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("�е��쳣"));
					makeSound(ALARM_INPUT_ERROR);
					count++;
					break;
				}
				if(!_2023ups[i].UPS_ERROR){	//ups����
					//
				}
				else{						//ups����
					gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
						GTK_MESSAGE_ERROR);
					gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("UPS����"));
					makeSound(ALARM_UPS_ERROR);
					count++;
					break;
				}
				//���ж������Ļ���ִ������
				gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
					GTK_MESSAGE_QUESTION);
				gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("����"));
			}
			else{							//ͨ���쳣
				gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
					GTK_MESSAGE_INFO);
				gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("ͨ���쳣"));
				makeSound(ALARM_NOT_CONNECT);
				count++;
				break;
			}
		}
	}
	return TRUE;
}
