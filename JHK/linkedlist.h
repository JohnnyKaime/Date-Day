/******************************************************************
*Jia-Cong Hou
*3565155
*Prac3 - Linkedlist using pointer - pointer
*File - linkedlist.h
*
*Linkedlist file that contains all the function that a node
*and linkedlist can perform. The driver or main.c calls this to 
*while the main.c runs through the list of testcases, it calls
*each function inside linkedlist.
*
*A more detailed description is by each function level documentation
*Functions include the following:
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
*********************************************************************/
/*Includes system library*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*Includes user defined files*/
#include "node.h"
#include "error.h"
/*Global variable HEAD*/
/*HEAD is always available to all functions*/
/*HEAD - type node, stores the very first node in the list*/
struct node * HEAD = NULL;
/*Global variable SIZE*/
/*SIZE is always available to all functions*/
/*SIZE - type int, stores the size of the list*/
int SIZE = 0;
/*
*Description: Push
*Push adds a node in front of the list
*
*Compares data and checks if it's valid
*	65 is A and 90 is Z in ASCI
*	data must be within this specific range
*		else it calls invalid input function 
*
*Since it takes in the pointer pointer, which we use HEAD is most case
*(This could be used to push other nodes at any position provided pointer
*is given at the corrent format. One before the matching case of Data)
*Ceates a empty node then assgins it with data from received by file
*Assigns the new create node points to the pointer pointer
*Then pointer pointer points (next) to the new create node
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*	  - a ASCI representation of the character
*ptpt - type struct node, pointer pointer of a node
*
*Output:
*Returns nothing
*Creates a new node and puts it to the front of list
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
void Push(struct node ** ptpt, char data){
	/*Checks if data is within range A ~ Z*/
	if(data < 65 || data > 90){
		InvalidInput();
	}else{
		/*Allocates memory to a newly created node*/
		/*With default values of nothing*/
		struct node * newNode = malloc(sizeof(struct node));
		/*Updates data of the new node*/
		newNode -> data = data;
		/*Updates the next node of new node to pointer pointer*/
		newNode -> next = * ptpt;
		/*Pointer pointer points to the new create node*/
		*ptpt = newNode;
		/*Increase the size of the list*/
		SIZE++;
	}
}
/*
*Description: InsertBefore
*InsertBefore adds a node in front of the given node
*
*Checks if list is empty or not
*Checks if the given data is within the list
*Compares data and checks if it's valid
*	65 is A and 90 is Z in ASCI
*	data must be within this specific range
*		else it calls invalid input function 
*
*Using the Find function, if Find returns NULL, then our target is by the 
*Head node, then we call Push function passing in the Head node address and
*data, this creates a new node in front of the list.
*
*Else Find function will return a pointer pointer, this pointer next values 
*points to the node of our target node, with the matching data.
*Then we call our Push function giving this pointer pointer next node and
*data, thie creates a new node in front of the target node.
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*	  - a ASCI representation of the character
*ptpt - type struct node, pointer pointer of a node
*
*Output:
*Returns nothing
*Creates a new node and puts it to the front of node with the given data
*Error message
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
void InsertBefore(struct node * ptpt, char data){
	/*Checks if data is within range A ~ Z*/
	/*List must not be empty*/
	if(data < 65 || data > 90 || HEAD == NULL){
		InvalidInput();
	/*Checks if Find function returned a NULL*/
	}else if(ptpt == NULL){
		/*Call Push giving HEAD node address*/
		/*Because our target is in the first node*/
		/*We need to insert before that by passing in HEAD node*/
		Push(&HEAD,data);
		/*Increase size of the list*/
		SIZE++;
	}else{
		/*Call Push giving the pointers pointers next node*/
		Push(&(ptpt)->next,data);
		/*Increase size of the list*/
		SIZE++;
	}
}
/*
*Description: InsertAfter
*InsertAfter adds a node in behind the given node
*
*Checks if list is empty or not
*Checks if the given data is within the list
*Compares data and checks if it's valid
*	65 is A and 90 is Z in ASCI
*	data must be within this specific range
*		else it calls invalid input function 
*
*Using the Find function, if Find returns NULL, then our target is by the 
*Head node, then we call Push function passing in the Head node address and
*data, this creates a new node to the back of the given node.
*
*Else Find function will return a pointer pointer, this pointer next next
*values points to the node of our target node, with the matching data.
*Then we call our Push function giving this pointer pointer next next node
*and data, thie creates a new node to the back of the target node.
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*	  - a ASCI representation of the character
*ptpt - type struct node, pointer pointer of a node
*
*Output:
*Returns nothing
*Creates a new node and puts it to the back of node with the given data
*Error message
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
void InsertAfter(struct node * ptpt, char data){
	/*Checks if data is within range A ~ Z*/
	/*List must not be empty*/
	if(data < 65 || data > 90 || HEAD == NULL){
		InvalidInput();
	/*Checks if Find function returned a NULL*/
	}else if(ptpt == NULL){
		/*Call Push giving HEAD node address*/
		/*Because our target is in the first node*/
		/*We need to insert after that by passing next node*/
		Push(&HEAD->next,data);
		/*Increase size of the list*/
		SIZE++;
	}else{
		/*Creates a new node last*/
		struct node * last = HEAD;
		/*Move it until the just before last position*/
		/*A node before*/
		/*A pointer pointer pointing to last node*/
		while(last -> next != NULL){
			last = last -> next;
		}
		/*If Find function returns the last node in the list*/
		/*That means our target is at the end of the node*/
		if(ptpt == last){
			/*Call Push function while passing node just before last node*/
			Push(&last,data);
		}else{
			/*Call Push function while passing node pointer pointer pointing to the next next node*/
			/*Because the previous if statement made sure the boundaries, end of list is valid*/
			Push(&(ptpt)->next->next,data);
		}
		/*Increase size of the list*/
		SIZE++;
	}
}
/*
*Description: Append
*Append adds a node in front of the list
*
*Compares data and checks if it's valid
*	65 is A and 90 is Z in ASCI
*	data must be within this specific range
*		else it calls invalid input function 
*
*Since it takes in the pointer pointer, which we use HEAD is most case
*(This could be used to push other nodes at any position provided pointer
*is given at the corrent format. One before the matching case of Data)
*Ceates a empty node then assgins it with data from received by file
*Assigns the new create node points to the pointer pointer
*Then pointer pointer points (next) to the new create node
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*	  - a ASCI representation of the character
*ptpt - type struct node, pointer pointer of a node
*
*Output:
*Returns nothing
*Creates a new node and puts it to the end / back of list
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
struct node * Append(struct node ** ptpt, char data){
	/*Creates a current node use to move to end of the list*/
	struct node * current = *ptpt;
	/*Checks if data is within range A ~ Z*/
	if(data < 65 || data > 90){
		InvalidInput();
	/*Checks if HEAD is empty, list is empty*/
	}else if(current == NULL){
		/*Call Push function while passing HEAD address*/
		Push(ptpt, data);
		/*Increase size of the list*/
		SIZE++;
	}else{
		/*Navigate till just before the end of the list*/
		/*A node before the last node in the list*/	
		while(current -> next != NULL){
			current = current -> next;
		}
		/*Call Push while passing the end node*/
		Push(&(current -> next), data);
		/*Increase size of the list*/
		SIZE++;
	}
}
/*
*Description: PrintList
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
*Prints out "-" if list is empty
*Prints out data of each node with "-" serperating each data
*
*Caveats:
*Nothing
*/
void PrintList(){
	/*Checks if head is empty*/
	if(HEAD == NULL){
		printf("-\n");
	}else{
		/*Creates a node at position head*/
		struct node * current = HEAD;
		/*Loops through until end of list*/
		while(current != NULL){
			/*Prints data and "-"*/
			printf("%c",current->data); 
			if(current -> next != NULL){
				/*Doesnt print "-" cause its not the end of list yet*/
				printf("-");
			}
			/*Go to next node*/
			current = current -> next;
		}
		printf("\n");
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
	if(HEAD == NULL && SIZE == 0){
		printf("0\n");
	}else{
		printf("%d\n",SIZE);
	}
}
/*
*Description: Find
*Checks if the HEAD node is empty
*Checks if the HEAD node data is the target node with matching data
*Loops from the 2nd position
*	Checks if the last node next node is NULL
*		Hence end of file reached, doesnt exit in list
*	Return that pointer pointer next node
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*Prints out length of the list
*
*Output:
*Returns 0 to terminate
*Returns pointer pointer to next node with matching data
*
*Caveats:
*Nothing
*/
struct node * Find(struct node ** ptpt, char data){
	/*If given pointer or HEAD is NULL*/
	if(ptpt == NULL || HEAD == NULL){
		/*Terminate*/
		return 0;
	/*If give pointer data is matching to the data given*/
	}else if((*ptpt) -> data == data){
		/*Return NULL hence head node*/
		return NULL;
	}else{
		/*Creates a node from the given pointer (normally HEAD address)*/
		struct node * current = *ptpt;
		/*Since we checked the first value or HEAD position*/
		/*We start checking by current next node*/
		/*If that node is not NULL and not equal to data given*/
		while(current -> next != NULL && current -> next -> data != data){
			/*Continue moving to next node*/
			current = current -> next;
		}
		/*If the next node is NULL*/
		/*Reached the end of file*/
		if(current -> next== NULL){
			/*Terminate*/
			return 0;
		}else{
			/*Return that pointer pointer or position in the list*/
			return current;
		}
	}
}
/*
*Description: Remove
*First checks if data received from file is
*Empty and within range A ~ Z (Uses ASCI values)
*	else it calls invalid input function 
*Checks if the head is first encoutered node to be removed
*	if it is then update head to next node
*Then runs a loop to find data
*	if its found then update the next node to next of the next node
*
*Input:
*data - type char, but this char is not the character char, it's an Integer
*	  - a ASCI representation of the character
*ptpt - type struct node, pointer pointer of a node
*
*Output:
*Nothing
*A node is either removed or error message is printed out
*
*Caveats:
*Only accpets data between A ~ Z
*No integers, data must be in capital, and a single character
*/
void Remove(struct node ** ptpt, char data){
	/*Checks if data is within range A ~ Z*/
	/*Checks if head is empty*/
	if(HEAD == NULL || data < 65 || data > 90){
		InvalidInput();
	/*Check if HEAD is the corrent node to delete*/
	}else if(HEAD -> data == data){
		/*Updates head to the new node*/
		/*Deletes HEAD*/
		HEAD = HEAD -> next;
		/*Decrease size of list*/
		SIZE--;
	}else{
		/*Find the pointer pointer next node that points to the value*/
		struct node * delete = Find(ptpt,data);
		/*If Find functions returns NULL then calls InvalidInput*/
		if(delete != NULL){
			/*Deletes the node*/
			/*Updates node next to the next next node*/
			delete -> next = delete -> next -> next;
			/*Decrease size of list*/
			SIZE--;
		}else{
			InvalidInput();
		}
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
	if(HEAD == NULL){
		InvalidInput();
	}else{
		printf("%c\n", HEAD -> data);
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
	/*Checks if list is empty*/
	if(HEAD == NULL){
		InvalidInput();
	}else{
		/*Creates node at head position*/
		struct node * current = HEAD;
		/*Loops through until just before end of list*/
		/*aka Last node*/
		while(current -> next != NULL){
			/*Go to next node*/
			current = current -> next;
		}
		printf("%c\n", current -> data);
	}
}

