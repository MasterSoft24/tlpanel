#include <config.h>
#include <gtk/gtk.h>


#include <glib/gi18n.h>


#ifndef DATE_CHANGER
#define DATE_CHANGER 1

#include "helper.h"
#include "label_widget.h"


typedef struct _date_changer_w{

	GtkWidget* self;

	date_w* current_date;
	
	label_w*	m_left;
	label_w*	m_text;
	label_w*	m_right;
	
	label_w*	y_left;
	label_w*	y_text;
	label_w*	y_right;

	int test;


}date_changer_w;





date_changer_w* date_changer_new(date_w* date);

void date_changer_update(date_changer_w* dcw);

gint year_inc_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data);
gint year_dec_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data) ;
gint month_inc_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data);
gint month_dec_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data);


#endif
