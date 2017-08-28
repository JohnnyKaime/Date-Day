#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int dayofweek(char *month, int day, int year);
int getOddDaysEachMonth(int month);
int getMonth(char *month);
char *getDays(int month);
bool check(int size, char *input);


int dayofweek(char *month, int day, int year){
	int newMonth = getMonth(month);
	int normalMonth = newMonth + 1;
	year -= normalMonth < 3;
	return ((year + year / 4 - year / 100 + year / 400 + getOddDaysEachMonth(newMonth) + day) % 7);
}

int getOddDaysEachMonth(int month){
	static int oddDaysEachMonth[] = {0,3,2,5,0,3,5,1,4,6,2,4};
	return oddDaysEachMonth[month];
}

int getMonth(char *month){
	static char *monthArray[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	int count;
	for(count = 0; count < 12; count++)
		if(strcmp(month,monthArray[count]) == 0){
			return count;
		}
}

char *getDays(int month){
	static char *dayArray[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	return dayArray[month];
}

bool check(int size, char *input[]){
	if(size != 4){
		invalidInput();
	}
	static char *monthArray[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	static int dayArray[] = {31,28,31,30,31,30,31,30,31,30,31,30};

	char *month = input[1];
	char *day = input[2];
	char *year = input[3];

	if(!isdigit(year)){
		invalidInput();
	}

	int count;
	for (count = 0; count < 12; count++){
		if(strcmp(monthArray[count],month)){
			
		}
	}


}

void invalidInput(){
	printf("Input not valid")
	exit(1);
}

int main(int argc, char *argv[]){

	check(size, argv);
	//char *day = getDays(dayofweek("Mar",31,2010));
	//printf("%s",day);
	return 0;
}
