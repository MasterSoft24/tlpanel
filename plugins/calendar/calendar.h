#include <config.h>
#include <gtk/gtk.h>


#include <glib/gi18n.h>

#include "day_widget.h"
#include "label_widget.h"
#include "changer.h"



typedef struct _calendar_w{

	GtkWidget *self;

	GtkWidget *container;
	

	day_w *cal_grid[42];
        
        label_w* dw_labels[7];

	day_w** p_cal_grid;

	int current_day_week; // counter
	int current_week;	 // counter

	int currentMonthNumber;
	int currentDayMonthNumber;


	const gchar* dayNames[8];


	date_changer_w* changer;
	

}calendar_w;


//gchar* dayNames[8]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat","Sun"};


#define FIRST_WEEK_DAY 1 // 0 - sunday; 1- monday


calendar_w* calendar_new(date_w* date);
//void destruct_calendar(calendar_w* cal);
//void update_calendar(calendar_w* obj);

void refill_calendar(calendar_w* cw,date_w* fdm);

void change_date(int type); // type=0 inc month; type=1 dec month; type=2 inc year; type=3 dec year




