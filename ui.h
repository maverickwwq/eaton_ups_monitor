#define UI_H

#ifndef GTK_H
#define GTK_H
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#endif
//#include <stdlib.h>

#define _G(str)		g_convert(str,-1,"UTF-8","GB2312",NULL,NULL,NULL)


//����widget�������С����ɫ
void setFontColor(GtkWidget *widget,int fontSize,char * colorStr);
//���������¼�
void destroyEvent(GtkWidget *widget,void *data);
//��ʱˢ�½���
gboolean refreshUI(void *nothing);

void destroyEvent(GtkWidget *widget,void *data){
	gtk_main_quit();
}



void setFontColor(GtkWidget *widget,int fontSize,char * colorStr){
	PangoFontDescription	*font=pango_font_description_from_string("Sans 13");
	pango_font_description_set_size(font,fontSize * PANGO_SCALE);
	GdkColor	color;
	gdk_color_parse(colorStr,&color);
	gtk_widget_modify_fg(GTK_WIDGET(widget),GTK_STATE_NORMAL,&color);
	gtk_widget_modify_font(GTK_WIDGET(widget),font);
}


static void
activate (GApplication *app,
         gpointer      user_data)
{
		//	4.ͼ�ν������
	if(!gtk_init_check(NULL,NULL)){
//		g_thread_init(NULL);
		printf("����ϵͳ�޷���ʼ��\n");
		exit(0);
	}
//	GtkWidget *window;
	GtkWidget *mainWin;													//������
	GtkWidget *horizonAllUPS;											//
	GtkWidget *frame;													//
	GtkWidget *vbox;													//
	GtkWidget *hbox;													//
	GtkWidget *item;													//
	GtkWidget *evenbox;													//
	GError *error = NULL;	
	extern GtkWidget *itemValue[4][11];									//
	extern const char *frames[];										//
	extern const char *items[];											//

	  /* Create a window with a title and a default size */
	mainWin = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (mainWin), _G("2023̨�ڴ�UPS��ʾϵͳ"));
	gtk_window_set_default_size (GTK_WINDOW (mainWin), 1024, 640);

//	mainWin=gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_title(GTK_WINDOW(mainWin),_G("2023̨�ڴ�UPS��ʾϵͳ"));	//������
	gtk_window_set_resizable(GTK_WINDOW(mainWin),TRUE);						//�ɸı��С
//	gtk_window_set_default_size(GTK_WINDOW(mainWin),1000,640);				//���ڴ�С
	gtk_window_set_position(GTK_WINDOW(mainWin),GTK_WIN_POS_CENTER);		//����
		
	gtk_container_set_border_width(GTK_CONTAINER(mainWin),6);				//�߽��С
//	g_signal_connect(mainWin,"destroy",G_CALLBACK(destroyEvent),NULL);		//���ٺ���
	GdkPixbuf *pixBuf;														//����Сͼ��													//
	pixBuf=gdk_pixbuf_new_from_file("icons/battery.png",&error);			//ͼ��·��
	if(!pixBuf){															//
		fprintf(stderr, "%s\n", error->message);							//
		//��Ҫ�����쳣������־��¼
		g_error_free(error);												//
	}																		//
	gtk_window_set_icon(GTK_WINDOW(mainWin),pixBuf);						//
		
	int frameCount=0;											//
	GdkColor valueBGColor;
	//horizonAllUPS=gtk_hbox_new(TRUE,2);									//
	horizonAllUPS=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,2);				//
	gtk_container_add(GTK_CONTAINER(mainWin),horizonAllUPS);
	gtk_container_add(GTK_CONTAINER(mainWin),horizonAllUPS);				//
	for(frameCount=0;frameCount<4;frameCount++){							//
		frame=gtk_frame_new(_G(frames[frameCount]));						//
		gtk_box_pack_start(GTK_BOX(horizonAllUPS),frame,TRUE,TRUE,2);		//
		//vbox=gtk_vbox_new(TRUE,10);										//
		vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,10);
		gtk_container_add(GTK_CONTAINER(frame),vbox);						//
		for(int i=0;i<9;i++){
			//hbox=gtk_hbox_new(TRUE,2);												//
			hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,2);
			gtk_box_set_homogeneous(GTK_BOX(hbox),TRUE);
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
		gtk_box_pack_start (GTK_BOX (vbox), itemValue[frameCount][9], FALSE, FALSE, 0);
		gtk_info_bar_set_message_type (GTK_INFO_BAR (itemValue[frameCount][9]),\
			GTK_MESSAGE_QUESTION);
		itemValue[frameCount][10]= gtk_label_new (_G("����"));
		gtk_box_pack_start (GTK_BOX (gtk_info_bar_get_content_area (GTK_INFO_BAR (itemValue[frameCount][9]))),\
			itemValue[frameCount][10], FALSE, FALSE, 0);
	}
	g_timeout_add(REFRESH_PER_X_SECONDS*1000,(GSourceFunc)refreshUI,NULL);
	gtk_widget_show_all(mainWin);
}

static void 
startup(GApplication *app,
         gpointer      user_data){
	  /* Initialize variables */
  GtkBuilder *builder;

  GError *error = NULL;
  /* A builder to add the User Interface designed with GLADE to the grid: */
  builder = gtk_builder_new ();
  /* Get the file (if it is there):
   * Note: you must make sure that the file is in the current directory for
   * this to work. The function used here returns a non-null value within
   * our variable "error" if an error is indeed found.
   */
  gtk_builder_add_from_file (builder, "menubar.ui", &error);
  if (error != NULL) {
     g_print ("%s\n", error->message);
     g_error_free (error);
  }

  /* Extract the menubar */
  GObject *menubar = gtk_builder_get_object (builder, "menubar");
  gtk_application_set_menubar (GTK_APPLICATION (app), G_MENU_MODEL (menubar));

  /* Extract the appmenu */
  GObject *appmenu = gtk_builder_get_object (builder, "appmenu");
  gtk_application_set_app_menu (GTK_APPLICATION (app), G_MENU_MODEL (appmenu));
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
/*
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
*/
	extern GtkWidget *itemValue[4][11];
	char buf[25];
	
	for(i=0;i<NUM_OF_UPS;++i){
		if(_2023ups[i].UPS_SET_ACTIVE	==	TRUE){	// 
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
			else{							//ͨ�Ź���
				for(j=0;j<=8;j++){
 					setFontColor(itemValue[i][j],15,"red");
 					gtk_label_set_text(GTK_LABEL(itemValue[i][j]),"-- --");
				}
				setFontColor(itemValue[i][0],15,"red");
				gtk_label_set_text(GTK_LABEL(itemValue[i][0]),_G("ͨ�Ź���"));
			}
		}
		else{		//�����ļ��رո�ups�ļ��
			//
		}
	}
	
	//��������
	for(i=0;i<NUM_OF_UPS;++i){
		if(_2023ups[i].UPS_SET_ACTIVE	==	TRUE){	//��ʼ��ʱ��򿪴���,���Դ���ͨ��
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