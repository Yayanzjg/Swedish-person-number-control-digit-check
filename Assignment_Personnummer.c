#include <stdio.h>
#include <stdlib.h>
#include "Personnummer.h"

int main(void) {
	setbuf(stdout,NULL);
	Personno Person;
	char *input;

	//Input control. Guarantee the input date is valid date
	do{
	input = receive_input();
	Person = chartostruct(input);
	}while(!rangecheck(Person));

	//print the birth date and calculate if the input has the correct control digit
	print_date(Person);
	print_ctrdigit_result(Person,cal_ctrdigit(input));
	return 0;
}
