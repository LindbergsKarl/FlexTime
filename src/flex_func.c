/*
 * 	flex_func.c
 *
 *  Created on: 24 nov. 2020
 *  Author: Karl Lindberg
 */
#include "Flex.h"

char input_filter_raw_data(char input, char array[MAX_STRING], char *argv[]) {
	char two_stampes[]={'0','0','0',',','0','0',',','0','0',';'};
	char comp_day[]={'0','0','0',',','0','7',',','3','0',';','0','0','0',',','1','2',',','3','0',';'
			,'0','0','0',',','1','3',',','3','0',';','0','0','0',',','1','6',',','3','0',';'};
	char *ptr_array=array;
	FILE *fpnt;
	if ((fpnt = fopen(*argv, "r")) == NULL) {
		printf("\n Cannot read the file!");
		exit(1);
	}
	int k = 0;
	int new_line_count = 0;
	int stamp_count = 0;
	while (fread(&input, sizeof(char), 1, fpnt) == 1) {
		if (input == '\n') {
			new_line_count++;
		}
		if (new_line_count == 1 && stamp_count == STAMPE) {
			stamp_count = 0;
			new_line_count = 0;
		}
		if (new_line_count == 1 && stamp_count == WEEKS) {
			stamp_count = 0;
			for(int i=0; i<TWO_STAMPS; i++){
				array[k]=two_stampes[i];
				k++;
			}
			stamp_count = 0;
			new_line_count = 0;
		}
		if (new_line_count == 1 && stamp_count == 0) {
			stamp_count = 0;
			for(int i=0; i<STAMPS; i++){
				array[k]=comp_day[i];
				k++;
			}
			stamp_count = 0;
			new_line_count = 0;
		}
		if (input == ';') {
			stamp_count++;
		}
		if (!(input == '\n')) {
			array[k++] = input;
		}
	}
	fclose(fpnt);
	return *ptr_array;
}


Timestampe input_to_struct(char array[]){
	char *ptr_array=array;
	Timestampe Temp;

	char tempcharDay[SIZE_DAY];
	char *ptrTempcahrDay=tempcharDay;
	for(ptrTempcahrDay=tempcharDay; ptrTempcahrDay<tempcharDay+SIZE_DAY-1; ptr_array++){
		*ptrTempcahrDay= *ptr_array ;
		ptrTempcahrDay++;
	}
	*ptrTempcahrDay='\0';
	ptr_array++;

	char tempcharHour[SIZE_TIME];
	char *ptrTempcahrHour=tempcharHour;
	for(ptrTempcahrHour=tempcharHour; ptrTempcahrHour<tempcharHour+SIZE_TIME-1; ptr_array++){
		*ptrTempcahrHour= *ptr_array ;
		ptrTempcahrHour++;
	}
	*ptrTempcahrDay='\0';
	ptr_array++;

	char tempcharMin[SIZE_TIME];
	char *ptrTempcahrMin=tempcharMin;
	for(ptrTempcahrMin=tempcharMin; ptrTempcahrMin<tempcharMin+SIZE_TIME-1; ptr_array++){
		*ptrTempcahrMin= *ptr_array ;
		ptrTempcahrMin++;
	}
	*ptrTempcahrMin='\0';

	int temp1=atoi(tempcharDay);
	int temp2=atoi(tempcharHour);
	int temp3=atoi(tempcharMin);

	Temp.daynr= temp1;
	Temp.hour= temp2;
	Temp.min= temp3;

	return Temp;
}

Output week_output(int x, Timestampe Allstamps[DAY][STAMPE]) {
	Output weeks;
	int a=0; int b=1; int c=SIZE_TIME-1; int d=SIZE_TIME;
	float *ptrWeek = &weeks.day1;
	float *ptrHour1 = &Allstamps[x][a].hour; float *ptrHour2 = &Allstamps[x][b].hour;
	float *ptrHour3 = &Allstamps[x][c].hour; float *ptrHour4 = &Allstamps[x][d].hour;
	float *ptrMin1 = &Allstamps[x][a].min; float *ptrMin2 = &Allstamps[x][b].min;
	float *ptrMin3 = &Allstamps[x][c].min; float *ptrMin4 = &Allstamps[x][d].min;
	weeks.week_total = 0;
	for (int a = 0; a < STAMPE+1; a++) {
		float temp1 = (*ptrHour2 - *ptrHour1)+ (*ptrHour4 - *ptrHour3);
		float temp2 = ((*ptrMin2 / MINUTES) - (*ptrMin1 / MINUTES))	+ ((*ptrMin4 / MINUTES) - (*ptrMin3 / MINUTES));
		float temp3 = temp1 + temp2;
		*ptrWeek = temp3;
		ptrHour1 = (ptrHour1 + DAT_JUMP); ptrHour2 = (ptrHour2 + DAT_JUMP);
		ptrHour3 = (ptrHour3 + DAT_JUMP); ptrHour4 = (ptrHour4 + DAT_JUMP);
		ptrMin1 = (ptrMin1 + DAT_JUMP); ptrMin2 = (ptrMin2 + DAT_JUMP);
		ptrMin3 = (ptrMin3 + DAT_JUMP); ptrMin4 = (ptrMin4 + DAT_JUMP);
		x++;
		ptrWeek++;
		weeks.week_total = weeks.week_total + temp3;
	}
	return weeks;
}

