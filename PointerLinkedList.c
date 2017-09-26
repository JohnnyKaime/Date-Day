/*
*Linked list
*
*Includes the system library below for uses in our program
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
*Algorithm:
*This program reads a file say "test" and loops untill the end of it
*Then determines which type of command it is beetween the 6
*	Rush - Adds a node in the front of the list
*	Remove - Removes a specific node
*	Head - Prints out first node
*	Tail - Prints out last node
*	PrintList - Prints out whole list wiht "-" between each node
*	Length - Prints out size of the list
*Also checks the input if its valid
*	if not then error message is printed
*
*
*Description:
*Creates node structure used in the list
*	data - type char, stores the data or input from the file
*	node - type node, stores the next linked node
*
*Input:
*Nothing
*
*Output:
*Returns nothing
*But creates a node
*
*Caveats:
*Only accepts char as data inputs
*/
struct node{
	char data;
	struct node * next;
};
/*Global variable head*/
/*head is always available to all functions*/
/*head - type node, stores the very first node in the list*/
struct node *head = NULL;
/*Global variable size*/
/*size is always available to all functions*/
/*size - type int, stores the size of the list*/
int size = 0;
/*
*Description: invalidInput
*Prints out input no valid to standard error "stderr"
*
*Input:
*Nothing
*
*Output:
*Returns nothing
*Prints out standard error message
*
*Caveats:
*Nothing
*/
void invalidInput(){
	fprintf(stderr,"Input not valid\n");
}
/*
*Description: Push
*Push adds a node in front of the list
*
*Compares data and checks if it's valid
*	65 is A and 90 is Z in ASCI
*	data must be within this specific range
*		else it calls invalid input function 
*
*Ceates a empty node then assgins it with data from received by file
*Assigns the new create node to the front of the list
*
*Input:
*newData - type char, but this char is not the character char, it's an Integer
*		 - a ASCI representation of the character
*
*Output:
*Returns nothing
*Creates a new node and puts it to the front of list
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
void Push(char newData){
	/*Checks if data is within range A ~ Z*/
	if(newData<65 || newData>90){
		invalidInput();
	}else{
		/*Allocates memory to a newly created node*/
		/*With default values of nothing*/
		struct node * newNode = malloc(sizeof(struct node));
		/*Updates data of the new node*/
		newNode -> data = newData;
		/*Updates the next node of new node to become head*/
		newNode -> next = head;
		/*Sets new node to head*/
		head = newNode;
		/*Increase the size of the list*/
		size++;
	}
}
/*
*Description: Length
*First checks if the list is empty
*Checks if head exist
*	else it calls invalid input function 
*Prints out the size of the list
*
*Input:
*Returns nothing
*Prints out length of the list
*
*Output:
*Nothing, but prints out size of the list
*
*Caveats:
*Nothing
*/
void Length(){
	if(head == NULL){
		invalidInput();
	}else{
		printf("%d\n",size);
	}
}
/*
*Description: Remove
*First checks if data received from file is
*Empty and within range A ~ Z (Uses ASCI values)
*	else it calls invalid input function 
*	by setting a flag to true/1
*Checks if the head is first encoutered node to be removed
*	if it is then update head to next node
*Then runs a loop to find data
*	if its found then update the next node to next of the next node
*	sets flag to true/1
*
*If flag is false
*	then data doesnt exit in the node or
*	input is invalid, then function invalid input is called
*else
*	decrease the size of list
*
*Input:
*deleteData - type char, but this char is not the character char, it's an Integer
*		 - a ASCI representation of the character
*
*Output:
*Nothing
*A node is either removed or error message is printed out
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
void Remove(char deleteData){
	/*Flag for operation*/
	int flag = 0;
	/*Checks if data is within range A ~ Z*/
	/*Checks if head is empty*/
	if(head == NULL || deleteData<65 || deleteData>90){
		flag = 0;
	}else if(head -> data == deleteData){
		/*Updates head to the new node*/
		head = head -> next;
		flag = 1;
	}else{
		/*Creates a node current, starting position at head*/
		struct node *current = head;
		/*Only loops if a node has not been deleted*/
		/*Loops until end of file has been reach and delete has been performed*/
		while(flag == 0 && current -> next != NULL){
			/*Since we checked the head node we can safely just check the 2nd node onwards*/
			/*If 2nd node and onwards matches data*/
			if(current -> next -> data == deleteData){
				/*Update next node of current to the next next node*/
				current -> next = current -> next -> next;
				/*Set delete performed flag to true/1*/
				flag = 1;
			}
			/*Go to next node*/
			current = current -> next;
		}
	}
	/*If no deletion has been performed*/
	/*Call invalidInput function*/
	if(flag == 0){
		invalidInput();
	}else if (flag == 1){
		/*Deletion has been performed*/
		/*Size of the lis is decreased*/
		size--;
	}
}
/*
*Description: Tail
*First checks if head isn't empty
*	else it calls invalid input function 
*Loops through list until the last node
*Prints out the last node
*
*Input:
*Nothing
*
*Output:
*Returns nothing
*Prints out last node
*
*Caveats:
*Nothing
*/
void Tail(){
	/*Checks if head is empty*/
	if(head == NULL){
		invalidInput();
	}else{
		/*Creates node at head position*/
		struct node * current = head;
		/*Loops through until just before end of list*/
		/*aka Last node*/
		while(current -> next != NULL){
			/*Go to next node*/
			current = current -> next;
		}
		printf("%c\n",current -> data);
	}
}
/*
*Description: Head
*First checks if head isn't empty
*	else it calls invalid input function 
*Prints out the first node
*
*Input:
*Nothing
*
*Output:
*Returns nothing
*Prints out first node
*
*Caveats:
*Nothing
*/
void Head(){
	if(head == NULL){
		invalidInput();
	}else{
		printf("%c\n",head -> data);
	}
}
/*
*Description: Head
*First checks if head isn't empty
*	else it prints "-"
*Loops through list and prints data
*Seperated with "-"
*	if the last node is reached then
*		"-" is not printed
*
*Input:
*Nothing
*
*Output:
*Returns nothing
*Prints out first node
*
*Caveats:
*Nothing
*/
void PrintList(){
	/*Checks if head is empty*/
	if(head == NULL){
		/*List is empty*/
		printf("-\n");
	}else{
		/*Creates a node at position head*/
		struct node * current = head;
		/*Loops through until end of list*/
		while(current != NULL){
			/*Prints data and "-"*/
			printf("%c",current->data);
			if(current -> next != NULL){
				/*Doesnt print "-" cause its not the end of list yet*/
				printf("-");
			}
		/*Go to next node*/
		current = current->next;
		}
		printf("\n");
	}
}
/*
*Description: main
*Gets the file name and use fopen to read file
*Loops until end of file
*	checks each line by taking the command (1st part) by usnig string token
*	if its either Push or Remove
*		then checks the data (2nd part) by using string token
*	else it should be the other commands
*	
*	but if it's neither of this specificed commands
*		invalidInput function is called
*
*Input:
*argc - type int, total amout of input in the command line
*argcv - type char array, arg[1] should be file name to be read in
*
*Output:
*Nothing
*Follows commands and executes accordingly
*
*Caveats:
*Only accepts file names
*Memory might run out
*/
int main(int argc, char *argv[]){
	/*Takes in file name*/
	char const * const fileName = argv[1];
	/*Reads file*/
	FILE * file = fopen(fileName,"r");
	/*Create a large line, type char array to store each line of the file*/
	char line[256];
	/*Loop until end of file*/
	while(fgets(line,sizeof(line),file)){
	/*Replace all new lines with NULL or 0*/
	/*0 is not equal to '0'*/
        line[strcspn(line, "\r\n")] = 0;
        /*Use string token to strip out everything before the " "*/
        /*This is the command part*/
        char * command=strtok(line, " ");
	if(command != NULL){
		/*Checks if command is equal to Push*/
	        if(strcmp(command,"Push") == 0){
		    /*Use string token to strip out everything after he " "*/
	            char * data=strtok(NULL, " ");
	            /*Calls Push function*/
	            /*Push takes in single char*/
	            Push(data[0]);
	        /*Checks if command is equal to Remove*/
	        }else if(strcmp(command,"Remove") == 0){
	            /*Use string token to strip out everything after he " "*/
		    char * data=strtok(NULL, " ");
		    /*Calls Remove function*/
	            /*Remove takes in single char*/
	            Remove(data[0]);
	        }else{
	            /*Checks if command is equal to Length*/
	            if(strcmp(command,"Length") == 0){
	            	/*Calls Length function*/
	                Length();
	            /*Checks if command is equal to PrintList*/
	            }else if(strcmp(command,"PrintList") == 0){
	            	/*Calls PrintList function*/
	                PrintList();
	            /*Checks if command is equal to Head*/
	            }else if(strcmp(command,"Head") == 0){
	            	/*Calls Head function*/
	                Head();
	            /*Checks if command is equal to Tail*/
	            }else if(strcmp(command,"Tail") == 0){
	            	/*Calls Tail function*/
	                Tail();
	            }else{
	            	/*Command doesnt match any of the other*/
	            	/*Calls invalidInput function*/
	                invalidInput();
	            }
	        }
	}else{
		invalidInput();
	}
	}
	/*Best practise to close file*/
	fclose(file);
return 0;
}
