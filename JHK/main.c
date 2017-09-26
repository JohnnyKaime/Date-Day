/*************************************************************
*Jia-Cong Hou
*3565155
*Prac3 - Linkedlist using pointer - pointer
*File - main.c
*
*Driver or main.c file that gets the file input and loops until
*end of file, it then analyses each command and checks if it in
*the specificied format.
*	If not it calls input invalid in error.c linked by error.h
*
*Command include the following:
*	InsertBefore A B - Adds B before A
*	InsertAfter A B - Add B after A
*	Rush A - Adds a node in the front of the list
*	Remove A - Removes a specific node
*	Append A - Adds a node to the back of the list
*	These below have user output
*		Head - Prints out first node
*		Tail - Prints out last node
*		PrintList - Prints out whole list wiht "-" between each node
*		Length - Prints out size of the list
*************************************************************/
/*Includes user defined files*/
#include "linkedlist.h"
#include "error.h"
/*
*Description: main
*Gets the file name and use fopen to read file
*Loops until end of file
*	checks each line by taking the command (1st part) by usnig string token
*	if its either Push or Remove
*		then checks the data (2nd part) by using string token
*		uses it to call Push or Remove
*	else if its InsertBefore or InsertAfter
*		checks the data (3rd part) by using string token again
*	uses it to call InsertBefore or InsertAfter
*	else it should be the other commands
*		Remove
*		Head
*		Tail
*		PrintList
*		Length
*		These function return output
*	but if it's neither of this specificed commands
*		invalidInput function is called
*
*Input:
*argc - type int, total amout of input in the command line
*argcv - type char array, arg[1] should be file name to be read in
*
*Output:
*Nothing
*
*Caveats:
*Only accepts file names
*All data must be single, in range of A ~ Z
*Memory might run out
*/
int main(int argc, char * argv[]){
	/*Takes in file name*/
	char const * const fileName = argv[1];
	/*Reads the file*/
	FILE * file = fopen(fileName,"r");
	/*Create a large line, type char array to store each line of the file aka buffer*/
	char line[256];
	/*Loop until end of file*/
	while(fgets(line,sizeof(line),file)){
		/*Replace all new lines with NULL or 0*/
		/*This is not equal to '0'*/
		line[strcspn(line,"\r\n")] = 0;
		/*Use string token to strip out everything before the " "*/
        /*This is the command part*/
		char * command = strtok(line," ");
		/*Checks if command is not NULL*/
		/*Hence must not be empty*/
		if(command != NULL){
			/*Checks if command is InsertAfter*/
			if(strcmp(command, "InsertAfter") == 0){
				/*Use string token to strip 2nd part out everything after the " "*/
				char * dataA = strtok(NULL, " ");
				/*Use string token to strip 3rd part out everything after the " "*/
				char * dataB = strtok(NULL, " ");
				/*Calls the InsertAfter function*/
				/*While using Find to find the node before the matching case*/
				InsertAfter(Find(&HEAD,(*dataB)),(*dataA));
			/*Checks if command is InsertAfter*/
			}else if(strcmp(command, "InsertBefore") == 0){
				/*Use string token to strip 2nd part out everything after the " "*/
				char * dataA = strtok(NULL, " ");
				/*Use string token to strip 3rd part out everything after the " "*/
				char * dataB = strtok(NULL, " ");
				/*Calls the InsertBefore function*/
				/*While using Find to find the node before the matching case*/
				InsertBefore(Find(&HEAD,(*dataB)),(*dataA));
			/*Checks if command is equal to Push*/
			}else if(strcmp(command, "Push") == 0){
				/*Use string token to strip out everything after the " "*/
				char * data = strtok(NULL, " ");
				/*Calls Push function*/
				Push(&HEAD,(*data));
			/*Checks if command is equal to Append*/
			}else if(strcmp(command, "Append") == 0){
				/*Use string token to strip out everything after the " "*/
				char * data = strtok(NULL, " ");
				/*Calls Append function*/
				Append(&HEAD,(*data));
			/*Checks if command is equal to Remove*/
			}else if(strcmp(command, "Remove") == 0){
				/*Use string token to strip out everything after the " "*/
				char * data = strtok(NULL, " ");
				/*Calls Remove function*/
				Remove(&HEAD,(*data));
			/*Checks if command is equal to Head*/
			}else if(strcmp(command, "Head") == 0){
				/*Calls Head function*/
				Head();
			/*Checks if command is equal to Tail*/
			}else if(strcmp(command, "Tail") == 0){
				/*Calls Tail function*/
				Tail();
			/*Checks if command is equal to Length*/
			}else if(strcmp(command, "Length") == 0){
				/*Calls Length function*/
				Length();
			/*Checks if command is equal to Length*/
			}else if(strcmp(command, "PrintList") == 0){
				/*Calls PrintList function*/
				PrintList();
			}else{
				/*Command doesnt match any of the other*/
	            /*Calls invalidInput function*/
				InvalidInput();
			}
		}else{
			/*Command is empty*/
			/*Calls invalidInput function*/
			InvalidInput();
		}
	}
	/*Best practise to close file*/
	fclose(file);
	/*End of program terminate*/
	return 0;
}
