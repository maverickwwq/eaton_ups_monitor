//************************************************
//AUTHOR:KIMI WANG
//DATE:2013-03-04
//DESCRIPTION:ͼ�ν��涨�塢�ص���������ʱ����
//************************************************


#define UI_H

#ifndef GTK_H
#define GTK_H
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#endif

#ifndef UPS_STATE_LOG_H
#define UPS_STATE_LOG_H
#include "ups_state_log.h"
#endif

#ifndef ALARM_H
#define ALARM_H
#include "alarm.h"
#endif

#define _G(str)		g_convert(str,-1,"UTF-8","GB2312",NULL,NULL,NULL)

//����widget�������С����ɫ
void setFontColor(GtkWidget *widget,int fontSize,char * colorStr);
//���������¼�
void destroyEvent(GtkWidget *widget,void *data);
//��ʱˢ�½���
gboolean refreshUI(void *nothing);

//---------------------------------------------------------------------------
//����������ɫ
//
//---------------------------------------------------------------------------
void setFontColor(GtkWidget *widget,int fontSize,char * colorStr){
	PangoFontDescription	*font=pango_font_description_from_string("Sans 13");
	pango_font_description_set_size(font,fontSize * PANGO_SCALE);
	GdkColor	color;
	gdk_color_parse(colorStr,&color);
	gtk_widget_modify_fg(GTK_WIDGET(widget),GTK_STATE_NORMAL,&color);
	gtk_widget_modify_font(GTK_WIDGET(widget),font);
}

//---------------------------------------------------------------------------
//�˳����
//
//---------------------------------------------------------------------------
void destroyEvent(GtkWidget *widget,void *data){
	gtk_main_quit();
}

//---------------------------------------------------------------------------
//���ڽ����˳���ť�Ļص�����
//
//---------------------------------------------------------------------------
/* Callback function in which closes the about_dialog created below */
static void
on_close (GtkDialog *dialog,
          gint       response_id,
          gpointer   user_data)
{
  gtk_widget_destroy (GTK_WIDGET (dialog));
}

//---------------------------------------------------------------------------
//�������ð�ť�Ļص�����
//
//---------------------------------------------------------------------------
static void
alarm_setting_cb (GtkDialog *dialog,
          gint       response_id,
          gpointer   user_data)
{
  printf("alarm_setting call\n");
}

//---------------------------------------------------------------------------
//�������ð�ť�Ļص�����
//
//---------------------------------------------------------------------------
static void
com_setting_cb (GtkDialog *dialog,
          gint       response_id,
          gpointer   user_data)
{
  printf("com_setting call\n");
}


//---------------------------------------------------------------------------
//�쳣��ʷ��¼��ť�Ļص�����
//
//---------------------------------------------------------------------------
static void
exception_history_cb (GtkDialog *dialog,
          gint       response_id,
          gpointer   user_data)
{
  printf("exception_history call\n");
}


//---------------------------------------------------------------------------
//���ڰ�ť�Ļص�����
//
//---------------------------------------------------------------------------
/* Callback function for the about action (see aboutdialog.c example) */
static void
about_callback (GSimpleAction *simple,
            GVariant      *parameter,
            gpointer       user_data)
{
	   GtkWidget *about_dialog;
	   about_dialog = gtk_about_dialog_new ();
	   const gchar *authors[] = {"wang weiqiang", NULL};
	   const gchar *documenters[] = {"wang weiqiang", NULL};

	   /* Fill in the about_dialog with the desired information */
	   gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG (about_dialog), "UPS Monitor");
	   gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG (about_dialog), "Copyright \xc2\xa9 ");
	   gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (about_dialog), authors);
	   gtk_about_dialog_set_documenters (GTK_ABOUT_DIALOG (about_dialog), documenters);
	   gtk_about_dialog_set_website_label (GTK_ABOUT_DIALOG (about_dialog), "Mail:821819304@qq.com");
	   gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (about_dialog), "www.2023.abrs.gov.cn");

	   /* The "response" signal is emitted when the dialog receives a delete event,
		* therefore we connect that signal to the on_close callback function
		* created above.
		*/
	   g_signal_connect (GTK_DIALOG (about_dialog), "response",
						G_CALLBACK (on_close), NULL);

	   /* Show the about dialog */
	   gtk_widget_show (about_dialog);
}

	static void
	quit_callback (GSimpleAction *simple,
				GVariant      *parameter,
				gpointer       user_data){
		GApplication *application = user_data;
		// kill sendDataViaCom thread
		// exit_();
		g_application_quit (application);
	}

	
