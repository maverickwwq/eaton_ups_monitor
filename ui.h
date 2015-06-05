#define UI_H

#ifndef GTK_H
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#endif
//#include <stdlib.h>

#define _G(str)		g_convert(str,-1,"UTF-8","GB2312",NULL,NULL,NULL)


//设置widget的字体大小及颜色
void setFontColor(GtkWidget *widget,int fontSize,char * colorStr);
//窗口销毁事件
void destroyEvent(GtkWidget *widget,void *data);


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