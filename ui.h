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

#define _G(str)		g_convert(str,-1,"UTF-8","GB2312",NULL,NULL,NULL)


//设置widget的字体大小及颜色
void setFontColor(GtkWidget *widget,int fontSize,char * colorStr);
//窗口销毁事件
void destroyEvent(GtkWidget *widget,void *data);
//定时刷新界面
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


/* Callback function in which closes the about_dialog created below */
static void
on_close (GtkDialog *dialog,
          gint       response_id,
          gpointer   user_data)
{
  gtk_widget_destroy (GTK_WIDGET (dialog));
}


static void
alarm_setting_cb (GtkDialog *dialog,
          gint       response_id,
          gpointer   user_data)
{
  printf("alarm_setting call\n");
}

static void
com_setting_cb (GtkDialog *dialog,
          gint       response_id,
          gpointer   user_data)
{
  printf("com_setting call\n");
}

static void
exception_history_cb (GtkDialog *dialog,
          gint       response_id,
          gpointer   user_data)
{
  printf("exception_history call\n");
}

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


static void
activate (GApplication *app,
         gpointer      user_data)
{
	GtkWidget *mainWin;													//主窗口
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
	GSimpleAction *com_setting;
	GSimpleAction *exception_history;
	GError *error = NULL;	
	extern GtkWidget *itemValue[4][11];									//参数值
	extern const char *frames[];										//监控设备名称
	extern const char *items[];											//参数名

	mainWin = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (mainWin), _G("2023台节传UPS警示系统"));
	gtk_window_set_default_size (GTK_WINDOW (mainWin), 960, 640);
	gtk_window_set_resizable(GTK_WINDOW(mainWin),TRUE);						//可改变大小
	gtk_window_set_position(GTK_WINDOW(mainWin),GTK_WIN_POS_CENTER);		//居中	
	gtk_container_set_border_width(GTK_CONTAINER(mainWin),6);				//边界大小
	
	GdkPixbuf *pixBuf;														//设置小图标													//
	pixBuf=gdk_pixbuf_new_from_file("icons/battery.png",&error);			//图标路径
	if(!pixBuf){															//
		fprintf(stderr, "%s\n", error->message);							//
		//需要加入异常处理及日志记录
		g_error_free(error);												//
	}																		//
	gtk_window_set_icon(GTK_WINDOW(mainWin),pixBuf);						//
		
	int frameCount=0;														//
	GdkColor valueBGColor;
	//horizonAllUPS=gtk_hbox_new(TRUE,2);									//
	horizonAllUPS=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,2);				//
	gtk_container_add(GTK_CONTAINER(mainWin),horizonAllUPS);
	gtk_container_add(GTK_CONTAINER(mainWin),horizonAllUPS);				//
	for(frameCount=0;frameCount<NUM_OF_UPS;frameCount++){							//
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
			gtk_widget_modify_bg(evenbox, GTK_STATE_NORMAL, &valueBGColor);		//背景颜色
			gtk_box_pack_start(GTK_BOX(hbox),evenbox,TRUE,TRUE,2);					//
			itemValue[frameCount][i]=gtk_label_new("-- --");									//
			setFontColor(itemValue[frameCount][i],15,"green");									//
			gtk_container_add(GTK_CONTAINER(evenbox),itemValue[frameCount][i]);					//
		}
		volumn = gtk_label_new (_G("声音"));
		vol_switcher = gtk_switch_new ();
		gtk_switch_set_active (GTK_SWITCH (vol_switcher), TRUE);
		
		hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,2);
		gtk_box_set_homogeneous(GTK_BOX(hbox),TRUE);
		gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,5);						//
		//item=gtk_label_new(_G(items[i]));										//
		//volumn = gtk_label_new ("Volumn");
		setFontColor(volumn,11,"blue");											//
		gtk_box_pack_start(GTK_BOX(hbox),volumn,TRUE,TRUE,2);						//
//		evenbox=gtk_event_box_new();											//
//		gdk_color_parse("black",&valueBGColor);
//		gtk_widget_modify_bg(evenbox, GTK_STATE_NORMAL, &valueBGColor);		//背景颜色
		gtk_box_pack_start(GTK_BOX(hbox),vol_switcher,TRUE,TRUE,2);					//
//		itemValue[frameCount][i]=gtk_label_new("-- --");									//
//		setFontColor(itemValue[frameCount][i],15,"green");									//
//		gtk_container_add(GTK_CONTAINER(evenbox),vol_switcher);					//
		
		
		
		itemValue[frameCount][9] = gtk_info_bar_new ();
		gtk_box_pack_start (GTK_BOX (vbox), itemValue[frameCount][9], FALSE, FALSE, 0);
		gtk_info_bar_set_message_type (GTK_INFO_BAR (itemValue[frameCount][9]),\
			GTK_MESSAGE_QUESTION);
		itemValue[frameCount][10]= gtk_label_new (_G("正常"));
		gtk_box_pack_start (GTK_BOX (gtk_info_bar_get_content_area (GTK_INFO_BAR (itemValue[frameCount][9]))),\
			itemValue[frameCount][10], FALSE, FALSE, 0);
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


//刷新图形函数+语音报警
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
//	static unsigned int count=0;

