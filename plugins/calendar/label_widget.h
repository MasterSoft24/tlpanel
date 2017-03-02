#include <config.h>
#include <gtk/gtk.h>


#include <glib/gi18n.h>

#ifndef LABEL_WIDGET
#define LABEL_WIDGET 1

typedef struct _label_w{ // day widget

	GtkWidget* self;
	GtkContainer *box;
	GtkWidget *drawingArea;
	cairo_surface_t *pixmap;
	//GtkWidget* event_box;

	gchar* text;
	gboolean fitWidthOnContent;

	int label_height;
	int label_width;
	int font_size;

	

}label_w;


label_w* lw_new(int width,int height);
void update_lw(label_w* obj);
//void destruct_day_w(day_w)
void lw_clicked(GtkWidget *widget, gpointer data);
void free_lw(label_w* obj);


#endif
