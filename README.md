# Swedish social security number control
 AdvSWDev assignment
The control should focus on correct final digit according to the algorithm described below.
Use pointers when implementing this algorithm.
Algorithm for control digit:
* Multiply odd and even digits no 1-9 by 2 and 1 respectively
* Sum up all digits from the previous step. NB! 14 = 1+4.
* Calculate control digit as (10 – last digit of sum) % 10

Ex. PersonNr 7 1 0 6 2 5 4 7 8 7
multiply 14, 1, 0, 6, 4, 5, 8, 7, 16 -
sum up 1+4+1+0+6+4+ 5+ 8+ 7+1+6 = 43
control digit 10 - (4)3 = 7
Control digit equals last entered digit in PersonNr => OK!

Make sure that the first 6 digits represents a valid date of birth.
Limit the entries to cover persons of age 0 - 99 years.
