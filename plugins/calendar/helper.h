#include <config.h>
#include <gtk/gtk.h>


#include <glib/gi18n.h>

#include <stdio.h>
#include <time.h>

#ifndef CAL_HELPER
#define CAL_HELPER 1



typedef struct _date_w{

	int day;
	int month;
	int year;

}date_w;

int getWeekDay(date_w date);
gboolean IsLeapYear(int year);
int getMonthDaysNumber(date_w date);
date_w* date_w_add_days(date_w* date,int count);
date_w* date_w_add_months(date_w* date,int months);
date_w* get_current_day();
date_w* get_month_begin(date_w* date);
date_w* get_month_end(date_w* date);


#endif