#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Personnummer.h"

// to check if date is valid
int normal_year[] = {
		LONGMONTH,SHORTFEB,LONGMONTH,SHORTMONTH,
		LONGMONTH,SHORTMONTH,LONGMONTH,LONGMONTH,
		SHORTMONTH,LONGMONTH,SHORTMONTH,LONGMONTH
};
int leap_year[] = {
		LONGMONTH,LONGFEB,LONGMONTH,SHORTMONTH,
		LONGMONTH,SHORTMONTH,LONGMONTH,LONGMONTH,
		SHORTMONTH,LONGMONTH,SHORTMONTH,LONGMONTH
};

/*
 * Input control. Only allow XXXXXXXXXX or XXXXXX-XXXX
 * Output: a char pointer points input array
 * Invalid case 1: too short or too long input
 * Invalid case 2: invalid characters(letters symbols)
 */
char* receive_input(){
	char *inputstr;
	if((inputstr = (char *)malloc(sizeof(char)*INPUTLENGTH))==NULL){
		printf("Memory not enough!");
	}
	char input;
	int i=0;
	_Bool formatcheck=false;//
	printf("Enter the personal number to check if valid (YYMMDDXXXX or YYMMDD-XXXX):\n");
	while(!formatcheck){
		input = getchar();
		// input can be 1) digit. valid 2) other characters, not valid, reset input and buffer
		// 3) Enter. finish 4) '-' in 6th place, valid
		if(isdigit(input)){
			inputstr[i++] = input;
		}
		// if slash in 6th place, accept and ignore
		else if(input=='-'&&i==SLASHPOS){
			// do nothing
		}
		// only way to go out of the format check loop is to get 10 digits
		else if(input=='\n'){
			if(i==INPUTLENGTH-1){
				inputstr[++i] = '\0';
				formatcheck = true;
			}
			else{
				// invalid case: too short or too long
				char error[ERRORMSG];
				i>INPUTLENGTH-1?strcpy(error,"long"):strcpy(error,"short");
				printf("Input is too %s.\n",error);
				i = reset();
			}
		}
		// invalid case: invalid characters
		else{
			printf("Input includes invalid character.\n");
			i = reset();
		}
	}
	return inputstr;
}

/*
 * convert input to struct
 * Input: char pointer
 * Output: a defined struct Personno
 */
Personno chartostruct(char* somepnt){
	char *help = somepnt;
	Personno Person;
	for(int i=0;i<YMDLENGTH;i++,help++){
		Person.year[i]=*help;
	}
	Person.year[YMDLENGTH]='\0';
	for(int i=0;i<YMDLENGTH;i++,help++){
		Person.month[i]=*help;
	}
	Person.month[YMDLENGTH]='\0';
	for(int i=0;i<YMDLENGTH;i++,help++){
		Person.day[i]=*help;
	}
	Person.day[YMDLENGTH]='\0';
	for(int i=0;i<XXXLENGTH;i++,help++){
		Person.xxx[i]=*help;
	}
	Person.xxx[XXXLENGTH]='\0';
	Person.ctrdigit=*help-ZEROASCII;
	return Person;
}

/*
 * To check the date in struct Personno a valid date
 * including leap year check
 */
_Bool rangecheck(Personno someperson){
	_Bool range_check = false;
	int yyint=atoi(someperson.year);
	int mmint=atoi(someperson.month);
	int ddint=atoi(someperson.day);
	if(mmint>0&&mmint<MONTHLIMIT){
		if(leapyear(yyint)){
			if(ddint<=leap_year[mmint-1]){
				range_check = true;
			}
		}
		else{
			if(ddint<=normal_year[mmint-1]){
				range_check = true;
			}
		}
	}
	if(!range_check) printf("The input date is out of range.\n");
	return range_check;
}

/*
 * return true if input year is a leap year otherwise return false
 */
_Bool leapyear(int year){
	_Bool flag=false;
	if(year%LEAPYR4==0){
		flag = true;
	}
	if(year%LEAPYR100==0&&year%LEAPYR400!=0){
		flag = false;
	}
	return flag;
}

// calculate ctr ctrdigit.
int cal_ctrdigit(char *somepnt){
	int multiarray[]=MULTIARRAY;
	int sum=0,mid=0,plus=0;
	char *help=somepnt;
	for(int i=0;i<INPUTLENGTH;i++,help++){
		mid = (*help-ZEROASCII)*multiarray[i];
		if(mid>=MOD)plus=1;
		else plus=0;
		sum += mid%MOD+plus;
	}
	if(sum%MOD==0){
		return 0;
	}
	else{
		return MOD-sum%MOD;
	}
}
// print input date, limit age 0-99.
// Dates equal to or earlier than today should be 21st century.
// Dates later than today should be 20th century.
void print_date(Personno someperson){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int today_yr=tm.tm_year%100, today_mth=tm.tm_mon+1, today_day=tm.tm_mday;
	int century;
	if(atoi(someperson.year)<today_yr){
		century = today_yr;
	}
	else if(atoi(someperson.year)>today_yr){
		century = today_yr - 1;
	}
	else{
		if(atoi(someperson.month)<today_mth||(atoi(someperson.month)==today_mth&&atoi(someperson.day)<=today_day)){
			century = today_yr;
		}
		else{
			century = today_yr-1;
		}
	}
	printf("Date of birth %d%s-%s-%s ",century,someperson.year,someperson.month,someperson.day);

}
void print_ctrdigit_result(Personno someperson,int result){
	if(someperson.ctrdigit==result){
		printf("OK!\n");
	}
	else{
		printf("NOT OK!\n");
	}
}
/*
 * The function will reset buffer and counter to 0 for next input
 */
int reset(){
	fflush(stdin);
	printf("Enter the personal number to check if valid (YYMMDDXXXX or YYMMDD-XXXX):\n");
	return 0;
}
