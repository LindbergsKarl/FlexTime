/*
 ============================================================================
 Name        : Flextime.c
 Author      : Karl Lindberg
 Description : Lab Flextime Xtras
 ============================================================================
 */
#include "Flex.h"

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	Timestampe Allstamps[DAY][STAMPE];
	argv++;
	char input, array[MAX_STRING];
	char *ptr_array=array;
	char *ptr_input=&input;

	*ptr_array = input_filter_raw_data(*ptr_input, ptr_array, argv);

	Employee person=Person_func(*argv);

	ptr_array=array;
	int y=0; int t=0;
	for(int a=0; a<DAY; a++){
		for(int i=0; i<STAMPE; i++, y++){
			Allstamps[t][y]= input_to_struct(ptr_array);
			ptr_array=(ptr_array+DAY);
		}
		t++; y=0;
	}

	Output weeks[WEEKS];
	int a=0; int x=0;
	for(int i=0; i<WEEKS; i++, a++){
		weeks[a]=week_output(x, Allstamps);
		x=x+SIZE_DAY+1;
	}

	Output *ptrWeeks=weeks;

	print_old_file(&person);

	printout(&person, ptrWeeks);

	return 0;
}