static void activate_volumn (GObject    *switcher,
             GParamSpec *pspec,
             gpointer    user_data){
	int i = user_data;
	if (gtk_switch_get_active (GTK_SWITCH (switcher))){
		_2023ups[i].UPS_ALARM_ENABLE=TRUE;
	}
	else{
		_2023ups[i].UPS_ALARM_ENABLE=FALSE;
	}
	printf("\n\nYou press %d\n\n",i);
}
	

static void
activate (GApplication *app,
         gpointer      user_data)
{
	GtkWidget *mainWin;													//������
	GtkWidget *horizonAllUPS;											//
	GtkWidget *frame;													//
	GtkWidget *vbox;													//
	GtkWidget *hbox;													//
	GtkWidget *item;													//
	GtkWidget *evenbox;													//
	GtkWidget *volumn;
	GtkWidget *vol_switcher;
	GSimpleAction *about_action;
	GSimpleAction *alarm_setting_action;
//	GSimpleAction *com_setting;
//	GSimpleAction *exception_history;
	GError *error = NULL;	
	extern GtkWidget *itemValue[4][12];									//����ֵ
	extern const char *frames[];										//����豸����
	extern const char *items[];											//������

	mainWin = gtk_application_window_new ((GtkApplication*)app);
	gtk_window_set_title (GTK_WINDOW (mainWin), _G("2023̨�ڴ�UPS��ʾϵͳ"));
	gtk_window_set_default_size (GTK_WINDOW (mainWin), 960, 640);
	gtk_window_set_resizable(GTK_WINDOW(mainWin),TRUE);						//�ɸı��С
	gtk_window_set_position(GTK_WINDOW(mainWin),GTK_WIN_POS_CENTER);		//����	
	gtk_container_set_border_width(GTK_CONTAINER(mainWin),6);				//�߽��С
	
	GdkPixbuf *pixBuf;														//����Сͼ��													//
	pixBuf=gdk_pixbuf_new_from_file("icons/battery.png",&error);			//ͼ��·��
	if(!pixBuf){															//
		fprintf(stderr, "%s\n", error->message);							//
		//��Ҫ�����쳣������־��¼
		g_error_free(error);												//
	}																		//
	gtk_window_set_icon(GTK_WINDOW(mainWin),pixBuf);						//
															//
	GdkColor valueBGColor;
	horizonAllUPS=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,2);				//
	gtk_container_add(GTK_CONTAINER(mainWin),horizonAllUPS);				//
	gtk_container_add(GTK_CONTAINER(mainWin),horizonAllUPS);				//
	for(int frameCount=0;frameCount<NUM_OF_UPS;frameCount++){				//
		frame=gtk_frame_new(_G(frames[frameCount]));						//
		gtk_box_pack_start(GTK_BOX(horizonAllUPS),frame,TRUE,TRUE,2);		//
		vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,10);						//
		gtk_container_add(GTK_CONTAINER(frame),vbox);						//
		for(int i=0;i<NUM_OF_DATA-2;i++){
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
		volumn = gtk_label_new (_G("����"));
		itemValue[frameCount][9]=gtk_switch_new();
		gtk_switch_set_active (GTK_SWITCH (itemValue[frameCount][9]), FALSE);
		hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,2);
		gtk_box_set_homogeneous(GTK_BOX(hbox),TRUE);
		gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,5);						//
		setFontColor(volumn,11,"blue");											//
		gtk_box_pack_start(GTK_BOX(hbox),volumn,TRUE,TRUE,2);						//
		gtk_box_pack_start(GTK_BOX(hbox),itemValue[frameCount][9],TRUE,TRUE,2);					//
		g_signal_connect (GTK_SWITCH (itemValue[frameCount][9]),"notify::active",G_CALLBACK (activate_volumn),frameCount);		
		itemValue[frameCount][10] = gtk_info_bar_new ();
		gtk_box_pack_start (GTK_BOX (vbox), itemValue[frameCount][10], FALSE, FALSE, 0);
		gtk_info_bar_set_message_type (GTK_INFO_BAR (itemValue[frameCount][10]),\
			GTK_MESSAGE_QUESTION);
		itemValue[frameCount][11]= gtk_label_new (_G("����"));
		gtk_box_pack_start (GTK_BOX (gtk_info_bar_get_content_area (GTK_INFO_BAR (itemValue[frameCount][10]))),\
			itemValue[frameCount][11], FALSE, FALSE, 0);
	}
	
	g_timeout_add(REFRESH_PER_X_SECONDS*1000,(GSourceFunc)refreshUI,NULL);
	
	about_action = g_simple_action_new ("about", NULL);
	g_signal_connect (about_action, "activate", G_CALLBACK (about_callback),
		GTK_WINDOW (mainWin));
	g_action_map_add_action (G_ACTION_MAP (mainWin), G_ACTION (about_action));
	
	alarm_setting_action = g_simple_action_new ("alarm_setting",NULL);
	g_signal_connect (alarm_setting_action,"activate",G_CALLBACK(alarm_setting_cb),GTK_WINDOW(mainWin));
	g_action_map_add_action (G_ACTION_MAP(mainWin),G_ACTION(alarm_setting_action));
	gtk_widget_show_all(mainWin);
}

