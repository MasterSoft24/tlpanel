#include <config.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include <glib/gi18n.h>



#include "helper.h"





typedef struct _day_w{ // day widget

	GtkWidget* self;
	GtkContainer *box;
	GtkWidget *drawingArea;
	cairo_surface_t *pixmap;

	date_w* date;

	
	gboolean isCurrentMonth;
	gboolean isToday;
	//int dayOfMonth;

	gboolean haveTask;
		
	

}day_w;


const day_w* construct();
day_w* dw_new();
void update_dw(day_w* obj);
void free_dw(day_w* obj);

//static gboolean on_expose_event (GtkWidget *widget,GdkEventExpose *event,gpointer data);