/*
	printf("\n--------------------------------------------\n");
	printf("--------------------------------------------\n");
	printf("通信:%s\n",(_2023ups[i].UPS_COMMUNICATE_NORMAL==TRUE)?"正常":"故障");
	printf("UPS:%s\n",(_2023ups[i].UPS_ERROR==FALSE)?"正常":"故障");
	printf("市电:%s\n",(_2023ups[i].INPUT_POWER_ABNORMAL==FALSE)?"正常":"故障");
	printf("市电电压:%d\n",_2023ups[i].INPUT_VOLTAGE);
	printf("市电频率:%d\n",_2023ups[i].INPUT_FREQUENCY);
	printf("Count:%4d\n",count);
	printf("--------------------------------------------\n");
	printf("--------------------------------------------\n");
*/
	extern GtkWidget *itemValue[4][11];
	char buf[25];
	int i=0,j=0;
	for(i=0;i<NUM_OF_UPS;++i){
		if(_2023ups[i].UPS_SET_ACTIVE	==	TRUE){	// 
			if(_2023ups[i].UPS_COMMUNICATE_NORMAL){
				setFontColor(itemValue[i][0],15,"green");
				gtk_label_set_text(GTK_LABEL(itemValue[i][0]),_G("通信正常"));
				if(_2023ups[i].CMD_01_CHECK){
					if(_2023ups[i].INPUT_POWER_ABNORMAL){
						gtk_label_set_text(GTK_LABEL(itemValue[i][2]),_G("市电故障"));
						setFontColor(itemValue[i][2],15,"red");
					}
					else{
						gtk_label_set_text(GTK_LABEL(itemValue[i][2]),_G("市电正常"));
						setFontColor(itemValue[i][2],15,"green");
					}
					if(_2023ups[i].DISCHARGE){
						setFontColor(itemValue[i][5],15,"red");
						gtk_label_set_text(GTK_LABEL(itemValue[i][5]),_G("放电"));
					}
					else{
						setFontColor(itemValue[i][5],15,"green");
						gtk_label_set_text(GTK_LABEL(itemValue[i][5]),_G("充电"));
					}
				}
				if(_2023ups[i].CMD_02_CHECK){
					if(_2023ups[i].UPS_ERROR){
						gtk_label_set_text(GTK_LABEL(itemValue[i][1]),_G("故障"));
						setFontColor(itemValue[i][1],15,"red");
					}
					else{
						gtk_label_set_text(GTK_LABEL(itemValue[i][1]),_G("正常"));
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
			else{							//通信故障
				for(j=0;j<=8;j++){
 					setFontColor(itemValue[i][j],15,"red");
 					gtk_label_set_text(GTK_LABEL(itemValue[i][j]),"-- --");
				}
				setFontColor(itemValue[i][0],15,"red");
				gtk_label_set_text(GTK_LABEL(itemValue[i][0]),_G("通信故障"));
			}
		}
		else{		//配置文件关闭该ups的监控
			//
		}
	}
	static _Bool ups_communicate_normal=TRUE,input_power_abnormal=FALSE,ups_error=FALSE;
	//声音报警
	for(i=0;i<NUM_OF_UPS;++i){
		if(_2023ups[i].UPS_SET_ACTIVE	==	TRUE){	//初始化时会打开串口,尝试串口通信
			if(_2023ups[i].UPS_COMMUNICATE_NORMAL){	//通信正常
				if(!ups_communicate_normal){
					ups_communicate_normal=TRUE;
					conditionChangeLog(50,TRUE,i);
				}
				if(!_2023ups[i].INPUT_POWER_ABNORMAL){//市电正常
					if(input_power_abnormal){
						conditionChangeLog(3,TRUE,i);
						input_power_abnormal=FALSE;
					}
				}
				else{						//市电异常
					if(!input_power_abnormal){
						conditionChangeLog(3,FALSE,i);
						input_power_abnormal=TRUE;
						gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
							GTK_MESSAGE_WARNING);
						gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("市电异常"));
					}					
					makeSound(ALARM_INPUT_ERROR);
					continue;
				}
				if(!_2023ups[i].UPS_ERROR){	//ups正常
					//
					if(ups_error){
						conditionChangeLog(4,TRUE,i);
						ups_error=FALSE;
					}
				}
				else{						//ups故障
					if(!ups_error){
						gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
							GTK_MESSAGE_ERROR);
						gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("UPS故障"));
						ups_error=TRUE;
						conditionChangeLog(4,FALSE,i);
					}
					makeSound(ALARM_UPS_ERROR);
					continue;
				}
				//所有都正常的话走执行这里
				gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
					GTK_MESSAGE_QUESTION);
				gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("正常"));
			}
			else{							//通信异常
				if(ups_communicate_normal){
					ups_communicate_normal=FALSE;
					conditionChangeLog(50,FALSE,i);
					gtk_info_bar_set_message_type(GTK_INFO_BAR (itemValue[i][9]),\
						GTK_MESSAGE_INFO);
					gtk_label_set_text(GTK_LABEL(itemValue[i][10]),_G("通信异常"));
				}
				makeSound(ALARM_UPS_ERROR);
				makeSound(ALARM_NOT_CONNECT);
				continue;
			}
		}
	}
	return TRUE;
}