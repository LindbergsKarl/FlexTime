/*
 *  flex_func.c
 *
 *  Created on: 24 nov. 2020
 *  Author: Karl Lindberg
 */

#ifndef FLEX_H_
#define FLEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Flex.h"

#define MAX_STRING 400
#define DAY 10
#define WEEKS 2
#define STAMPE 4
#define SIZE_DAY 4
#define SIZE_TIME 3
#define DAT_JUMP 12
#define MINUTES 60
#define NORMAL_WORK_WEEK 80
#define WEEK 7
#define SIZE_SIGN 2
#define SIZE_NAME 30
#define SIZE_EMPNO 12
#define STAMPS 40
#define TWO_STAMPS 20

#define FILE_NAME *argv

typedef struct{
	int daynr;
	float hour;
	float min;
}Timestampe;

typedef struct{
	float day1;
	float day2;
	float day3;
	float day4;
	float day5;
	float week_total;
}Output;

typedef struct{
	char name[SIZE_NAME];
	char empno[SIZE_EMPNO];
	char period[WEEK];
}Employee;

char input_filter_raw_data(char input, char array[MAX_STRING], char *argv[]);
//Input_filter_raw_data reads the provided program argument from *argv.
//The function control if there is correct numbers of stamps before new line in file.
//If it's not correct the array will be filled with sick/flex data.
//Incoming to the function: ptr_input, ptr_array, argv
//char array[]  - the array that are being filled.
//char input[] - the data coming from stream while reading from file.
//int new_line_count - control if there is a new line in file.
//int stamp_cont - keep count how many stamps before new line.
//char two_stampes[] - Stores std values for two missing stamps.
//char comp_day[] - Stores std values for a hole day missing.
//array being returned to main.


Employee Person_func(char *argv);
//Person_func get the the name of the employee from the file name.
//char *argv coming in from main.
//Employee person - the struct are filled with name, empno and period.
//The info are used later for print out employee info.
//person being returned to main.


Timestampe input_to_struct(char array[]);
//Input_to_struct put the stamps from array[] into right place in Timestampe Allstamps[DAY][STAMPE].
//char array[] coming in from main.
//char tempcharDay[] - filled up with dayno.
//char tempcharHour[] - filled up with hour.
//char tempcharMin[] - filled up with min.
//Timestamp Temp - gets the data dayno, hour and min.
//Returns Temp to main. Repeated for every timestamp.


Output week_output(int x, Timestampe Allstamps[DAY][STAMPE]);
//Week_output calculate the total for every day and put it in Output week.
//Incoming Timestampe Allstamps[10][4] and int x.
//int x decides if week1 or week2 bing filled.
//Output weeks[2] - struct holding day1,day2,... week_total.
//weeks being returned to main.


void print_old_file(const Employee *person);
//Print_old_file check if there is any history data to print out of the employee.
//Employee person incoming from main holding info of the employee.
//char last_period_file[] - holding the name of the history file.
//int last_period - storing number of last period, this period number - 2 weeks.
//_Bool error_flag - set true if the there is any history file.
//float tempfloat[] - storing data from file.
//if file exists the data are printed out.


void printout(const Employee *person, Output weeks[WEEKS]);
//Printout print out the data from Output weeks, and save it as .dat file.
//incoming from main: Employee person and Output weeks.
//float periodtime - stores the total time from week 1 and 2.
//float difftime - stores the diff between a normal 80h work period and worked hours.
//char stringname[] - stores the filename that being stored as binary data.


#endif /* FLEX_H_ */
