


#include "changer.h"

gchar* dc_month_list[12]={  "January",
							"February",
							"March",
							"April",
							"May",
							"June",
							"July",
							"August",
							"September",
							"October",
							"November",
							"December"}; 



date_changer_w* date_changer_new(date_w* date){

	date_changer_w* dcw=g_new0(date_changer_w,1);

	dcw->test=1973;

	dcw->current_date=date;

	dcw->self= gtk_grid_new ();

/*	dcw->m_left= gtk_label_new(NULL);
	gtk_label_set_width_chars(dcw->m_left,3);
	gtk_label_set_text(dcw->m_left,"<");

	dcw->m_right= gtk_label_new(NULL);
	gtk_label_set_width_chars(dcw->m_right,3);	
	gtk_label_set_text(dcw->m_right,">");*/


	// left arrow for months	
	dcw->m_left= lw_new(20,40);
	g_signal_connect(G_OBJECT(dcw->m_left->self), "button-press-event", G_CALLBACK(month_dec_clicked),(gpointer*) dcw);
	dcw->m_left->text="<";
	dcw->m_left->font_size=12;
	//update_lw(dcw->m_left);
	gtk_grid_attach (GTK_GRID (dcw->self),dcw->m_left->self ,0, 0, 1, 1);
	update_lw(dcw->m_left);


	// text view for months
	dcw->m_text= lw_new(100,40);
	dcw->m_text->text= dc_month_list[date->month-1];     ;//"September";
	dcw->m_text->fitWidthOnContent=TRUE;
	dcw->m_text->font_size=12;
	//update_lw(dcw->m_text);
	gtk_grid_attach (GTK_GRID (dcw->self),dcw->m_text->self ,1, 0, 1, 1);
	update_lw(dcw->m_text);	



	// right arrow for months	
	dcw->m_right= lw_new(20,40);
	g_signal_connect(G_OBJECT(dcw->m_right->self), "button-press-event", G_CALLBACK(month_inc_clicked), NULL);
	dcw->m_right->text=">";
	dcw->m_right->font_size=12;
	//update_lw(dcw->m_right);
	gtk_grid_attach (GTK_GRID (dcw->self),dcw->m_right->self ,2, 0, 1, 1);
	update_lw(dcw->m_right);


	label_w* spacer=lw_new(50,40);
	update_lw(spacer);
	gtk_grid_attach (GTK_GRID (dcw->self),spacer->self ,3, 0, 1, 1);
	




	// left arrow for years	
	dcw->y_left= lw_new(20,40);
	g_signal_connect(G_OBJECT(dcw->y_left->self), "button-press-event", G_CALLBACK(year_dec_clicked), NULL);
	//g_signal_connect(G_OBJECT(dcw->y_left->self), "button-release-event", G_CALLBACK(year_dec_clicked), NULL);
	dcw->y_left->text="<";
	dcw->y_left->font_size=12;
	//update_lw(dcw->m_left);
	gtk_grid_attach (GTK_GRID (dcw->self),dcw->y_left->self ,4, 0, 1, 1);
	update_lw(dcw->y_left);


	// text view for years
	dcw->y_text= lw_new(50,40);

	gchar ych[7];
	sprintf(ych, "%d", date->year);
	dcw->y_text->text=&ych[0];
	dcw->y_text->fitWidthOnContent=TRUE;
	dcw->y_text->font_size=12;
	//update_lw(dcw->m_text);
	gtk_grid_attach (GTK_GRID (dcw->self),dcw->y_text->self ,5, 0, 1, 1);
	update_lw(dcw->y_text);		


	// right arrow for years	
	dcw->y_right= lw_new(20,40);
	g_signal_connect(G_OBJECT(dcw->y_right->self), "button-press-event", G_CALLBACK(year_inc_clicked), NULL);
	//g_signal_connect(G_OBJECT(dcw->y_right->self), "button-release-event", G_CALLBACK(year_inc_clicked), NULL);
	dcw->y_right->text=">";
	dcw->y_right->font_size=12;
	//update_lw(dcw->m_right);
	gtk_grid_attach (GTK_GRID (dcw->self),dcw->y_right->self ,6, 0, 1, 1);
	update_lw(dcw->y_right);

	
	
	//gtk_grid_attach (GTK_GRID (dcw->self),dcw->m_left ,0, 0, 1, 1);

	return dcw;
}


void date_changer_update(date_changer_w* dcw){


	// text view for months
	
	dcw->m_text->text= dc_month_list[dcw->current_date->month-1];     ;//"September";
/*	dcw->m_text->fitWidthOnContent=TRUE;
	dcw->m_text->font_size=12;
	//update_lw(dcw->m_text);
	gtk_grid_attach (GTK_GRID (dcw->self),dcw->m_text->self ,1, 0, 1, 1);*/
	update_lw(dcw->m_text);	


	// text view for years
	

	gchar ych[7];
	sprintf(ych, "%d", dcw->current_date->year);
	dcw->y_text->text=&ych[0];
/*	dcw->y_text->fitWidthOnContent=TRUE;
	dcw->y_text->font_size=12;
	//update_lw(dcw->m_text);
	gtk_grid_attach (GTK_GRID (dcw->self),dcw->y_text->self ,5, 0, 1, 1);*/
	update_lw(dcw->y_text);		
}




gint year_inc_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data) {


	if(event->button!=1){
		return FALSE;
	}
	
	if(!(event->type==GDK_2BUTTON_PRESS ||
		    event->type==GDK_3BUTTON_PRESS) ){

	  g_print("year inc clicked\n");
		change_date (2);
	}

	return FALSE;
}


gint year_dec_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data) {

	if(event->button!=1){
		return FALSE;
	}	

		if(!(event->type==GDK_2BUTTON_PRESS ||
		    event->type==GDK_3BUTTON_PRESS) ){
			
			  g_print("year dec clicked\n");
				change_date (3);

		}

	return FALSE;
} 


gint month_inc_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data) {

	if(event->button!=1){
		return FALSE;
	}	

	

	if(!(event->type==GDK_2BUTTON_PRESS ||
		    event->type==GDK_3BUTTON_PRESS) ){
	
		  g_print("month inc clicked\n");
			change_date (0);
	}

	return FALSE;
}


gint month_dec_clicked(GtkWidget *widget, GdkEventButton *event, gpointer data) {

	if(event->button!=1){
		return FALSE;
	}	
    
	if(!(event->type==GDK_2BUTTON_PRESS ||
		    event->type==GDK_3BUTTON_PRESS) ){


			g_print("month dec clicked\n");
				change_date (1);	
	}

	return FALSE;
	
}









