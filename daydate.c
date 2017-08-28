/*
Jia-Cong Hou
3565155
Operating System - Prac 1

Includes the system library below for uses in our program
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
/*
Below are headers of our function
*/
int dayofweek(char *month, int day, int year);
int getOddDaysEachMonth(int month);
int getMonth(char *month);
char *getDays(int month);
void check();
void invalidInput();
/*
This algorithm uses "odd days" to determine the day of an given date
User must input 3 arguments, month (first 3 letters, must be capitalised), day (numeric form) and year (numeric form)

References: 
http://www.geeksforgeeks.org/placements-qa-calendar/
https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week

Below are rules from the reference source I used:
Odd days are the days more than complete number of weeks, aka reminders
Number of odd days in a non-leap year = 1
Number of odd days in a leap year = 2
Number of odd days in 100 years = 5
Number of odd days in 200 year = 3
Number of odd days in 300 years = 1
Number of odd days in 400 years = 0
Non – centennial year is a leap year, if we divide by 4 and get no remainder then its a leap year
Centennial year is a leap year, if we divide by 400 and get no remainder then its a leap year

Number of odd days = 0, Day = Sunday
Number of odd days = 1, Day = Monday
Number of odd days = 2, Day = Tuesday
Number of odd days = 3, Day = Wednesday
Number of odd days = 4, Day = Thursday
Number of odd days = 5, Day = Friday
Number of odd days = 6, Day = Saturday
*/
int dayofweek(char *month, int day, int year){
	/*
	getMonth returns the numeric (integer) form of the input month
	To the corresponding index in the month array
	*/
    int newMonth = getMonth(month);
    int normalMonth = newMonth + 1;
    year -= normalMonth < 3;
    /*
	Uses the above rules to compute the amount of odd days given by the date
    */
    return ((year + year / 4 - year / 100 + year / 400 + getOddDaysEachMonth(newMonth) + day) % 7);
}
/*
Returns the odd days each month as integer value
*/
int getOddDaysEachMonth(int month){
    static int oddDaysEachMonth[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    return oddDaysEachMonth[month];
}
/*
Returns the index position, of the month in numeric form
Starting from 0
*/
int getMonth(char *month){
    static char *monthArray[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    int count;
    for(count = 0; count < 12; count++)
        if(strcmp(month,monthArray[count]) == 0){
            return count;
        }
}
/*
Returns the final day given the the remaining odd days after computation
*/
char *getDays(int day){
    static char *dayArray[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    return dayArray[day];
}
/*
Checks if the user inputs are valid
	entered 3 parts in the format of "month, day, year"
Checks if each month is given in the correct form
	3 letter abbrevaition, captialized, alphabet
Checks if each day is given in the correct form
	numeric with in the range of each month, such as leap year maximum of day can be up to 29, otherwise only 28
Checks if each year is given in the correct form
	numeric
If any of the condition are not met, then it displays "Invalid Input"
Then terminates the program
*/
void check(int size, char t1[],char t2[],char t3[]){
	/*
	Checks if 3 parameters are inputted
	*/
    if(size != 4){
        invalidInput();
    }
    /*
    Creates two arrays monthArray and dayArray
    monthArray contains the months used to compare with user input
    dayArray contains the day used to compare with user input

    Create new char pointers to the user input
    */
    static char *monthArray[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    static int dayArray[] = {31,28,31,30,31,30,31,30,31,30,31,30};
    char *month = t1;
    char *day = t2;
    char *year = t3;

    /*
    Checks input, year, if its numeric
    */
    if(!isdigit(year[0]) || !isdigit(day[0])){
        invalidInput();
    }
    /*
    Check input, month, if its one of the 12
    Remembers the index of the correct month in the monthArray
    */
    int count;
    int flag = 0;
    int index = -1;
    for (count = 0; count < 12; count++){
        if(strcmp(monthArray[count],month) == 0){
                flag = 1;
        index = count;
        }
    }
    /*
    If month is not within the monthArray
    So its not any of the 12 or input is not the valid format
    Then display "Invalid input" and terminates
    */
    if(flag == -1){
        invalidInput();
    }
    /*
    Checks if the day is within the range
    Must be less than the maximum day in the dayArray and greate than 1
    */
    int dayNum;
    char *end;
    dayNum = strtol(day,&end,10);
    if(dayNum > dayArray[index] || dayNum < 1){
        invalidInput();
    }
    /*
    Checks leap year
    And if Feb has the correct days if its a leap year
    */
    int yearNum = strtol(year, &end, 10);
    if(((yearNum % 400) == 0) && ((yearNum % 4) == 0) && ((yearNum % 100) != 0)){
        if(dayNum > 29 && strcmp(month,"Feb")){
            invalidInput();
        }
        else{
            invalidInput();
        }
    }
}
/*
Prints out "Input not valid"
Then terminates the program
*/
void invalidInput(){
    printf("Input not valid\n");
    exit(1);
}

int main(int argc, char *argv[]){
    /*
    Passing the arguments as parameters
    */
    char *str1 = argv[1];
    char *str2 = argv[2];
    char *str3 = argv[3];
    char *end;
    check(argc,str1, str2, str3);
    int num2 = strtol(str2,&end,10);
    int num3 = strtol(str3,&end,10);
    char *day = getDays(dayofweek(str1,num2,num3));
    printf("%s\n",day);
    return 0;
}
