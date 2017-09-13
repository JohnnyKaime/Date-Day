/*
*Operating System - Prac 1
*
*Includes the system library below for uses in our program
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
/*
*Below are headers of our function
*/
int dayofweek(char *month, int day, int year);
int getOddDaysEachMonth(int month);
int getMonth(char *month);
char *getDays(int month);
void check();
void invalidInput();
/*
*Description:
*This algorithm uses "odd days" to determine the day of an given date
*User must input 3 arguments, month (first 3 letters, must be capitalised), day
*(numeric form) and year (numeric form)

*References: 
*http://www.geeksforgeeks.org/placements-qa-calendar/
*https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
*
*Below are rules from the reference source I used:
*Odd days are the days more than complete number of weeks, aka reminders
*Number of odd days in a non-leap year = 1
*Number of odd days in a leap year = 2
*Number of odd days in 100 years = 5
*Number of odd days in 200 year = 3
*Number of odd days in 300 years = 1
*Number of odd days in 400 years = 0
*Non – centennial year is a leap year, if we divide by 4 and get no remainder
*then its a leap year
*Centennial year is a leap year, if we divide by 400 and get no remainder then
*its a leap year
*
*Number of odd days = 0, Day = Sunday
*Number of odd days = 1, Day = Monday
*Number of odd days = 2, Day = Tuesday
*Number of odd days = 3, Day = Wednesday
*Number of odd days = 4, Day = Thursday
*Number of odd days = 5, Day = Friday
*Number of odd days = 6, Day = Saturday
*
*Input: Takes in 3 parameters
*char, month - The month of the input, 1st input from argv
*int, day - The day of the input, 2nd input from argv
*int year - The year of the input, 3rd input from argv
*
*Output: Returns integer
*Uses the formula to caculate the odd days, using the 2nd set of rules
*
*Caveats: Nothing
*/
int dayofweek(char *month, int day, int year){
    /*
    *getMonth returns the numeric (integer) form of the input month
    *To the corresponding index in the month array
    */
    int newMonth = getMonth(month);
    int normalMonth = newMonth + 1;
    year -= normalMonth < 3;
    /*
    *Uses the above rules to compute the amount of odd days given by the date
    */
    return ((year + year / 4 - year / 100 + year / 400 + getOddDaysEachMonth(newMonth) + day) % 7);
}
/*
*Description:
*Returns the odd days each month as integer value
*
*Input: Takes in one parameter
*int, month - The month of the input, which was converted into numeric form
*
*Output: Returns integer
*Uses the rules, the odd days in each month and returns it as an integer
*We converted the month to its numeric form and to the corresponding index
*position of our oddDayEachMonth array, hence we can directly return 
*the number of odd days
*
*Caveats: Nothing
*/
int getOddDaysEachMonth(int month){
    static int oddDaysEachMonth[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    return oddDaysEachMonth[month];
}
/*
*Description:
*Returns the index position, of the month in numeric form
*Starting from 0
*
*Input: Takes in one parameter
*Month of the given date in char
*
*Output: Return integer
*Returns the index position, of the month in numeric form
*
*Caveats: Nothing
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
*Description:
*Returns the final day given the the remaining odd days after computation
*
*Input: Take in one parameter
*Odd days after computation as an integer
*
*Output: Return char
*Returns a char that contains the day to the corresponding date
*
*Caveats: Nothing
*/
char *getDays(int day){
    static char *dayArray[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    return dayArray[day];
}
/*
*Description:
*Checks if the user inputs are valid
*	entered 3 parts in the format of "month, day, year"
*Checks if each month is given in the correct form
*	3 letter abbrevaition, captialized, alphabet
*Checks if each day is given in the correct form
*	numeric with in the range of each month, such as leap year maximum of day can be up to 29, otherwise only 28
*Checks if each year is given in the correct form
*	numeric
*If any of the condition are not met, then it displays "Invalid Input"
*Then terminates the program
*
*Input: Takes in 3 parameters
*int size - The amount of input parameters, seperate by spaces, in integer form
*char t1[] - The char array that contains the users input, expected format month
*char t2[] - The char array that contains the users input, expected format day
*char t2[] - The char array that contains the users input, expected format year
*
*Output: Nothing
*If theres any mismatch invalidInput() function is called
*"Invalid input" message is displayed then program is terminated
*
*Caveats: Nothing
*/
void check(int size, char t1[],char t2[],char t3[]){
    /*
    *Checks if 3 parameters are inputted, from argv[]
    *Display "Input invalid" message and terminates if its not 3
    */
    if(size != 4){
        invalidInput();
    }
    /*
    *Creates two arrays monthArray and dayArray
    *monthArray contains the months used to compare with user input
    *dayArray contains the day used to compare with user input
    *
    *Create new char pointers to the user input
    */
    static char *monthArray[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    static int dayArray[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    char *month = t1;
    char *day = t2;
    char *year = t3;
    /*
    *Checks input, year, if its numeric
    *Gets the len of each string for year and month
    *Uses a for loops to go through and check if each digit is numeric
    *If it fails
    *    Display "Input invalid" message and terminates
    */
    int yearlen = strlen(year);
    int daylen = strlen(day);
    int pos1, pos2;
    //*Loops through year to check if each digit is numeric
    for(pos1 = 0; pos1 < yearlen; pos1++){
        if(!isdigit(year[pos1])){
            invalidInput();
        }
    }
    //*Loops through year to check if each digit is numeric
    for(pos2 = 0; pos2 < daylen; pos2++){
        if(!isdigit(day[pos2])){
            invalidInput();
        }
    }
    /*
    *Check input, month, if its one of the 12
    *Remembers the index of the correct month in the monthArray
    *If the month is not found
    *	flag remains false (0)
    */
    int count;
    int flag = 0;
    int index = 0;
    for (count = 0; count < 12; count++){
        if(strcmp(monthArray[count],month) == 0){
            //*Sets flag to true
            flag = 1;
            //*Remain index position of month
	        index = count;
        }
    }
    /*
    *If month is not within the monthArray
    *So its not any of the 12 or input is not the valid format
    *Then display "Invalid input" and terminates
    */
    if(flag == 0){
        invalidInput();
    }

    /*
    *Checks leap year
    *And if Feb has the correct days if its a leap year
    *
    *Checks if the day is within the range
    *Must be less than the maximum day in the dayArray and greater than 0
    */
    //*End point that is "NULL" use for strtol
    char *end;
    //*Converts char into int, converts "day" till the end point "end" into base 10
    int dayNum = strtol(day,&end,10);
    //*Converts char into int, converts "year" till the end point "end" into base 10
    int yearNum = strtol(year, &end, 10);
    
    /*
    *Checks if year is a loop year by the following rules:
    *1. If the year is evenly divisible by 4, go to step 2. Otherwise, go to step 5.
    *2. If the year is evenly divisible by 100, go to  step 3. Otherwise, go to step 4.
    *3. If the year is evenly divisible by 400, go to step 4. Otherwise, go to step 5.
    *4. The year is a leap year (it has 366 day1s).
    *5. The year is not a leap year (it has 365 days).
    *
    *Reference:
    *https://support.microsoft.com/en-us/help/214019/method-to-determine-whether-a-year-is-a-leap-year
    */
    //*Checks if year is divisible by 4
    if(yearNum % 4 == 0){
       	//*Checks if year is divisible by 100
    	if(yearNum % 100 == 0){
    		//*Checks if year is divisibly by 400
    		if(yearNum % 400 == 0){
    			//*Checks if the month is feb and days is 29 and above
    			if(dayNum > 29 && (strcmp(month,"Feb")==0)){
                    		invalidInput();
                }
    		}else{ 
    			//*Checks if month is feb and days is 28 and above
    			if(dayNum > 28 && (strcmp(month,"Feb")==0)){
                    		invalidInput();
                }
    		}
        }else{ 
            //*Checks if month is feb and days is 28 and above
            if(dayNum > 29 && (strcmp(month,"Feb")==0)){
                invalidInput();
            }
        }
	}
    //*The below is checking a normal year, hence not a leap year
    //*Checks if month is feb and days is 28 and above
    else if(dayNum > 28 && (strcmp(month,"Feb") == 0)){
        invalidInput();
    }
    //*All the other months besides Feb
    //*Checking it must be in the range of 1 ~ dayArray[index]
    //*Maximum valid range for each month
    if((dayNum > dayArray[index] || dayNum < 1) && (strcmp(month,"Feb") != 0)){
        invalidInput();
    }
}
/*
*Description:
*Prints out "Input not valid"
*Then terminates the program
*
*Input: Nothing
*
*Output: Nothing
*
*Caveats: Nothing
*/
void invalidInput(){
    fprintf(stderr,"Input not valid\n");
    //*Terminate program
    exit(1);
}
/*
*Description:
*This program calculates the day of any given date using an algorithm
*Users must input a date in the following format
*MMM DD YYYY
*MMM - Month of the year, captialized and first 3 letters
*DD - Day of the month, in numeric form
*YYYY - Year of the given date, in numeric form
*The result prints out a char array (string) of that corresponding day
*
*Input: Takes in 2 parameters
*int argc - The total amount of input from the users, seperated by spaces
*char argv - A line of input in char array form, seperated by spaces
*
*Output: Prints out the day
*char day - Prints out the day after calculating it from the inputted date
*in DDD format, capitalized
*
*Caveats: Nothing
*/
int main(int argc, char *argv[]){
    /*
    *Passing the arguments as parameters
    */
    char *str1 = argv[1];
    char *str2 = argv[2];
    char *str3 = argv[3];
    //*End point that is "NULL" use for strtol
    char *end;
    check(argc,str1, str2, str3);
    int num2 = strtol(str2,&end,10);
    int num3 = strtol(str3,&end,10);
    //*Calling main function dayofweek, this returns an integer from 0 ~ 6
    //*The above result is then inputted to getDays that returns an string
    //*That contains the corresponding day
    char *day = getDays(dayofweek(str1,num2,num3));
    printf("%s",day);
    return 0;
}
