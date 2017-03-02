#include "label_widget.h"


//==================================================================

#if GTK_CHECK_VERSION(3, 0, 0)
static gint draw(GtkWidget *widget, cairo_t *cr, label_w *lx_b) {
#else
static gint exposeEvent(GtkWidget *widget, GdkEventExpose *event, label_w *lx_b) {
#endif



#if GTK_CHECK_VERSION(3, 0, 0)
    //cairo_set_source_rgb(cr, 0, 0, 0); // FIXME: set black color from the style


	
	GdkRGBA color;
	gdk_rgba_parse ( &color,"red");
    //gdk_cairo_set_source_rgba(cr, &color);
#else
    cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(widget));
    GtkStyle *style = gtk_widget_get_style(lx_b->drawingArea);

    gdk_cairo_region(cr, event->region);
    cairo_clip(cr);

    gdk_cairo_set_source_color(cr, &style->black);
#endif
    cairo_set_source_surface(cr, lx_b->pixmap, 0, 0);

	//cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
    cairo_paint(cr);

    //check_cairo_status(cr);
#if !GTK_CHECK_VERSION(3, 0, 0)
    cairo_destroy(cr);
#endif

  return 0;
}



//==================================================================


label_w* lw_construct(int width,int height){


	label_w* obj= g_new0(label_w,1);

	obj->fitWidthOnContent=FALSE;
	obj->label_height=height;
	obj->label_width=width;
	obj->font_size=15;

	GtkWidget* p = gtk_event_box_new();

		gtk_widget_set_events (p, GDK_BUTTON_PRESS_MASK);

		

	obj->self=p;

	obj->box = GTK_CONTAINER(p);

	

	obj->drawingArea = gtk_drawing_area_new();

	gtk_widget_set_size_request(obj->drawingArea, width, height);

	gtk_container_add(obj->box, obj->drawingArea);

	

	obj->pixmap = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);

	gtk_widget_show(obj->drawingArea);






	

#if GTK_CHECK_VERSION(3, 0, 0)
    g_signal_connect (G_OBJECT (obj->drawingArea), "draw",
          G_CALLBACK(draw), (gpointer) obj);
#else
    g_signal_connect (G_OBJECT (obj->drawingArea), "expose-event",
          G_CALLBACK (exposeEvent), (gpointer) obj);
#endif




	
	

	return obj;

}


//==================================================================



label_w* lw_new(int width,int height){

	//return(g_object_new(MY_TYPE_CPU, NULL));
	return lw_construct(width,height);

}


//==================================================================


void update_lw(label_w* obj){

	cairo_t *cr;
	cairo_text_extents_t extents;
	double x,y;
    
	
    cr =  cairo_create(obj->pixmap);
	
	// clear previous content of pixmap
	cairo_save (cr);
	cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
	cairo_paint(cr);
	cairo_restore (cr);


	cairo_text_extents (cr, obj->text, &extents);

	

	// make transparentness of pixmap
    cairo_set_source_rgba(cr, 204,4,90,0);
    cairo_paint(cr);


/*	if(obj->fitWidthOnContent==TRUE){
		obj->label_width= 100;//extents.width;
	}*/

			// draw some background
		cairo_set_source_rgba(cr, 0,0,0,0.07);
		cairo_rectangle (cr,0,0,obj->label_width,obj->label_height);
		cairo_fill (cr) ; 
	
	
		// print text on surface
		//GdkRGBA color;
		//gdk_rgba_parse ( &color,"rgba(0,0,0,1)");
		cairo_set_source_rgba(cr, 0,0,0,1);


	cairo_set_font_size(cr, obj->font_size);

	

	cairo_text_extents (cr, obj->text, &extents);
	x = obj->label_width/2 -(extents.width/2 + extents.x_bearing);
	y = obj->label_height/2 -(extents.height/2 + extents.y_bearing);

	cairo_move_to(cr, x, y);
	cairo_show_text(cr, obj->text);
	
	
	// this call emit update and repaint surface (i dont't understand for what it need)
	gtk_widget_queue_draw( obj->drawingArea );


	
    cairo_destroy(cr);


}


void lw_clicked(GtkWidget *widget, gpointer data) {
    
  g_print("clicked\n");
}


void free_lw(label_w* obj){
    
    
    cairo_surface_finish(obj->pixmap);
    gtk_widget_destroy(obj->drawingArea);
    gtk_widget_destroy(obj->self);
    g_free(obj);
}













