

// single calendar day presentation

#include "day_widget.h"


//==================================================================

#if GTK_CHECK_VERSION(3, 0, 0)
static gint draw(GtkWidget *widget, cairo_t *cr, day_w *lx_b) {
#else
static gint exposeEvent(GtkWidget *widget, GdkEventExpose *event, day_w *lx_b) {
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


day_w* dw_construct(){


	day_w* obj= g_new0(day_w,1);

	GtkWidget* p = gtk_event_box_new();

	obj->self=p;

	obj->box = GTK_CONTAINER(p);

	

	obj->drawingArea = gtk_drawing_area_new();

	gtk_widget_set_size_request(obj->drawingArea, 40, 40);

	gtk_container_add(obj->box, obj->drawingArea);

	

	obj->pixmap = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 40,40);

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

day_w* dw_new(){

	//return(g_object_new(MY_TYPE_CPU, NULL));
	return dw_construct();

}


//==================================================================

void update_dw(day_w* obj){

	cairo_t *cr;
	cairo_text_extents_t extents;
	double x,y;
    

	//obj->date= get_current_day();


	//date_w* dd=date_w_add_months(obj->date,-150);

	//obj->dayOfMonth= obj->date->day;
	 
	
    cr =  cairo_create(obj->pixmap);
	
	// clear previous content of pixmap
	cairo_save (cr);
	cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
	cairo_paint(cr);
	cairo_restore (cr);
	

	// make transparentness of pixmap
    cairo_set_source_rgba(cr, 204,4,90,0);
    cairo_paint(cr);



	if(obj->isToday ==TRUE){

		// draw frame rectangle
		cairo_set_source_rgba(cr, 0,0,0,1);
		cairo_rectangle (cr,0,0,40,40);
		cairo_stroke (cr);
	}
	else{
		
		// draw frame rectangle
/*		cairo_set_source_rgba(cr, 30,30,30,1);
		cairo_rectangle (cr,0,0,40,40);
		cairo_stroke (cr);*/
	}
	
	




	if(obj->isCurrentMonth == TRUE){

		
		// draw some background
		cairo_set_source_rgba(cr, 0,0,0,0.01);
		cairo_rectangle (cr,0,0,40,40);
		cairo_fill (cr) ; 
	
	
		// print text on surface
		//GdkRGBA color;
		//gdk_rgba_parse ( &color,"rgba(0,0,0,1)");
		cairo_set_source_rgba(cr, 0,0,0,1);
	}
	else{

		// draw some background
		cairo_set_source_rgba(cr, 0,0,0,0.01);
		cairo_rectangle (cr,0,0,40,40);
		cairo_fill (cr) ; 
	
	
		// print text on surface
		//GdkRGBA color;
		//gdk_rgba_parse ( &color,"rgba(100,100,100,0.3)");
		cairo_set_source_rgba(cr, 100,100,100,0.3);

	}
	


	cairo_set_font_size(cr, 20.0);

	gchar str[3];
	sprintf(str, "%d", obj->date->day); //obj->dayOfMonth

	cairo_text_extents (cr, str, &extents);
	x = 20.0-(extents.width/2 + extents.x_bearing);
	y = 20.0-(extents.height/2 + extents.y_bearing);

	cairo_move_to(cr, x, y);
	cairo_show_text(cr, str);
	
	
	// this call emit update and repaint surface (i dont't understand for what it need)
	gtk_widget_queue_draw( obj->drawingArea );


	
    cairo_destroy(cr);

}

void free_dw(day_w* obj){
    
    g_free(obj->date);
    cairo_surface_finish(obj->pixmap);
    gtk_widget_destroy(obj->drawingArea);
    gtk_widget_destroy(obj->self);
    g_free(obj);
}