Employee Person_func(char *argv){
	Employee person;
	char name[SIZE_NAME], s[SIZE_SIGN]="_";
	char *ptrName=name;
	char *ptrPersonName=person.name;
	char *ptrPersonEmpno=person.empno;
	char *ptrPersonPeriod=person.period;

	while((*argv !='.')){
		*ptrName=*argv;
		ptrName++, argv++;
	}
	*ptrName='\0';

	ptrPersonName=strtok(name,s);
	ptrPersonEmpno=strtok(NULL,s);
	ptrPersonPeriod=strtok(NULL,s);

	FILE *fpnt;
	if( (fpnt=fopen("temp_char.txt","wt")) == NULL){
		printf("\n Cannot read the file!");
		exit(1);
	}
	fprintf(fpnt, "%s %s %s", ptrPersonName,ptrPersonEmpno,ptrPersonPeriod);
	fclose(fpnt);
	fpnt=fopen("temp_char.txt", "r");
	fscanf(fpnt,"%s %s %s",person.name,person.empno,person.period);
	fclose(fpnt);
	remove("temp_char.txt");

	return person;
}

void print_old_file(const Employee *person){

	FILE *fpnt;
	char last_period_file[SIZE_NAME];
	int temp=atoi(person->period);
	int last_period=temp-WEEKS;
	sprintf(last_period_file,"%s_%s_%d.dat",person->name,person->empno,last_period);
	printf("\n **************************************************");
	printf("\n Last period: %d",last_period);

	_Bool error_flag=false;
	if((fpnt=fopen(last_period_file,"rb"))==NULL){
		printf("\nCannot find a earlier file for %s!", person->name);
		error_flag=true;
	}
	if(error_flag==false){
		int k=0;
		float num=0;
		float tempfloat[SIZE_NAME];
		while( fread(&num, sizeof(float), 1, fpnt)==1){
			tempfloat[k++]=num;
		}
		fclose(fpnt);

		printf("\n");
		for(int n=0; n<k; n++){
			printf(" %.2f", tempfloat[n]);
		}
	}
	printf("\n **************************************************");
}
void printout(const Employee *person, Output weeks[WEEKS]) {
	FILE *fpnt;
	int a=0; int b=1;
	float periodtime = weeks[a].week_total + weeks[b].week_total;
	float difftime = periodtime - NORMAL_WORK_WEEK;
	char stringname[SIZE_NAME];
	sprintf(stringname,"%s_%s_%s.dat",person->name,person->empno,person->period);

	if( (fpnt=fopen(stringname,"wb")) == NULL){
		printf("\n Cannot read the file!");
		exit(1);
	}
	fwrite(&weeks[a].day1, sizeof(weeks[a].day1),1, fpnt); 	fwrite(&weeks[a].day2, sizeof(weeks[a].day2),1, fpnt);
	fwrite(&weeks[a].day3, sizeof(weeks[a].day3),1, fpnt); 	fwrite(&weeks[a].day4, sizeof(weeks[a].day4),1, fpnt);
	fwrite(&weeks[a].day5, sizeof(weeks[a].day5),1, fpnt); 	fwrite(&weeks[b].day1, sizeof(weeks[b].day1),1, fpnt);
	fwrite(&weeks[b].day2, sizeof(weeks[b].day2),1, fpnt); 	fwrite(&weeks[b].day3, sizeof(weeks[b].day3),1, fpnt);
	fwrite(&weeks[b].day4, sizeof(weeks[b].day4),1, fpnt); 	fwrite(&weeks[b].day5, sizeof(weeks[b].day5),1, fpnt);
	fclose(fpnt);

	printf("\n\nName:%s \t\tEmployee no:%s \tPeriod:%s",person->name,person->empno,person->period);
	printf("\n\n Overview     Day1    Day2    Day3    Day4    Day5");
	printf("\n Week 1       %.2f    %.2f    %.2f    %.2f    %.2f",
			weeks[a].day1, weeks[a].day2, weeks[a].day3, weeks[a].day4, weeks[a].day5);
	printf("\n Week 2       %.2f    %.2f    %.2f    %.2f    %.2f",
			weeks[b].day1, weeks[b].day2, weeks[b].day3, weeks[b].day4, weeks[b].day5);
	printf("\n\n Period time: %.2f (%.2f)", periodtime, difftime);

	fclose(fpnt);
}
