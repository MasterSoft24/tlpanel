

#include "calendar.h"


calendar_w* GLOBAL_CALENDAR_PTR;


void insert_day(date_w* day,calendar_w* cal){


	
	cal->cal_grid[cal->current_day_week + cal->current_week*7]->date=day;

	if(day->month == cal->currentMonthNumber){
		cal->cal_grid[cal->current_day_week + cal->current_week*7]->isCurrentMonth=TRUE;

		if(day->day == cal->currentDayMonthNumber){
			cal->cal_grid[cal->current_day_week + cal->current_week*7]->isToday=TRUE;
		}
		
	}
	else{
		cal->cal_grid[cal->current_day_week + cal->current_week*7]->isCurrentMonth=FALSE;
	}
	

	update_dw(cal->cal_grid[cal->current_day_week + cal->current_week*7]);
	
	cal->current_day_week++;
	
	if(cal->current_day_week>6){
		cal->current_day_week=0;
		cal->current_week++;
	}

	
}




void update_day(date_w* day,calendar_w* cal){


	
	cal->cal_grid[cal->current_day_week + cal->current_week*7]->date->day=day->day;
	cal->cal_grid[cal->current_day_week + cal->current_week*7]->date->month=day->month;
	cal->cal_grid[cal->current_day_week + cal->current_week*7]->date->year=day->year;


	cal->cal_grid[cal->current_day_week + cal->current_week*7]->isCurrentMonth=FALSE;
	cal->cal_grid[cal->current_day_week + cal->current_week*7]->isToday=FALSE;

	if(day->month == cal->currentMonthNumber){
		cal->cal_grid[cal->current_day_week + cal->current_week*7]->isCurrentMonth=TRUE;

		if(day->day == cal->currentDayMonthNumber){
			cal->cal_grid[cal->current_day_week + cal->current_week*7]->isToday=TRUE;
		}
		
	}
	else{
		cal->cal_grid[cal->current_day_week + cal->current_week*7]->isCurrentMonth=FALSE;
	}
	

	update_dw(cal->cal_grid[cal->current_day_week + cal->current_week*7]);
	
	cal->current_day_week++;
	
	if(cal->current_day_week>6){
		cal->current_day_week=0;
		cal->current_week++;
	}

	
}







calendar_w* calendar_new(date_w* date){

	

	calendar_w* cw=g_new0(calendar_w,1);

	GLOBAL_CALENDAR_PTR=cw; // get pointer for global usage

	cw->changer= date_changer_new(date);

	


	cw->container=gtk_box_new(GTK_ORIENTATION_VERTICAL,1);

	gtk_box_pack_start(cw->container,cw->changer->self,FALSE,FALSE,0);

	cw->self= gtk_grid_new ();

		gtk_box_pack_start(cw->container,cw->self,FALSE,FALSE,0);
		//gtk_grid_attach (GTK_GRID (cw->self), cw->changer->self,0, 0, 7, 1);


	cw->current_day_week=0;
	cw->current_week=0;
	cw->currentDayMonthNumber=0;
	cw->currentMonthNumber=0;

	cw->dayNames[0]="Sun";
	cw->dayNames[1]="Mon";
	cw->dayNames[2]="Tue";
	cw->dayNames[3]="Wed";
	cw->dayNames[4]="Thu";
	cw->dayNames[5]="Fri";
	cw->dayNames[6]="Sat";
	cw->dayNames[7]="Sun";
		
	

	cw->p_cal_grid= &cw->cal_grid[0];
        int dwlc=0;
	for(int i=FIRST_WEEK_DAY; i<=FIRST_WEEK_DAY+6;i++){

		//label_w* l=lw_new(40,40);
            cw->dw_labels[dwlc]=lw_new(40,40);
		cw->dw_labels[dwlc]->text=cw->dayNames[i];
		gtk_grid_attach (GTK_GRID (cw->self), cw->dw_labels[dwlc]->self,cw->current_day_week, cw->current_week, 1, 1);
		update_lw(cw->dw_labels[dwlc]);

		cw->current_day_week++;
	
		if(cw->current_day_week>6){
			cw->current_day_week=0;
			cw->current_week++;
		}
                
                dwlc++;

	}

	cw->current_day_week=0;
	cw->current_week=1;

	for(int i=0;i<42;i++){// fill all calendar fields

		cw->p_cal_grid[i]= dw_new();

		gtk_grid_attach (GTK_GRID (cw->self), cw->cal_grid[i]->self,cw->current_day_week, cw->current_week, 1, 1);

		//cal_grid[current_day_week + current_week*7]->date=day;

		//update_dw(cal_grid[current_day_week + current_week*7]);
	
		cw->current_day_week++;
	
		if(cw->current_day_week>6){
			cw->current_day_week=0;
			cw->current_week++;
		}		
	}



	cw->current_day_week=0;
	cw->current_week=0;

	date_w* fdm= get_month_begin(date);

	cw->currentMonthNumber=fdm->month;
	cw->currentDayMonthNumber=get_current_day()->day;
	

	int pm_day_count= getWeekDay(*fdm);

	if(FIRST_WEEK_DAY == 1){

		pm_day_count--;
		if(pm_day_count<0){

			pm_day_count = 7+pm_day_count;
		}
		
	}
	
	// pm_day_count - number of the days from previous month for display into calendar

	date_w* pmld = date_w_add_days( get_month_end (date_w_add_days(fdm,-2)),0-(pm_day_count -1) ); // previous month last day for displaing
	



	for(int i=0;i<pm_day_count;i++){// fill with previous month days

		insert_day( date_w_add_days (pmld,i ),cw);

	}

	
	int cm_count=getMonthDaysNumber(*fdm);

	for(int i=0;i<cm_count;i++){ // fill with current month days

		insert_day (date_w_add_days (fdm,i ),cw);
	}


	date_w* nmd=date_w_add_days (fdm,cm_count );

	int nm_count=42 -(cm_count+pm_day_count);


	for(int i=0;i<nm_count;i++){ // fill with next month days

		insert_day (date_w_add_days (nmd,i ),cw);
	}
	


	return cw;
	
}





