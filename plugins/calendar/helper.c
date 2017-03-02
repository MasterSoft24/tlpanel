
#include "helper.h"


#include <stdio.h>
#include <time.h>

// return day of week as zero-based value, where 0 is sunday and 6 is saturday (thanks to Michael Keith and Tom Craver )
int getWeekDay(date_w date){

	int d    = date.day;   ; 
	int m    = date.month    ; 
	int y    = date.year ; 

	return (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
}



gboolean IsLeapYear(int year){
    if (year % 4 != 0) return FALSE;
    if (year % 400 == 0) return TRUE;
    if (year % 100 == 0) return FALSE;
    return TRUE;
}




int getMonthDaysNumber(date_w date){

	int numberOfDays;  
	if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)  
	  numberOfDays = 30;  
	else if (date.month == 2)  
	{ 
		gboolean isLeapYear = (date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0);  
	  if (isLeapYear)  
		numberOfDays = 29;  
	  else  
		numberOfDays = 28;  
	}  
	else  
	  numberOfDays = 31; 

	return numberOfDays;
}




date_w* date_w_add_days(date_w* date,int count){// if first param == NULL then will use curent date

	time_t rawtime;
	struct tm * timeinfo;
	//char buffer [80];

	date_w* out= g_new0(date_w,1);
	
	
	gint64 delta=count*86400; // delta in seconds

	if(date == NULL){

		time ( &rawtime ); //curent time date in seconds since unix epoch
		rawtime+=(time_t)delta;	
	}
	else{

		gchar str[30];
		struct tm *  tmm;
		
		tmm= g_new0(struct tm, 1);
		
		sprintf(str, "%d/%d/%d", date->day,date->month,date->year);
		//gchar* strs="2001/02/03";
		strptime(str, "%d/%m/%Y", tmm);

		rawtime=mktime(tmm);

		rawtime+=(time_t)delta;

		//free(tmm);

	}

	timeinfo = localtime ( &rawtime );

	out->year= 1900 + timeinfo->tm_year;
	out->month= 1 + timeinfo->tm_mon;
	out->day=timeinfo->tm_mday;


	return out;

}



date_w* get_current_day(){

	struct tm * timeinfo;
	time_t rawtime;
	date_w* out= g_new0(date_w,1);

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	out->year= 1900 + timeinfo->tm_year;
	out->month= 1 + timeinfo->tm_mon;
	out->day=timeinfo->tm_mday;

	return out;
}



date_w* date_w_add_months(date_w* date,int months){// if first param == NULL then will use curent date

	struct tm *  d;
	gchar str[30];
		
	d= g_new0(struct tm, 1);
		
	sprintf(str, "%d/%d/%d", date->day,date->month,date->year);
		
	strptime(str, "%d/%m/%Y", d);

	date_w dw;
	dw.day=d->tm_mday;
	dw.month=1+d->tm_mon;
	dw.year=1900+d->tm_year;
		

    gboolean isLastDayInMonth = d->tm_mday == getMonthDaysNumber(dw);

	int year,month,dy,dm;
	
	
	if(months < 0){

		dy= months / 12;
		dm= months % 12;

		if(0-months < dw.month){
			year=dw.year;
			month= dw.month+months;
		}
		else{
			if((0-dm) >= dw.month){
				dy--;
			}
		
			year+= dw.year +dy;
			if(dm != 0){
				month=12+ (dw.month+dm);
			}
			else{
				month=dw.month;
			}
		}


		
	}
	else{
		year = dw.year + months / 12;
		month = dw.month + months % 12;

		if (month > 11)
		{
		    year += 1;
		    month -= 12;
		}

		
	}



    int day;

	dw.month=month;
	dw.year=year;
	
    if (isLastDayInMonth==TRUE){
        day = getMonthDaysNumber(dw); // Last day of month maps to last day of result month
	}
    else{
        day = MIN(dw.day, getMonthDaysNumber(dw));
	}


	date_w* out= g_new0(date_w,1);

	out->year= year;
	out->month= month;
	out->day=day;

	

    return out;
	
}



date_w* get_month_begin(date_w* date){

	date->day=1;
	return date;
}



date_w* get_month_end(date_w* date){

	int d=getMonthDaysNumber(*date);
	date->day=d;
	return date;

}










