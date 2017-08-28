#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int dayofweek(char *month, int day, int year);
int getOddDaysEachMonth(int month);
int getMonth(char *month);
char *getDays(int month);
void check();
void invalidInput();
void parse_cmdline(int argc, char *argv[]);


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

void check(int size, char t1[],char t2[],char t3[]){
    if(size != 4){
    printf("%d\n",size);
        invalidInput();
    }
    static char *monthArray[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    static int dayArray[] = {31,28,31,30,31,30,31,30,31,30,31,30};
    char *month = t1;
    char *day = t2;
    char *year = t3;

    //Checks input if its numeric
    if(!isdigit(year[0]) || !isdigit(day[0])){
        invalidInput();
    }
    //Checks the month
    int count;
    int flag = 0;
    int index = -1;
    for (count = 0; count < 12; count++){
        if(strcmp(monthArray[count],month) == 0){
                flag = 1;
        index = count;
        }
    }

    if(flag == -1){
        invalidInput();
    }
    //Checks the days
    int dayNum;
    char *end;
    dayNum = strtol(day,&end,10);
    if(dayNum > dayArray[index] || dayNum < 1){
        invalidInput();
    }
    //Check leap year
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

void invalidInput(){
    printf("Input not valid\n");
    exit(1);
}

int main(int argc, char *argv[]){
    //check(3,"Feb","28","2010");
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
