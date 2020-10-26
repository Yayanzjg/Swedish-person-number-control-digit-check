#ifndef PERSONNUMMER_H_
#define PERSONNUMMER_H_

#define INPUTLENGTH 11
#define SLASHPOS 6
#define ERRORMSG 5
#define MONTHLIMIT 13
#define YMDLENGTH 2
#define XXXLENGTH 3
#define CTRLENGTH 1
#define ZEROASCII 48
#define MULTIARRAY {2,1,2,1,2,1,2,1,2,0} // for control digit calculation
#define MOD 10
#define LEAPYR4 4 // for leap year check
#define LEAPYR100 100
#define LEAPYR400 400
#define LONGMONTH 31 // days for a long month
#define SHORTMONTH 30 // days for a short month
#define LONGFEB 29 // days for February in a leap year
#define SHORTFEB 28 // days for February in a normal year

typedef struct{
	char year[YMDLENGTH+1];
	char month[YMDLENGTH+1];
	char day[YMDLENGTH+1];
	char xxx[XXXLENGTH+1];
	int ctrdigit;
}Personno;
/*
 * Input control. Only allow XXXXXXXXXX or XXXXXX-XXXX at the 6th position
 * Output: a char pointer points input array
 * Invalid case 1: too short or too long input
 * Invalid case 2: invalid characters(letters symbols)
 */
char* receive_input();

/*
 * convert input to struct
 * Input: char pointer
 * Output: a defined struct Personno
 */
Personno chartostruct(char* somepnt);

/*
 * To check the date in struct Personno a valid date
 * including leap year check
 */
_Bool rangecheck(Personno someperson);

/*
 * return true if input year is a leap year otherwise return false
 */
_Bool leapyear(int year);

/*
 * Input: a char pointer points an array
 * Output: calculate the control digit according to Swedeish personal number rule
 */
int cal_ctrdigit(char* somepnt);

/*
 * print OK if control digit of entered person number is the same as the calculated result
 * print NOT OK if mismatch
 */
void print_ctrdigit_result(Personno someperson, int result);

/*
 * print date of birth according to the entered personal number
 * the age is limited between 0-99 taking TODAY as the reference day
 */
void print_date(Personno someperson);

/*
 * The function will reset buffer and counter to 0 for next input
 */
int reset();
#endif /* PERSONNUMMER_H_ */