void refill_calendar(calendar_w* cw,date_w* fdm){



	cw->currentMonthNumber=fdm->month;
	cw->currentDayMonthNumber=get_current_day()->day;

	cw->current_day_week=0;
	cw->current_week=0;
	

	int pm_day_count= getWeekDay(*fdm);

	if(FIRST_WEEK_DAY == 1){

		pm_day_count--;
		if(pm_day_count<0){

			pm_day_count = 7+pm_day_count;
		}
		
	}
	
	// pm_day_count - number of the days from previous month for display into calendar

	date_w* pmld = date_w_add_days( get_month_end (date_w_add_days(fdm,-2)),0-(pm_day_count -1) ); // previous month last day for displaing
	



	for(int i=0;i<pm_day_count;i++){// fill with previous month days

		update_day( date_w_add_days (pmld,i ),cw);

	}

	
	int cm_count=getMonthDaysNumber(*fdm);

	for(int i=0;i<cm_count;i++){ // fill with current month days

		update_day (date_w_add_days (fdm,i ),cw);
	}


	date_w* nmd=date_w_add_days (fdm,cm_count );

	int nm_count=42 -(cm_count+pm_day_count);


	for(int i=0;i<nm_count;i++){ // fill with next month days

		update_day (date_w_add_days (nmd,i ),cw);
	}


}



void change_date(int type){ // type=0 inc month; type=1 dec month; type=2 inc year; type=3 dec year

	switch(type){

		case 0:

			GLOBAL_CALENDAR_PTR->changer->current_date->month++;

			if(GLOBAL_CALENDAR_PTR->changer->current_date->month == 13){
				GLOBAL_CALENDAR_PTR->changer->current_date->month=1;
				GLOBAL_CALENDAR_PTR->changer->current_date->year++;
				
			}


			date_changer_update(GLOBAL_CALENDAR_PTR->changer);
			break;

		case 1:

			GLOBAL_CALENDAR_PTR->changer->current_date->month--;

			if(GLOBAL_CALENDAR_PTR->changer->current_date->month == 0){
				GLOBAL_CALENDAR_PTR->changer->current_date->month=12;
				GLOBAL_CALENDAR_PTR->changer->current_date->year--;
			}


			date_changer_update(GLOBAL_CALENDAR_PTR->changer);			

			break;
			
		case 2:

			GLOBAL_CALENDAR_PTR->changer->current_date->year++;


			date_changer_update(GLOBAL_CALENDAR_PTR->changer);

			break;

		case 3:

			GLOBAL_CALENDAR_PTR->changer->current_date->year--;


			date_changer_update(GLOBAL_CALENDAR_PTR->changer);
			break;			
	}

	refill_calendar (GLOBAL_CALENDAR_PTR,GLOBAL_CALENDAR_PTR->changer->current_date);
	
/*	struct timespec ts;
    ts.tv_sec = 200 / 1000;
    ts.tv_nsec = (200 % 1000) * 1000000;
    nanosleep(&ts, NULL);*/
	

}






