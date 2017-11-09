/********************************************************************************************************
*Jia-Cong Hou
*3565155
*Prac4 - Deadlock
*File - main.c
*
*Driver or main.c file that gets the file input and loops until
*end of file, it then analyses each command and checks if it in
*the specificied format.
*   If not it calls input invalid in error.c linked by error.h
*
*Command include the following:
*   PRAC4
*   A Requests A - Adds resource A to processlist at position A
*   Clear - Reinitialize both resourcelist array and processlist array
*   Kill B - Deletes process C from both resourcelist and processlist
*   C Releases C -  Process C releasees resource C
*   DeadLockDectetion - Loops through resourcelist once to find any duplicates
*These are "help" functions that helps the above such as DeadLockDectetion
*   CycleDectetion - Allows maximum of 1 cycle before it terminates and calls deadLock in error.c
*   EndOfList - Finds if position given 
*   Finds - Returns position of resource or process in a array position say processlist[i]
*   FindsNext - Returns position of next available node to append to or check for cycle dectetion
*
*   PRAC3
*   InsertBefore A B - Adds B before A
*   InsertAfter A B - Add B after A
*   Rush A - Adds a node in the front of the list
*   Remove A - Removes a specific node
*   Append A - Adds a node to the back of the list
*   These below have user output
*       Head - Prints out first node
*       Tail - Prints out last node
*       PrintList - Prints out whole list wiht "-" between each node
*       Length - Prints out size of the list
*********************************************************************************************************/
/*Includes system defined files*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Includes user defined files*/
#include "node.h"
#include "functions.h"
#include "error.h"
/*Default structure type node*/
typedef struct node node;
/*
Creates two array
processlist, process array made of nodes
resroucelist, integer list to keep track of whats free and whos requesting it
*/
node * processlist[25] = {};
int resourcelist[25] = {};
/*
*Description: main
*Gets the file name and use fopen to read file
*Loops until end of file
*   checks each line by taking the 1st part by usnig string token
*   if its either a single length hence A ~ Z
*       then checks the command (2nd part) by using string token
*           Resource (3rd part) is also called
*           uses it to call Releases or Requests
*   else if its not a single length
*       checks the command (1rd part) by using string token again
*       checks if its Kill
*           if true then request Resource (3rd part)
*       uses it to call Kill or Clear
*   else
*       no other input is accepts
*       and if it's neither of this specificed commands
*           invalidInput function is called
*
*Input:
*argc - type int, total amout of input in the command line
*argcv - type char array, arg[1] should be file name to be read in
*
*Output:
*Returns Nothing
*Displays deadLock message or invalid input message accordingly
*
*Caveats:
*Only accepts file names
*All data must be single, in range of A ~ Z
*Memory might run out
*/
int main(int argc, char const *argv[])
{
    /*Takes in file name*/
	char const * const fileName = argv[1];
    /*Reads the file*/
	FILE * file = fopen(argv[1], "r");
    /*Create a large line, type char array to store each line of the file aka buffer*/
    char line[128];
    /*Loop until end of file*/
    while (fgets(line, sizeof(line), file)){
        //printf("%s\n", &argv[1][strlen(argv[1])-1]);
        /*Replace all new lines with NULL or 0*/
        /*This is not equal to '0'*/
    	line[strcspn(line,"\r\n")] = 0;
        /*Use string token to strip out everything before the " "*/
        /*This is the 1st part*/
    	char * part1 = strtok(line," ");
        /*Checks if 1st part is equal to kill*/
        if(strcmp(part1,"kill") == 0){
            /*Requests 2nd part*/
            /*Use string token to strip 2nd part out everything after the " "*/
            char * part2 = strtok(NULL," ");
            /*Checks if resource and proceess is in valid range*/
            if(*part2 < 65 || *part2 > 90){
                /*Doesnt satisfy specifications displays input invalid message*/
                InvalidInput();
            }else{
                /*Calls kill function giving processlist, part2(process), resourcelist*/
                /* *part2 gives it the address to use directly when called*/
                Kill(processlist, *part2, resourcelist);
                //printf("%s %s\n", part1, part2);
            }
        /*Checks if 1st part is equal to clear*/
        }else if(strcmp(part1,"clear") == 0){
            /*Calls clear function*/
            Clear(processlist, resourcelist);
            //printf("%s\n", part1);
        /*Checks if resource or proceess is in valid range*/
        }else if(*part1 > 64 && *part1 < 91){
            /*Use string token to strip 2nd part out everything after the " "*/
            char * part2 = strtok(NULL," ");
            /*Checks if command equals to Requests*/
            if(strcmp(part2,"requests") == 0){
                /*Use string token to strip 3nd part out everything after the " "*/
                /*Resource*/
                char * part3 = strtok(NULL," ");
                if(*part3 > 64 && *part3 < 91){
                    //requests
                    /*Convert resource into position (index in array) by subtracting ASCII value*/
                    int position = *part3 - 65;
                    /*Calls Request function*/
                    /*Throwing process, processlist and its position resources, resourcelist and its position of resources*/
                    if(Requests(&processlist[position], *part1, resourcelist[position])){
                        resourcelist[position]++;
                    }
                    //printf("%s %s %s\n", part1,part2,part3);
                }else{
                    /*Doesnt satisfy specifications displays input invalid message*/
                    InvalidInput();  
                }
            /*Use string token to strip 2nd part out everything after the " "*/
            /*Checks if command equals to releases*/
            }else if(strcmp(part2,"releases") == 0){
                /*Use string token to strip 3rd part out everything after the " "*/
                /*Resource*/
                char * part3 = strtok(NULL," ");
                if(*part3 > 64 && *part3 < 91){
                    //releases
                    /*Convert resource into position (index in array) by subtracting ASCII value*/
                    int position = *part3 - 65;
                    /*Calls Release function*/
                    /*Throwing process, processlist and its position resources, resourcelist and its position of resources*/
                    if(Releases(&processlist[position], *part1, resourcelist[position]) == 1){
                        resourcelist[position]--;
                    }
                    //printf("%s %s %s\n", part1,part2,part3);
                }else{
                    /*Doesnt satisfy specifications displays input invalid message*/
                    InvalidInput();  
                }
            }else{
                /*Doesnt satisfy specifications displays input invalid message*/
                InvalidInput();
            }
        }else{
            /*Doesnt satisfy specifications displays input invalid message*/
            InvalidInput();
        }
        //PrintList(processlist,*resourcelist);
        DeadLockDetection(processlist, resourcelist);
	}
    /*Close file after use*/
    fclose(file);
    checkbit(argv[1]);
	return 0;
}