static void 
startup(GApplication *app,
         gpointer      user_data){
	/* Initialize variables */
	GSimpleAction *quit_action;
	GtkBuilder *builder;
	GError *error = NULL;
	  	
	quit_action = g_simple_action_new("quit",NULL);
	g_signal_connect (quit_action, "activate", G_CALLBACK (quit_callback),
		GTK_WINDOW (app));
	/* Add it to the window */
	g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (quit_action));	
	
	
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
	extern GtkWidget *itemValue[4][12];
	char buf[25];
	int i=0,j=0;
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
					setFontColor(itemValue[i][3],15,"green");
					sprintf(buf,"%d V",_2023ups[i].INPUT_VOLTAGE);
					gtk_label_set_text(GTK_LABEL(itemValue[i][3]),\
						buf);
					setFontColor(itemValue[i][4],15,"green");
					sprintf(buf,"%d Hz",_2023ups[i].INPUT_FREQUENCY);
					gtk_label_set_text(GTK_LABEL(itemValue[i][4]),\
						buf);
				}
				if(_2023ups[i].CMD_06_CHECK){
					setFontColor(itemValue[i][6],15,"green");
					sprintf(buf,"%d %%",_2023ups[i].BATTERY_CAPACITY);
					gtk_label_set_text(GTK_LABEL(itemValue[i][6]),\
						buf);
				}
				if(_2023ups[i].CMD_42_CHECK){
					setFontColor(itemValue[i][7],15,"green");
					sprintf(buf,"%d V",_2023ups[i].OUTPUT_VOLTAGE);
					gtk_label_set_text(GTK_LABEL(itemValue[i][7]),\
						buf);
					setFontColor(itemValue[i][8],15,"green");
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
	static _Bool ups_communicate_normal=TRUE,input_power_abnormal=FALSE,ups_error=FALSE;
	//��������
	for(i=0;i<NUM_OF_UPS;++i){
		if(_2023ups[i].UPS_SET_ACTIVE	==	TRUE){	//��ʼ��ʱ��򿪴���,���Դ���ͨ��
			if(_2023ups[i].UPS_COMMUNICATE_NORMAL){	//ͨ������
				if(!ups_communicate_normal){
					ups_communicate_normal=TRUE;
					conditionChangeLog(50,TRUE,i);
				}
				if(!_2023ups[i].INPUT_POWER_ABNORMAL){//�е�����
					if(input_power_abnormal){
						conditionChangeLog(3,TRUE,i);
						input_power_abnormal=FALSE;
					}
				}
				else{						//�е��쳣
					if(!input_power_abnormal){
						conditionChangeLog(3,FALSE,i);
						input_power_abnormal=TRUE;
						gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
							GTK_MESSAGE_WARNING);
						gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("�е��쳣"));
					}
					if(_2023ups[i].UPS_ALARM_ENABLE)
						makeSound(ALARM_INPUT_ERROR);
					continue;
				}
				if(!_2023ups[i].UPS_ERROR){	//ups����
					//
					if(ups_error){
						conditionChangeLog(4,TRUE,i);
						ups_error=FALSE;
					}
				}
				else{						//ups����
					if(!ups_error){
						gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
							GTK_MESSAGE_ERROR);
						gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("UPS����"));
						ups_error=TRUE;
						conditionChangeLog(4,FALSE,i);
					}
					if(_2023ups[i].UPS_ALARM_ENABLE)
						makeSound(ALARM_UPS_ERROR);
					continue;
				}
				//���ж������Ļ���ִ������
				gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
					GTK_MESSAGE_QUESTION);
				gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("����"));
			}
			else{							//ͨ���쳣
				if(ups_communicate_normal){
					ups_communicate_normal=FALSE;
					conditionChangeLog(50,FALSE,i);
					gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
						GTK_MESSAGE_INFO);
					gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("ͨ���쳣"));
				}
				if(_2023ups[i].UPS_ALARM_ENABLE)
					makeSound(ALARM_NOT_CONNECT);
				continue;
			}
		}
	}
	return TRUE;
}